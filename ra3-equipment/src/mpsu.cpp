#include    "mpsu.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MPSU::MPSU(QObject *parent) : Device(parent)
  , is_reseted(false)
  , old_start_state(false)
  , n_min(800)
  , n_max(1800)
  , n_min_gb(1700)
  , v_HB(1.0)
  , p_HB(0.15)
  , startButtonTimer(new Timer(5.0, false))
  , button_select_old(false)
  , button_speed_plus_old(false)
  , button_speed_minus_old(false)
  , is_speed_hold_disable(false)
  , Kp(1.0)
  , Ki(0.0)
  , dv(0.0)
  , u(0.0)
  , T(0.5)
  , lengthHead(24.24)
  , lengthMiddle(24.7)

{
    connect(startButtonTimer, &Timer::process, this, &MPSU::slotStartButtonTimer);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MPSU::~MPSU()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::step(double t, double dt)
{
    // При выключенном питании - ничего не делаем
    if (!mpsu_input.is_power_on)
    {
        is_reseted = false;
        mpsu_output = mpsu_output_t();
        return;
    }

    // Однократный сброс при включении питания
    if (!is_reseted)
    {
        reset();
        return;
    }

    main_loop_step(t, dt);

    startButtonTimer->step(t, dt);

    Device::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::setInputData(const mpsu_input_t &mpsu_input)
{
    // Принимаем данные извне ТОЛЬКО при включенном питании
    if (mpsu_input.is_power_on)
        this->mpsu_input = mpsu_input;
    else
        this->mpsu_input = mpsu_input_t();

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
mpsu_output_t MPSU::getOutputData() const
{
    return mpsu_output;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    if (!mpsu_output.is_speed_hold_ON)
        Y[0] = 0;

    Y[0] = cut(Y[0], -1.0, 1.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)

    dYdt[0] = Ki * dv;
    dYdt[1] = (u - Y[1]) / T;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::load_config(CfgReader &cfg)
{
    Q_UNUSED(cfg)

    QString secName = "Device";

    cfg.getDouble(secName, "n_min", n_min);
    cfg.getDouble(secName, "n_max", n_max);
    cfg.getDouble(secName, "v_HB", v_HB);
    cfg.getDouble(secName, "p_HB", p_HB);
    cfg.getDouble(secName, "n_min_gb", n_min_gb);

    cfg.getDouble(secName, "lengthHead", lengthHead);
    cfg.getDouble(secName, "lengthMiddle", lengthMiddle);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::reset()
{
    std::fill(y.begin(), y.end(), 0.0);
    mpsu_input = mpsu_input_t();
    mpsu_output = mpsu_output_t();

    old_start_state = false;

    trig_disel_start.reset();

    is_reseted = true;

    std::fill(errors.begin(), errors.end(), false);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::train_config_process()
{
        // Обнуляем длину поезда
        mpsu_output.train_size = 0;
        mpsu_output.train_length = 0.0;
        // Обрабатываем сигналы от вагонов спереди
        int tc = static_cast<int>(mpsu_input.sme_train_config_fwd);
        if (tc > 0)
            for (int i = 0; i < MAX_TRAIN_SIZE - 1; i++)
            {
                // Сигнал от головных вагонов сзади разворачиваем (true)
                mpsu_output.train_config[0] = train_config_parsing(tc % SME_MULTIPLIER, true);
                tc = tc / SME_MULTIPLIER;
                if (tc == 0)
                    break;
                else
                    // Учитываем, что сигналы спереди пришли в обратном порядке
                    for (int j = i + 1; j > 0; j--)
                        mpsu_output.train_config[j] = mpsu_output.train_config[j - 1];
            }
        // Добавляем в поезд данный вагон
        mpsu_output.train_size++;
        mpsu_output.pos_in_train = mpsu_output.train_size;
        mpsu_output.train_length += lengthHead;
        mpsu_output.train_config[mpsu_output.pos_in_train - 1] = 1;
        // Обрабатываем сигналы от вагонов сзади
        if (mpsu_output.train_size >= MAX_TRAIN_SIZE)
            return;
        tc = static_cast<int>(mpsu_input.sme_train_config_bwd);
        for (int i = mpsu_output.train_size; i < MAX_TRAIN_SIZE; i++)
        {
            // Сигнал от головных вагонов спереди не меняем (false)
            mpsu_output.train_config[i] = train_config_parsing(tc % SME_MULTIPLIER, false);
            tc = tc / SME_MULTIPLIER;
            if (tc == 0)
                break;
        }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int MPSU::train_config_parsing(int unit, bool bias)
{
    switch (unit)
    {
        case 1:
        {
            mpsu_output.train_size++;
            mpsu_output.train_length += lengthHead;
            return 1 + bias;
        }
        case 2:
        {
            mpsu_output.train_size++;
            mpsu_output.train_length += lengthHead;
            return 2 - bias;
        }
        case 3:
        {
            mpsu_output.train_size++;
            mpsu_output.train_length += lengthMiddle;
            return 3;
        }
        default:
        {
            return 0;
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::start_disels()
{
    if (((mpsu_output.start_press_count == 1) ||
         mpsu_input.start_disel_sme) &&
         (!mpsu_output.is_disel_started))
    {
        startButtonTimer->stop();

        trig_disel_start.set();

        trig_fuel_valve.set();
    }

    mpsu_output.is_disel_started = static_cast<bool>(hs_p(mpsu_input.disel_shaft_freq - 700.0));

    // Команда на включение топливного насоса
    mpsu_output.is_fuel_pump_ON = trig_disel_start.getState();

    // Команда на включение стартера
    mpsu_output.is_starter_ON = static_cast<bool>(hs_p(mpsu_input.fuel_press - 0.1)) &&
            (!mpsu_output.is_disel_started);

    // Подача топлива
    mpsu_output.is_fuel_valve_open = trig_fuel_valve.getState();

    if (mpsu_output.is_disel_started)
            trig_disel_start.reset();

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::stop_disels()
{
    if (mpsu_input.stop_disel || mpsu_input.stop_disel_sme)
    {
        trig_fuel_valve.reset();
        mpsu_output.stop_diesel = true;
        mpsu_output.start_press_count = -1;
    }
    else
        mpsu_output.stop_diesel = false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::check_alarm_level()
{
    switch (mpsu_output.mfdu_disel_state_level)
    {
    case 0:
        mpsu_output.is_red_alarm = false;
        mpsu_output.is_yellow_alarm = false;
        break;

    case 1:
        mpsu_output.is_red_alarm = false;
        mpsu_output.is_yellow_alarm = true;
        break;

    case 2:
        mpsu_output.is_red_alarm = true;
        mpsu_output.is_yellow_alarm = false;
        break;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double MPSU::getTracRefDiselFreq(double trac_level, double brake_level)
{
    double motion_allow = static_cast<double>(!mpsu_output.motion_disable);

    double n_ref = n_min;

    if (!mpsu_output.hydro_brake_ON)
        n_ref = n_min + (n_max - n_min) * (trac_level - mpsu_input.trac_min) * motion_allow / (1.0 - mpsu_input.trac_min);
    else
        n_ref = n_min_gb + (n_max - n_min_gb) * (brake_level - mpsu_input.brake_min) * motion_allow / (1.0 - mpsu_input.brake_min);;

    return cut(n_ref, n_min, n_max);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::check_revers()
{
    mpsu_output.revers_finish = mpsu_input.revers_state;

    if (!mpsu_output.revers_finish)
        return;

    switch (mpsu_input.revers_handle)
    {
    case 1:

        mpsu_output.revers_fwd = true;
        mpsu_output.revers_bwd = false;
        mpsu_output.revers_neutral = false;
        break;

    case 0:

        mpsu_output.revers_fwd = false;
        mpsu_output.revers_bwd = false;
        mpsu_output.revers_neutral = true;
        break;

    case -1:

        mpsu_output.revers_fwd = false;
        mpsu_output.revers_bwd = true;
        mpsu_output.revers_neutral = false;
        break;

    default:

        break;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::check_moition_disable()
{
    if (mpsu_input.is_emergency_brake)
    {
        motion_lock.set();
    }

    if (!mpsu_input.is_emergency_brake && mpsu_input.is_KM_zero)
    {
        motion_lock.reset();
    }

    for (size_t i = 0; i < MAX_TRAIN_SIZE; i++)
    errors[ERROR_ST1 + i] = mpsu_input.unit_spt_state[i] && mpsu_output.is_disel_started;
    errors[ERROR_REVERS_0] = (mpsu_input.revers_handle == 0) && mpsu_output.is_disel_started;
    errors[ERROR_EPK_OFF] = !mpsu_input.is_autostop_ON && mpsu_output.is_disel_started;

    mpsu_output.motion_disable = false;

    for (size_t i = ERROR_ST1; i <= ERROR_EPK_OFF; ++i)
    {
        mpsu_output.motion_disable |= errors[i];
    }

    mpsu_output.motion_disable |= motion_lock.getState();

    // Обработка прочих ошибок
    errors[ERROR_HOLD_SPEED_TRAC] = is_speed_hold_disable && mpsu_input.is_KM_traction;
    errors[ERROR_HOLD_SPEED_BRAKE] = is_speed_hold_disable && mpsu_input.is_KM_brake;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::holding_brake_step()
{
    if (mpsu_output.motion_disable)
    {
        mpsu_output.holding_brake_level = p_HB / mpsu_input.pBC_max;
        mpsu_output.is_holding_braked = true;
        return;
    }

    if (mpsu_input.is_KM_zero)
    {
        if (mpsu_input.v_kmh < v_HB)
        {
            mpsu_output.holding_brake_level = p_HB / mpsu_input.pBC_max;
            mpsu_output.is_holding_braked = true;
        }
        else
        {
            mpsu_output.holding_brake_level = 0.0;
            mpsu_output.is_holding_braked = false;
        }
    }
    else
    {
        mpsu_output.holding_brake_level = 0.0;
        mpsu_output.is_holding_braked = false;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::output_error_msg()
{
    // Если КМ в нуле
    if (mpsu_input.is_KM_zero)
    {
        // Проверяем последнюю ошибку - если исправлена
        // то гасим транспарант
        if (!errors[mpsu_output.error_code])
        {
            mpsu_output.error_code = ERROR_NONE;
        }

        // и пока ничего не проверяем
        return;
    }

    if (!mpsu_input.is_KM_traction)
        return;

    // Проверяем все флаги ошибок
    for (size_t i = 0; i < errors.size(); ++i)
    {
        // Выводим транспарант
        if (errors[i])
        {
            mpsu_output.error_code = i;
            break;
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::calc_brake_level_PB()
{
    mpsu_output.pBC_max = 0.0;
    mpsu_output.pBC_min = mpsu_input.pBC_max;
    mpsu_output.brake_level_PB = 0.0;

    for (size_t i = 0; i < static_cast<size_t>(mpsu_output.train_size) * 2; ++i)
    {
        if (mpsu_input.unit_pBC[i] > mpsu_output.pBC_max)
        {
            mpsu_output.pBC_max = mpsu_input.unit_pBC[i];
        }

        if (mpsu_input.unit_pBC[i] < mpsu_output.pBC_min)
        {
            mpsu_output.pBC_min = mpsu_input.unit_pBC[i];
        }
    }

    mpsu_output.brake_level_PB = mpsu_output.pBC_min / mpsu_input.pBC_max;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::hydro_brake_control()
{
    // Блокируем питание КЭБ если не собираемся тормозить
    if ( (!mpsu_input.is_KM_brake) && (!mpsu_output.is_speed_hold_ON) )
    {
        mpsu_output.release_PB = false;
        mpsu_output.hydro_brake_ON = false;
        return;
    }

    // Блокируем питание КЭБ при экстренном торможении
    if (mpsu_input.is_emergency_brake)
    {
        mpsu_output.release_PB = false;
        mpsu_output.hydro_brake_ON = false;
        return;
    }

    // При скорости ниже 30 км/ч отключаем ГДТ безусловно и замещаем его
    if (mpsu_input.v_kmh < 30)
    {
        mpsu_output.release_PB = false;
        mpsu_output.hydro_brake_ON = false;
        return;
    }

    // Пытаемся включить ГДТ
    mpsu_output.hydro_brake_ON = (mpsu_input.is_KM_brake) || (mpsu_output.auto_brake_level >= 0.01);

    // Расчитываем максимальное усилие, обеспечиваемое ГДТ
    double B_gb_max = mpsu_input.M_gb_max * mpsu_input.ip * 2.0 / mpsu_input.wheel_diam;

    // Расчитываем фактическое усилие, обеспечиваемое ГДТ
    double B_gb = mpsu_input.M_gb * mpsu_input.ip * 2.0 / mpsu_input.wheel_diam;

    // Рассчитываем потребное усилие, заданное от КМ или регулятора скорости
    double B_ref = (mpsu_input.brake_level_KM + mpsu_output.auto_brake_level) * calcMaxBrakeForce(qAbs(mpsu_input.v_kmh));

    // Определяем задание ГДТ, пытаемся реализовать заданное усилие за счет применения ГДТ
    mpsu_output.brake_ref_level_GB = cut(B_ref / B_gb_max, 0.0, 1.0);
    // Определяем добавку по ЭПТ, если эффективности ГДТ не достаточно
    mpsu_output.brake_ref_level_EPB = cut( (B_ref - B_gb) / B_ref, 0.0, mpsu_output.brake_level);

    // Формируем сигнал "отпуск ПТ" на моторную тележку при работе ГДТ
    mpsu_output.release_PB = (mpsu_input.M_gb > Physics::ZERO);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::unit_brakes_sheck()
{
    // Тип тормоза повагонно для вывода на дисплей МФДУ
    for (size_t i = 0; i < MAX_TRAIN_SIZE; i++)
    {
        // По умолчанию погашен
        mpsu_output.unit_brakes[i] = 0;
        // Экстренное или включен СПТ - красный
        if (mpsu_input.is_emergency_brake || mpsu_input.unit_spt_state[i])
        {
            mpsu_output.unit_brakes[i] = 4;
            continue;
        }
        if ((mpsu_input.unit_pBC[2 * i] > 0.04) || (mpsu_input.unit_pBC[2 * i + 1] > 0.04))
        {
            // Совмещённое ГДТ + пневматика - белый
            if (mpsu_input.unit_level_GDB[i] > 0.01)
            {
                mpsu_output.unit_brakes[i] = 2;
                continue;
            }
            // Только пневматика - жёлтый
            else
            {
                mpsu_output.unit_brakes[i] = 3;
                continue;
            }
        }
        // Только ГДТ - синий
        if (mpsu_input.unit_level_GDB[i] > 0.01)
            mpsu_output.unit_brakes[i] = 1;
    }

    // Сигнал отпуска тормозов на всех тележках кроме последней
    mpsu_output.sot = true;
    for (int i = 0; i < mpsu_output.train_size * 2 - 1; i++)
        mpsu_output.sot &= (mpsu_input.unit_pBC[i] < 0.04);
    // Сигнал отпуска тормозов на последней тележке
    mpsu_output.soth = (mpsu_input.unit_pBC[mpsu_output.train_size * 2 - 1] < 0.04);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double MPSU::calcMaxBrakeForce(double V)
{
    double Bmax = 0;

    int shoes_num = 8;

    double K = mpsu_input.Kmax;

    Bmax = shoes_num * 1000.0 * Physics::g * K * 0.44 * (K + 20) * (V + 150) / (4 * K + 20) / (2 * V + 150);

    return Bmax;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::slotStartButtonTimer()
{
    stop_disels();
    startButtonTimer->stop();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int MPSU::check_disels_oil_pressure(double p_oil)
{
    int mfdu_oil_press_level = 1;

    // Анализируем уровень давления с выдачей сигнала в МФДУ
    if (p_oil < 0.1)
        mfdu_oil_press_level = 1;

    if ( (p_oil >= 0.1) && (p_oil < 0.15) )
        mfdu_oil_press_level = 0;

    if (p_oil >= 0.15)
        mfdu_oil_press_level = 2;

    return mfdu_oil_press_level;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int MPSU::check_disels(int mfdu_oil_press_level)
{
    // Контроль по маслу
    int oil_level = 2;

    switch (mfdu_oil_press_level)
    {
    case 0:
        oil_level = 1;
        break;

    case 1:
        oil_level = 2;
        break;

    case 2:
        oil_level = 0;
        break;

    default:
        oil_level = 2;
        break;
    }

    return oil_level;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::check_disels_oil_pressure()
{
    mpsu_output.mfdu_oil_press_level = check_disels_oil_pressure(mpsu_input.oil_press);

    // Контроль дизелей по всем параметрам
    mpsu_output.mfdu_disel_state_level = check_disels(mpsu_output.mfdu_oil_press_level);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::hold_speed_buttons_process()
{
    // Если не нажата кнопка влючения режима - нечего и делать
    if (!mpsu_input.button_speed_hold)
    {
        mpsu_output.is_speed_hold_ON = false;
        is_speed_hold_disable = false;
        mpsu_output.v_ref_kmh = 0;
        return;
    }

    // Обрабатываем возможность включения режима

    // Если контроллер машиниста в нуле
    if ( (mpsu_input.is_KM_zero) && (qRound(mpsu_input.v_kmh) >= 1) )
    {
        mpsu_output.is_speed_hold_ON = true;
        is_speed_hold_disable = false;
    }
    else
    {
        // Невозможно включить режим, отменяем его включение
        mpsu_output.is_speed_hold_ON = false;
        is_speed_hold_disable = true;
        return;
    }

    // Не обрабатываем кнопри при выключенном режиме
    if (!mpsu_output.is_speed_hold_ON)
    {
        button_select_old = false;
        button_speed_plus_old = false;
        button_speed_minus_old = false;
        return;
    }

    // Фиксация заданной скорости
    if ( (mpsu_input.button_speed_select) && (!button_select_old) )
    {
        if (qRound(mpsu_input.v_kmh) >= 1)
            mpsu_output.v_ref_kmh = mpsu_input.v_kmh;
    }

    // Увеличение заданной скорости
    if ( (mpsu_input.button_speed_plus) && (!button_speed_plus_old) )
    {
        mpsu_output.v_ref_kmh++;
    }

    // Уменьшение заданной скорости
    if ( (mpsu_input.button_speed_minus) && (!button_speed_minus_old) )
    {
        mpsu_output.v_ref_kmh--;
    }

    mpsu_output.v_ref_kmh = cut(mpsu_output.v_ref_kmh, 0, 120);

    button_select_old = mpsu_input.button_speed_select;
    button_speed_plus_old = mpsu_input.button_speed_plus;
    button_speed_minus_old = mpsu_input.button_speed_minus;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::speed_regulator()
{
    mpsu_output.trac_level = mpsu_input.trac_level_KM + mpsu_output.auto_trac_level;
    mpsu_output.brake_level = mpsu_input.brake_level_KM + mpsu_output.auto_brake_level;

    // Если не включен режим поддержания скорости - выдаем нулевое задание
    // Если задана нулевая скорость - действуем аналогично
    if ( (!mpsu_output.is_speed_hold_ON) || (mpsu_output.v_ref_kmh == 0) )
    {
        mpsu_output.auto_trac_level = mpsu_output.auto_brake_level = 0;
        return;
    }

    // Вычисляем ошибку по скорости
    dv = static_cast<double>(mpsu_output.v_ref_kmh) - mpsu_input.v_kmh;

    // Формируем управление
    u = cut(Kp * dv + getY(0), -1.0, 1.0);

    mpsu_output.auto_trac_level = pf(getY(1));
    mpsu_output.auto_brake_level = nf(getY(1));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::main_loop_step(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    // Включение дисплея
    mpsu_output.is_display_ON = true;

    // Обработка конфигурации СМЕ
    train_config_process();

    // Обработка кнопки "СТАРТ"
    start_button_process(mpsu_input.start_disel);

    // Запуск дизелей
    start_disels();

    // Останов дизелей
    stop_disels();

    // Контроль давления масла дизелей
    check_disels_oil_pressure();

    // Контроль сигналов "ТРЕВОГА"
    check_alarm_level();

    mpsu_output.n_ref = getTracRefDiselFreq(mpsu_input.trac_level_KM + mpsu_output.auto_trac_level,
                                            mpsu_input.brake_level_KM + mpsu_output.auto_brake_level);

    check_revers();

    // Проверка запрета движения
    check_moition_disable();

    // Управление удерживающим тормозом
    holding_brake_step();

    // Выбор уровня наполнения ТЦ между фактически заданным от КМ и уровнем
    // удерживающего тормоза
    mpsu_output.brake_ref_level_EPB = max(mpsu_input.brake_level_KM, mpsu_output.holding_brake_level);

    // Обработка ошибок
    output_error_msg();

    // Состояние СПТ
    mpsu_output.spt_state = false;
    for (size_t i = 0; i < MAX_TRAIN_SIZE; i++)
        mpsu_output.spt_state |= mpsu_input.unit_spt_state[i];

    // Тип торможения повагонно
    unit_brakes_sheck();

    // Анализ давлений в тормозных цилиндрах
    calc_brake_level_PB();

    // Управление гидродинамическим торможением
    hydro_brake_control();

    // Обработка кнопок ПУ-4 по режиму поддержания скорости
    hold_speed_buttons_process();

    // Регулятор скорости
    speed_regulator();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::start_button_process(bool is_start_button)
{
    // Блокировка пуска дизеля при ненулевом положении КМ
    if ( (!mpsu_input.is_KM_zero) && (!mpsu_output.is_disel_started) )
    {
        return;
    }

    // Обработка нажатия исключительно после того, как кнопка была отпущена
    if (is_start_button && (!old_start_state) )
    {
        // Засекаем время до второго нажатия
        if (!startButtonTimer->isStarted())
             startButtonTimer->start();

        // Считаем нажатия
        mpsu_output.start_press_count++;

        mpsu_output.start_press_count = cut(mpsu_output.start_press_count, 0, 1);
    }

    // Запоминаем предыдущее состояние кнопки
    old_start_state = is_start_button;
}
