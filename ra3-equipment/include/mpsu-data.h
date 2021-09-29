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

    /// Давление масла в дизеле 1
    double oil_press1;
    /// Давление масла в дизеле 2
    double oil_press2;

    /// Давление топлива в рампе ТНВД1
    double fuel_press1;

    /// Давление топлива в рампе ТНВД2
    double fuel_press2;

    mpsu_input_t()
        : is_power_on(false)
        , start_disel(false)
        , stop_disel(false)
        , oil_press1(0.0)
        , oil_press2(0.0)
        , fuel_press1(0.0)
        , fuel_press2(0.0)
    {

    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct mpsu_output_t
{
    /// Включение контактора топливного насоса в ведущей секции
    bool is_fuel_pump1_ON;
    /// Включение контактора топливного насоса в ведомой секции
    bool is_fuel_pump2_ON;

    /// Включение дисплея МПСУ
    bool is_display_ON;

    /// Текущий дизель для запуска
    int  current_started_disel;

    mpsu_output_t()
        : is_fuel_pump1_ON(false)
        , is_fuel_pump2_ON(false)
        , is_display_ON(false)
        , current_started_disel(-1)
    {

    }
};

#endif // MPSU_DATA_H
