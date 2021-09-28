#ifndef     MPSU_DATA_H
#define     MPSU_DATA_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct mpsu_input_t
{
    /// Признак подачи питания на МПСУ
    bool is_power_on;

    /// Состояние кнопки "ПУСК"
    bool start_disel;
    /// Состояние кнопки "СТОП"
    bool stop_disel;

    mpsu_input_t()
        : is_power_on(false)
        , start_disel(false)
        , stop_disel(false)
    {

    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct mpsu_output_t
{
    bool is_fuel_pump_ON;

    mpsu_output_t()
        : is_fuel_pump_ON(false)
    {

    }
};

#endif // MPSU_DATA_H
