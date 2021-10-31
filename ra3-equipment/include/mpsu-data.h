#ifndef     MPSU_DATA_H
#define     MPSU_DATA_H

#include    <array>

enum
{
    ERRORS_NUM = 100,
    ERROR_NONE = 0,
    ERROR_ST1 = 1,
    ERROR_ST2 = 2,
    ERROR_REVERS_0 = 3,
    ERROR_EPK_OFF = 4
};

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
    double trac_level_KM;

    /// Уровень тормозного усилия от контроллера машиниста
    double brake_level_KM;

    double trac_min;

    double brake_min;

    /// Реверсирование ведущей секции
    int revers_state1;

    /// Реверсирование ведомой секции
    int revers_state2;

    /// Состояние блок-контакта ЭПК
    bool is_autostop_ON;

    /// Состояние реверсивной рукоятки
    int revers_handle;

    /// Состояние СПТ на 1 вагоне
    bool is_parking_braked1;

    /// Сщстояние СПТ на 2 вагоне
    bool is_parking_braked2;

    /// Скорость поезда (км/ч)
    double v_kmh;

    /// Признак нулевого положения КМ
    bool is_KM_zero;

    /// Признак тягового положения КМ
    bool is_KM_traction;

    /// Максимальное давление в ТЦ от БТО
    double pBC_max;    

    /// Признак тормозного положения КМ
    bool is_KM_brake;

    /// Фактический уровень тормозного усилия от ГДТ на вагоне 1
    double brake_level_GB1;

    /// Фактический уровень тормозного усилия от ГДТ на вагоне 2
    double brake_level_GB2;

    /// Максимальное действительное нажатие на колодку
    double Kmax;

    /// Диаметр колеса по кругу катания
    double wheel_diam;

    /// Передаточное число редукторов
    double ip;

    /// Момент от ГДТ
    double M_gb;

    /// Максимальный момент от ГДТ
    double M_gb_max;

    /// Признак экстренного торможения
    bool is_emergency_brake;

    enum
    {
        NUM_AXIS = 4
    };

    /// Давления в ТЦ по всем тележкам поезда
    std::array<double, NUM_AXIS> pBC;

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
        , trac_level_KM(0.0)
        , brake_level_KM(0.0)
        , trac_min(0.17)
        , brake_min(0.26)
        , revers_state1(0)
        , revers_state2(0)
        , is_autostop_ON(false)
        , revers_handle(0)
        , is_parking_braked1(false)
        , is_parking_braked2(false)
        , v_kmh(0)
        , is_KM_zero(false)
        , is_KM_traction(false)
        , pBC_max(0.38)
        , is_KM_brake(false)
        , brake_level_GB1(0)
        , brake_level_GB2(0)
        , Kmax(0)
        , wheel_diam(0.86)
        , ip(3.32)
        , M_gb(0)
        , M_gb_max(0)
        , is_emergency_brake(false)
    {
        std::fill(pBC.begin(), pBC.end(), 0.0);
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

    /// Заданный уровень давления в тормозных цилиндрах
    /// при работе удерживающего тормоза
    double holding_brake_level;

    /// Признак наботы удерживающего тормоза
    bool is_holding_braked;

    /// Состояние стояночного тормоза
    bool is_parking_braked;

    /// Код ошибки
    int error_code;

    /// Сигнал наполнения ГДТ на 1 вагоне
    bool hydro_brake_ON1;

    /// Сигнал наполнения ГДТ на 2 вагоне
    bool hydro_brake_ON2;

    /// Сигнал отпуска пневматического тормоза (через КЭБ) на 1 вагоне
    bool release_PB1;

    /// Сигнал отпуска пневматического тормоза (через КЭБ) на 2 вагоне
    bool release_PB2;

    /// Максимальное давление в ТЦ
    double pBC_max;

    /// Минимальное давление в ТЦ
    double pBC_min;

    /// Фактический уровень торможения ПТ/ЭПТ
    double brake_level_PB;

    /// Заданный уровень торможения ЭПТ
    double brake_ref_level_EPB;

    /// Заданные уровень торможения ГДТ
    double brake_ref_level_GB;

    /// Тип активного торможения на первом вагоне
    int brake_type1;

    /// Тип активного торможения на втором вагоне
    int brake_type2;

    /// Общий уровен развиваемого тормозного усилия
    double brake_level;

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
        , holding_brake_level(0.0)
        , is_holding_braked(false)
        , is_parking_braked(false)
        , error_code(ERROR_NONE)
        , hydro_brake_ON1(false)
        , hydro_brake_ON2(false)
        , release_PB1(false)
        , release_PB2(false)
        , pBC_max(0)
        , pBC_min(0)
        , brake_level_PB(0)
        , brake_ref_level_EPB(0)
        , brake_ref_level_GB(0)
        , brake_type1(2)
        , brake_type2(2)
        , brake_level(0)
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
