#include    "mpsu.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MPSU::MPSU(QObject *parent) : Device(parent)
  , is_reseted(false)
  , old_start_state(false)
  , n_min(800)
  , n_max(1800)
  , v_HB(1.0)
  , p_HB(0.15)
{

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
    Device::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::setInputData(const mpsu_input_t &mpsu_input)
{
    this->mpsu_input = mpsu_input;
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
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
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

    for (size_t i = 0; i < trig_disel_start.size(); ++i)
        trig_disel_start[i].reset();

    is_reseted = true;

    std::fill(errors.begin(), errors.end(), false);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::start_disels()
{
    mpsu_output.is_disel1_started = static_cast<bool>(hs_p(mpsu_input.disel1_shaft_freq - 700.0));
    // Признак запуска дизеля 2
    mpsu_output.is_disel2_started = static_cast<bool>(hs_p(mpsu_input.disel2_shaft_freq - 700.0));

    // Команды на включение топливных насосов
    mpsu_output.is_fuel_pump1_ON = trig_disel_start[FWD_DISEL].getState();
    mpsu_output.is_fuel_pump2_ON = trig_disel_start[BWD_DISEL].getState();

    // Команды на включение стартеров
    mpsu_output.is_starter1_ON = static_cast<bool>(hs_p(mpsu_input.fuel_press1 - 0.1)) &&
            (!mpsu_output.is_disel1_started);

    mpsu_output.is_starter2_ON = static_cast<bool>(hs_p(mpsu_input.fuel_press2 - 0.1)) &&
            (!mpsu_output.is_disel2_started);

    if (mpsu_output.is_disel1_started)
            trig_disel_start[FWD_DISEL].reset();

    if (mpsu_output.is_disel2_started)
            trig_disel_start[BWD_DISEL].reset();

    mpsu_output.is_fuel_valve1_open = trig_fuel_valve[FWD_DISEL].getState();
    mpsu_output.is_fuel_valve2_open = trig_fuel_valve[BWD_DISEL].getState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::stop_disels()
{
    if (mpsu_input.stop_disel)
    {
        trig_fuel_valve[FWD_DISEL].reset();
        trig_fuel_valve[BWD_DISEL].reset();
        mpsu_output.current_started_disel = -1;
    }
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
double MPSU::getTracRefDiselFreq(double trac_level)
{
    double motion_allow = static_cast<double>(!mpsu_output.motion_disable);

    double n_ref = n_min + (n_max - n_min) * (trac_level - mpsu_input.trac_min) * motion_allow / (1.0 - mpsu_input.trac_min);

    return cut(n_ref, n_min, n_max);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::check_revers()
{
    mpsu_output.revers_finish = mpsu_input.revers_state1 == mpsu_input.revers_state2;

    if (!mpsu_output.revers_finish)
        return;

    switch (mpsu_input.revers_state1)
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
    errors[ERROR_ST1] = mpsu_input.is_parking_braked1;
    errors[ERROR_ST2] = mpsu_input.is_parking_braked2;
    errors[ERROR_REVERS_0] = mpsu_input.revers_handle == 0;
    errors[ERROR_EPK_OFF] = !mpsu_input.is_autostop_ON;

    mpsu_output.motion_disable = false;

    for (bool error : errors)
    {
        mpsu_output.motion_disable |= error;
    }
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

    for (double pBC : mpsu_input.pBC)
    {
        if (pBC > mpsu_output.pBC_max)
        {
            mpsu_output.pBC_max = pBC;
        }

        if (pBC < mpsu_output.pBC_min)
        {
            mpsu_output.pBC_min = pBC;
        }
    }

    mpsu_output.brake_level_PB = mpsu_output.pBC_min / mpsu_input.pBC_max;
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
void MPSU::main_loop_step(double t, double dt)
{
    // Включение дисплея
    mpsu_output.is_display_ON = true;

    // Обработка кнопки "СТАРТ"
    start_button_process(mpsu_input.start_disel);

    // Запуск дизелей
    start_disels();

    // Останов дизелей
    stop_disels();

    // Контроль давления масла дизелей
    mpsu_output.mfdu_oil_press_level1 = check_disels_oil_pressure(mpsu_input.oil_press1);
    mpsu_output.mfdu_oil_press_level2 = check_disels_oil_pressure(mpsu_input.oil_press2);

    double p_oil = min(mpsu_input.oil_press1, mpsu_input.oil_press2);
    mpsu_output.mfdu_oil_press_level = check_disels_oil_pressure(p_oil);

    // Контроль дизелей по всем параметрам
    mpsu_output.mfdu_disel_state_level1 = check_disels(mpsu_output.mfdu_oil_press_level1);
    mpsu_output.mfdu_disel_state_level2 = check_disels(mpsu_output.mfdu_oil_press_level2);

    mpsu_output.mfdu_disel_state_level = max(mpsu_output.mfdu_disel_state_level1,
                                             mpsu_output.mfdu_disel_state_level2);

    check_alarm_level();

    mpsu_output.n_ref = getTracRefDiselFreq(mpsu_input.trac_level_KM);

    check_revers();

    // Проверка запрета движения
    check_moition_disable();

    // Управление удерживающим тормозом
    holding_brake_step();

    // Обработка ошибок
    output_error_msg();

    mpsu_output.is_parking_braked = mpsu_input.is_parking_braked1 &&
                                    mpsu_input.is_parking_braked2;

    calc_brake_level_PB();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MPSU::start_button_process(bool is_start_button)
{
    // Обработка нажатия исключительно после того, как кнопка была отпущена
    if (is_start_button && (!old_start_state) )
    {
        // Выбираем дизель
        mpsu_output.current_started_disel++;
        // "Режем" индекс
        mpsu_output.current_started_disel = cut(mpsu_output.current_started_disel,
                                                0,
                                                static_cast<int>(NUM_DISELS) - 1);

        // Взводим триггер признака пуска
        trig_disel_start[mpsu_output.current_started_disel].set();

        // Взводим триггер топливного клапана
        trig_fuel_valve[mpsu_output.current_started_disel].set();
    }

    // Запоминаем предыдущее состояние кнопки
    old_start_state = is_start_button;
}
