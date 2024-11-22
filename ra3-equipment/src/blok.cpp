#include    "blok.h"

#include    <QTextStream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BLOK::BLOK(QObject *parent) : Device(parent)
{
    epk_state.reset();

    connect(safety_timer, &Timer::process, this, &BLOK::onSafetyTimer);
    connect(beepTimer, &Timer::process, this, &BLOK::onBeepTimer);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BLOK::~BLOK()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::step(double t, double dt)
{
    if (no_code_limit > no_code_limit_ref)
        passed_distance += v * dt;

    safety_timer->step(t, dt);
    beepTimer->step(t, dt);

    calc_acceleration(t, dt);

    Device::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::loadStationsMap(QString path)
{
    QFile stations_file(path);

    if (!stations_file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QTextStream stream(&stations_file);

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList tokens = line.split('\t');

        station_t station;
        station.name = tokens[0];
        station.coord.x = tokens[1].toDouble();
        station.coord.y = tokens[2].toDouble();
        station.coord.z = tokens[3].toDouble();

        stations.push_back(station);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString BLOK::getStationText() const
{
    QString tmp = station_text;
    tmp.resize(STATION_MAX_SYMBOLS, QChar(' '));
    return tmp;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString BLOK::getInfoText() const
{
    QString tmp = info_text;
    tmp.resize(INFO_MAX_SYMBOLS, QChar(' '));
    return tmp;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
sound_state_t BLOK::getSoundState(size_t idx) const
{
    if (idx < sounds.size())
        return sounds[idx];
    return Device::getSoundState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float BLOK::getSoundSignal(size_t idx) const
{
    if (idx < sounds.size())
        return sounds[idx].createSoundSignal();
    return Device::getSoundSignal();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y);
    Q_UNUSED(t);

    // Очищаем состояние ламп
    std::fill(lamps.begin(), lamps.end(), 0.0f);

    // Ничего не делаем при выключенном питании
    if (hs_n(U_pow - 0.95 * U_nom))
    {
        is_red.reset();
        is_dislplay_ON = false;
        is_trac_allowed = false;
        station_text = "";
        info_text = "";
        return;
    }

    is_dislplay_ON = true;
    is_trac_allowed = true;

    stations_process();

    calc_speed_limits_by_speedmap();

    calc_speed_limits_by_next_signal();

    speed_control();

    // Ничего не делаем при выключенном ЭПК
    if (!key_epk)
    {
        if (v_kmh > 1.0)
            epk_state.reset();

        key_epk_old = false;
        is_red.reset();
        return;
    }

    if (code_alsn < old_code_alsn)
    {
        epk_state.reset();
        safety_timer->stop();
    }

    if (is_red.getState())
    {
        lamps[RED_LAMP] = 1.0f;
        check_vigilance = true;
        epk_state.reset();
        is_trac_allowed = false;
        safety_timer->stop();
        return;
    }

    alsn_process(code_alsn);

    if (code_alsn == ALSN::RED_YELLOW)
    {
        if (v_kmh > 5)
        {
            if (!safety_timer->isStarted())
                safety_timer->start();
        }
        else
        {
            safety_timer->stop();
        }
    }

    if (code_alsn == ALSN::YELLOW)
    {
        if (v_kmh > 60.0)
        {
            if (!safety_timer->isStarted())
                safety_timer->start();
        }
        else
        {
            safety_timer->stop();
        }
    }

    if (state_RB || state_RBS)
    {
        epk_state.set();
        safety_timer->stop();
    }

    check_vigilance = !epk_state.getState();

    sounds_process();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::ode_system(const state_vector_t &Y,
                      state_vector_t &dYdt,
                      double t)
{
    Q_UNUSED(Y);
    Q_UNUSED(dYdt);
    Q_UNUSED(t);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    double safety_check_interval = 45.0;

    cfg.getDouble(secName, "SafetyCheckInterval", safety_check_interval);

    safety_timer->setTimeout(safety_check_interval);

    //cfg.getDouble(secName, "BeepInterval", beep_interval);

    //beepTimer->setTimeout(beep_interval);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::alsn_process(ALSN code_alsn)
{
    switch (code_alsn)
    {
    case ALSN::NO_CODE:
    {
        if ((old_code_alsn == ALSN::RED_YELLOW) && (v_kmh > 1.0))
        {
            lamps[RED_LAMP] = 1.0f;
            is_red.set();
        }
        else
        {
            if (!is_red.getState())
                lamps[WHITE_LAMP] = 1.0f;
        }

        break;
    }
    case ALSN::RED_YELLOW:
    {
        lamps[RED_YELLOW_LAMP] = 1.0f;

        break;
    }

    case ALSN::YELLOW:
    {
        lamps[YELLOW_LAMP] = 1.0f;

        break;
    }

    case ALSN::GREEN:
    {
        lamps[GREEN_LAMP1] = 1.0f;

        break;
    }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::sounds_process()
{
    if ( (state_RB && (!state_RB_old)) ||
         (state_RB_old && (!state_RB)) )
    {
        sounds[BUTTON_PRESS_SOUND].play();
    }

    if ( (state_RBS && (!state_RBS_old)) ||
         (state_RBS_old && (!state_RBS)) )
    {
        sounds[BUTTON_PRESS_SOUND].play();
    }

    state_RB_old = state_RB;
    state_RBS_old = state_RBS;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::calc_acceleration(double t, double dt)
{
    Q_UNUSED(t)

    if (v < 1e-4)
    {
        acceleration = 0;
        return;
    }

    if (t_diff >= delta_t)
    {
        v_i[v_count] = v;
        t_diff = 0;
        v_count++;
    }

    if (v_count >= v_i.size())
    {
        v_count = 0;
        t_diff = 0;

        acceleration = (3 * v_i[2] - 4 * v_i[1] + v_i[0]) / 2.0 / delta_t;
    }

    t_diff += dt;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::calc_speed_limits_by_speedmap()
{
    target_dist = 5000.0;

    if (!key_epk)
    {
        current_limit = v_max;
        next_limit = v_max;
        return;
    }

    // Ограничения скорости в топологии маршрута
    current_limit = speedmap->getCurrentLimit();
    next_limit = speedmap->getNextLimit();

    double v_lim = v_max;
    if ((current_limit - 1) > next_limit)
    {
        // Если следующее ограничение меньше текущего,
        // запоминаем растояние до него как до следующей цели
        target_dist = speedmap->getNextLimitDistance();

        // И рассчитываем кривую торможения
        double a = 0.7;
        double v_next = next_limit / Physics::kmh;
        v_lim = min(v_lim, sqrt(v_next * v_next + 2 * a * target_dist) * Physics::kmh);
    }

    current_limit = min(v_lim, current_limit) + 1;
    next_limit = min(v_max, next_limit);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::calc_speed_limits_by_next_signal()
{
    // Расстояние до следующего светофора в топологии маршрута
    double distance = coilALSN->getNextSignalDistance();

    // Если сигнал АЛСН жёлтый,
    // рассчитываем кривую торможения к светофору до 60 км/ч
    if (code_alsn == ALSN::YELLOW)
    {
        double a = 0.7;
        double yellow_limit = 61.0 / Physics::kmh;
        double v_lim = sqrt(yellow_limit * yellow_limit + 2 * a * distance) * Physics::kmh;
        current_limit = min(v_lim, current_limit);
    }

    // Если сигнал АЛСН красный с жёлтым (светофор закрыт),
    // устанавливаем ограничение 60 км/ч и
    // рассчитываем кривую торможения к светофору до 0 км/ч
    if (code_alsn == ALSN::RED_YELLOW)
    {
        double a = 0.7;
        double v_lim = sqrt(2 * a * distance) * Physics::kmh;

        double red_yellow_limit = 61.0;
        v_lim = min(v_lim, red_yellow_limit);
        current_limit = min(v_lim, current_limit);
    }

    // Если сигнал АЛСН отсутствует, устанавливаем ограничение 40 км/ч
    if (code_alsn == ALSN::NO_CODE)
    {
        // Если до этого был код зелёный или жёлтый,
        // плавно уменьшаем ограничение от текущей скорости
        if ((old_code_alsn == ALSN::YELLOW) || (old_code_alsn == ALSN::GREEN))
        {
            no_code_limit = max(no_code_limit_ref, v_kmh + 5.0);
        }

        // Уменьшаем ограничение на 1 км/ч каждые 50 метров
        if ((no_code_limit > no_code_limit_ref) && (passed_distance > 50.0))
        {
            passed_distance = 0.0;
            no_code_limit += -1.0;
        }

        current_limit = min(no_code_limit, current_limit);
    }
    else
    {
        no_code_limit = no_code_limit_ref;
    }

    QString liter = coilALSN->getNextSignalLiter();
    if ( (current_limit > next_limit) && (liter.isEmpty() || (distance > target_dist)) )
    {
        // Если впереди ограничение скорости,
        // а следующего светофора нет или он дальше чем ограничение,
        // то выводим информацию об ограничении скорости
        info_text = "ОПАСНОЕ МЕСТО";
        liter = QString::number(next_limit, 'f', 0) + " КМ/Ч";

        size_t fill_size = INFO_MAX_SYMBOLS - info_text.size() - liter.size();
        info_text += QString(fill_size, QChar(' '));
        info_text += liter;
        return;
    }

    if (liter.isEmpty())
    {
        // Если следующего светофора нет, ничего не выводим
        target_dist = 0.0;
        info_text = "";
    }
    else
    {
        // Выводим информацию о следующем светофоре
        target_dist = distance;
        info_text = "СВЕТОФОР";

        size_t fill_size = INFO_MAX_SYMBOLS - info_text.size() - liter.size();
        info_text += QString(fill_size, QChar(' '));
        info_text += liter;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::speed_control()
{
    int V_kmh = qRound(v_kmh);

    if (V_kmh < current_limit - 3)
    {
        beepTimer->stop();
    }
    else
    {
        if (!beepTimer->isStarted())
            beepTimer->start();
    }

    if (V_kmh >= current_limit + 1)
    {
        epk_state.reset();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::stations_process()
{
    station_idx = -1;
    if (stations.empty())
        return;

    double min_distance = station_search_radius;
    for (size_t i = 0; i < stations.size(); ++i)
    {
        double distance = length(coord - stations[i].coord);
        if (min_distance > distance)
        {
            min_distance = distance;
            station_idx = i;
        }
    }
    if (station_idx >= 0)
        station_text = stations[station_idx].name;
    else
        station_text = "";
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::onSafetyTimer()
{
    epk_state.reset();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::onBeepTimer()
{
    sounds[VELOCITY_NEAR_LIMIT_SOUND].play();
}
