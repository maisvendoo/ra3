#include    "mpsu.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MPSU::MPSU(QObject *parent) : Device(parent)
  , is_reseted(false)
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

    // Признак запуска дизеля 1
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
    }

    // Запоминаем предыдущее состояние кнопки
    old_start_state = is_start_button;
}
