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

    /// Обороты дизеля 1
    double disel1_shaft_freq;

    /// Обороты дизеля 2
    double disel2_shaft_freq;

    /// Уровень тяги от контроллера машиниста
    double trac_level;

    /// Уровень тормозного усилия от контроллера машиниста
    double brake_level;

    double trac_min;

    double brake_min;

    /// Реверсирование ведущей секции
    int revers_state1;

    /// Реверсирование ведомой секции
    int revers_state2;

    mpsu_input_t()
        : is_power_on(false)
        , start_disel(false)
        , stop_disel(false)
        , oil_press1(0.0)
        , oil_press2(0.0)
        , fuel_press1(0.0)
        , fuel_press2(0.0)
        , disel1_shaft_freq(0.0)
        , disel2_shaft_freq(0.0)
        , trac_level(0.0)
        , brake_level(0.0)
        , trac_min(0.17)
        , brake_min(0.26)
        , revers_state1(0)
        , revers_state2(0)
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

    /// Включение стартера на дизель 1
    bool is_starter1_ON;

    /// Включение стартера на дизель 2
    bool is_starter2_ON;

    /// Работа дизеля 1
    bool is_disel1_started;

    /// Работа дизеля 2
    bool is_disel2_started;

    /// Сигнал открытия клапана питания дизеля 1 топливом
    bool is_fuel_valve1_open;

    /// Сигнал открытия клапана питания дизеля 2 топливом
    bool is_fuel_valve2_open;

    /// Сигнал "Реверс: ВПЕРЕД"
    bool revers_fwd;

    /// Сигнал "Реверс: НАЗАД"
    bool revers_bwd;

    /// Сигнал "Реверс: НЕЙТРАЛЬ"
    bool revers_neutral;

    /// Уровень давления масла в дизеле для МФДУ
    int mfdu_oil_press_level;

    int mfdu_oil_press_level1;
    int mfdu_oil_press_level2;

    /// Желтая тревога
    bool is_yellow_alarm;

    /// Красная тревога
    bool is_red_alarm;

    /// Состояние дизелей
    int mfdu_disel_state_level;

    int mfdu_disel_state_level1;
    int mfdu_disel_state_level2;

    /// Заданные обороты дизеля
    double n_ref;

    /// Признак завершения реверсирования ГДП
    bool revers_finish;

    /// Запрет движения
    bool motion_disable;

    mpsu_output_t()
        : is_fuel_pump1_ON(false)
        , is_fuel_pump2_ON(false)
        , is_display_ON(false)
        , current_started_disel(-1)
        , is_starter1_ON(false)
        , is_starter2_ON(false)
        , is_disel1_started(false)
        , is_disel2_started(false)
        , is_fuel_valve1_open(false)
        , is_fuel_valve2_open(false)
        , revers_fwd(false)
        , revers_bwd(false)
        , revers_neutral(true)
        , mfdu_oil_press_level(1)
        , mfdu_oil_press_level1(1)
        , mfdu_oil_press_level2(1)
        , is_yellow_alarm(false)
        , is_red_alarm(false)
        , mfdu_disel_state_level(2)
        , mfdu_disel_state_level1(2)
        , mfdu_disel_state_level2(2)
        , n_ref(800)
        , revers_finish(true)
        , motion_disable(true)
    {

    }

    bool is_disel_started() const
    {
        return is_disel1_started || is_disel2_started;
    }

    int getReversorDir() const
    {
        return static_cast<int>(!revers_fwd) -
               static_cast<int>(!revers_bwd);
    }
};

#endif // MPSU_DATA_H
