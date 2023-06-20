#include    "blok.h"

#include    <QTextStream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BLOK::BLOK(QObject *parent) : Device(parent)
  , code_alsn(1)
  , old_code_alsn(1)
  , state_RB(false)
  , state_RB_old(false)
  , state_RBS(false)
  , state_RBS_old(false)
  , state_EPK(false)
  , v_kmh(0.0)
  , v(0.0)
  , delta_t(0.1)
  , v_count(0)
  , t_diff(0.0)
  , acceleration(0.0)
  , key_epk(false)
  , is_dislplay_ON(false)
  , check_vigilance(false)
  , safety_timer(new Timer(45.0, false))
  , beepTimer(new Timer(0.5, true))
  , beep_interval(0.5)
  , rail_coord(0.0)
  , train_length(0.0)
  , v_max(300.0)
  , current_limit(300.0)
  , next_limit(300.0)
  , dir(1)
  , limit_dist(0)
  , station_idx(-1)
  , begin_station_finded(false)
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
    safety_timer->step(t, dt);
    beepTimer->step(t, dt);

    calc_acceleration(t, dt);

    Device::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::loadSpeedsMap(QString path)
{
    QFile map_file(path);

    if (map_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!map_file.atEnd())
        {
            QByteArray line;
            line = map_file.readLine();

            QTextStream ss(&line);

            speed_limit_t limit;
            ss >> limit.coord >> limit.value;

            limits.push_back(limit);
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::loadStationsMap(QString path)
{
    QFile stations_file(path);

    if (stations_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!stations_file.atEnd())
        {
            QByteArray line = stations_file.readLine();
            QStringList tokens = QString(line).remove('\n').split(';');

            if (tokens.size() < 3)
                continue;

            station_t station;
            qSetRealNumberPrecision(2);
            station.begin_coord = pf(tokens[0].toDouble() - 3000.0);
            station.end_coord = pf(tokens[1].toDouble() + 3000.0);
            station.name = tokens[2];

            stations.push_back(station);
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::setTrainLength(double train_length)
{
    if (this->train_length == train_length)
        return;

    double length_diff = train_length - this->train_length;
    this->train_length = train_length;

    if (limits.empty())
        return;
    for (size_t i = 0 + hs_n(dir); i < limits.size() - hs_p(dir); ++i)
    {
        if (limits[i + dir].value > limits[i].value)
        {
            limits[i + hs_p(dir)].coord += dir * length_diff;
        }
    }
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
    if (hs_n(U_pow - 100.0))
    {
        is_dislplay_ON = false;
        return;
    }

    is_dislplay_ON = true;

    speed_control();

    // Ничего не делаем при выключенном ЭПК
    if (!key_epk)
    {
        epk_state.reset();
        return;
    }

    if (code_alsn < old_code_alsn)
        epk_state.reset();

    alsn_process(code_alsn);

    stations_process();

    if (code_alsn == 1)
    {
        if (v_kmh > 60.0)
        {
            epk_state.reset();
            return;
        }

        if ( (!safety_timer->isStarted()) && (v_kmh > 5) )
        {
            safety_timer->start();
        }
        else
        {
            safety_timer->stop();
        }
    }

    if (code_alsn == 2)
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
void BLOK::alsn_process(int code_alsn)
{
    switch (code_alsn)
    {
    case 0:
        {
            lamps[WHITE_LAMP] = 1.0f;

            break;
        }
    case 1:
        {
            lamps[RED_YELLOW_LAMP] = 1.0f;

            break;
        }

    case 2:
        {
            lamps[YELLOW_LAMP] = 1.0f;

            break;
        }

    case 3:
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
        emit soundPlay("BLOK_RB");
    }

    if ( (state_RBS && (!state_RBS_old)) ||
         (state_RBS_old && (!state_RBS)) )
    {
        emit soundPlay("BLOK_RB");
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
void BLOK::speed_control()
{
    calc_speed_limits();

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
void BLOK::calc_speed_limits()
{
    if (!key_epk)
    {
        current_limit = next_limit = 300.0;
        return;
    }

    if (limits.empty())
    {
        current_limit = next_limit = v_max;
        return;
    }

    speed_limit_t cur_lim;
    speed_limit_t next_lim;

    findLimits(cur_lim, next_lim);

    if (cur_lim.value > v_max)
    {
        cur_lim.value = v_max;
    }

    double v_lim = v_max;

    if (cur_lim.value > next_lim.value)
    {
        double a = 0.7;
        limit_dist = pf(dir * (next_lim.coord - rail_coord));
        v_lim = sqrt( pow(next_lim.value / Physics::kmh, 2) + 2 * a * limit_dist) * Physics::kmh;
    }

    current_limit = min(v_lim + 1, cur_lim.value + 1);
    next_limit = next_lim.value + 1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::findLimits(speed_limit_t &cur_limit, speed_limit_t &next_limit)
{
    if (limits.empty())
        return;

    size_t left_idx = 0;
    size_t right_idx = limits.size();
    size_t idx = (left_idx + right_idx) / 2;

    while (idx != left_idx)
    {
        speed_limit_t limit = limits[idx];

        if (rail_coord <= limit.coord)
            right_idx = idx;
        else
            left_idx = idx;

        idx = (left_idx + right_idx) / 2;
    }

    cur_limit = limits[idx];

    if ((dir < 0) && (idx <= 0))
    {
        next_limit = speed_limit_t();
        next_limit.coord = -next_limit.coord;
    }
    else if ((dir > 0) && (idx >= (limits.size() - 1)))
    {
        next_limit = speed_limit_t();
    }
    else
    {
        next_limit.coord = limits[idx + hs_p(dir)].coord;
        next_limit.value = limits[idx + dir].value;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::stations_process()
{
    if (stations.empty())
        return;

    find_begin_station();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::find_begin_station()
{
    if (begin_station_finded)
        return;

    for (size_t i = 0; i < stations.size(); ++i)
    {
        if ( (rail_coord >= stations[i].begin_coord) &&
             (rail_coord <= stations[i].end_coord) )
        {
             station_idx = i;
             break;
        }
        else
        {
            station_idx = -1;
        }
    }
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
    emit soundPlay("BLOK_RB");
}
