#ifndef     MPSU_DATA_H
#define     MPSU_DATA_H

#include    <array>

#include    <ra3-sme-signals.h>

enum
{
    ERRORS_NUM = 100,
    ERROR_NONE = 0,
    ERROR_ST1 = 1,
    ERROR_ST2 = 2,
    ERROR_ST3 = 3,
    ERROR_ST4 = 4,
    ERROR_ST5 = 5,
    ERROR_ST6 = 6,
    ERROR_REVERS_0 = 7,
    ERROR_EPK_OFF = 8,
    ERROR_HOLD_SPEED_TRAC = 9,
    ERROR_HOLD_SPEED_BRAKE = 10
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct mpsu_input_t
{
    /// Признак подачи питания на МПСУ
    bool is_power_on;

    /// Сигнал опроса конфигурации СМЕ спереди
    float sme_train_config_fwd;
    /// Сигнал опроса конфигурации СМЕ сзади
    float sme_train_config_bwd;

    /// Состояние кнопки "ПУСК"
    bool start_disel;
    /// Состояние кнопки "СТОП"
    bool stop_disel;

    /// Сигнал СМЕ запуска дизелей
    bool start_disel_sme;
    /// Сигнал СМЕ запуска дизелей
    bool stop_disel_sme;

    /// Давление масла в дизеле 1
    double oil_press;
    /// Давление топлива в рампе ТНВД1
    double fuel_press;
    /// Обороты дизеля
    double disel_shaft_freq;

    /// Уровень тяги от контроллера машиниста
    double trac_level_KM;

    /// Уровень тормозного усилия от контроллера машиниста
    double brake_level_KM;

    double trac_min;

    double brake_min;

    /// Реверсирование гидропередачи
    int revers_state;

    /// Состояние блок-контакта ЭПК
    bool is_autostop_ON;

    /// Состояние реверсивной рукоятки
    int revers_handle;

    /// Скорость поезда (км/ч)
    double v_kmh;

    /// Признак нулевого положения КМ
    bool is_KM_zero;

    /// Признак тягового положения КМ
    bool is_KM_traction;

    /// Признак тормозного положения КМ
    bool is_KM_brake;

    /// Максимальное давление в ТЦ от БТО
    double pBC_max;

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

    /// Состояние кнопки "Поддержание скорости"
    bool button_speed_hold;

    /// Состояние кнопки "Выбор скорости"
    bool button_speed_select;

    /// Состояние кнопки "Скорость +"
    bool button_speed_plus;

    /// Состояние кнопки "Скорость -"
    bool button_speed_minus;

    enum
    {
        NUM_BOGIES = 2
    };

    /// Фактический уровень тормозного усилия от ГДТ по вагонам
    std::array<double, MAX_TRAIN_SIZE> unit_level_GDB;

    /// Давления в ТЦ по всем тележкам поезда
    std::array<double, NUM_BOGIES * MAX_TRAIN_SIZE> unit_pBC;

    /// Состояние стояночного пружинного тормоза по вагонам
    std::array<bool, MAX_TRAIN_SIZE> unit_spt_state;

    mpsu_input_t()
        : is_power_on(false)
        , sme_train_config_fwd(0.0f)
        , sme_train_config_bwd(0.0f)
        , start_disel(false)
        , stop_disel(false)
        , start_disel_sme(false)
        , oil_press(0.0)
        , fuel_press(0.0)
        , disel_shaft_freq(0.0)
        , trac_level_KM(0.0)
        , brake_level_KM(0.0)
        , trac_min(0.17)
        , brake_min(0.26)
        , revers_state(0)
        , is_autostop_ON(false)
        , revers_handle(0)
        , v_kmh(0)
        , is_KM_zero(false)
        , is_KM_traction(false)
        , is_KM_brake(false)
        , pBC_max(0.38)
        , Kmax(0)
        , wheel_diam(0.86)
        , ip(3.32)
        , M_gb(0)
        , M_gb_max(0)
        , is_emergency_brake(false)
        , button_speed_hold(false)
        , button_speed_select(false)
        , button_speed_plus(false)
        , button_speed_minus(false)
    {
        std::fill(unit_level_GDB.begin(), unit_level_GDB.end(), 0.0);
        std::fill(unit_pBC.begin(), unit_pBC.end(), 0.0);
        std::fill(unit_spt_state.begin(), unit_spt_state.end(), false);
    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct mpsu_output_t
{
    /// Номер по порядку данного вагона в поезде
    int pos_in_train;

    /// Количество вагонов в конфигурации СМЕ
    int train_size;

    /// Длина поезда для БЛОК
    double train_length;

    /// Конфигурация поезда для МФДУ
    std::array<int, MAX_TRAIN_SIZE> train_config;

    /// Включение дисплея МПСУ
    bool is_display_ON;

    /// Счетчик нажатий кнопки "СТАРТ"
    int  start_press_count;

    /// Работа дизеля
    bool is_disel_started;

    /// Включение контактора топливного насоса
    bool is_fuel_pump_ON;

    /// Включение стартера
    bool is_starter_ON;

    /// Сигнал открытия клапана питания дизеля топливом
    bool is_fuel_valve_open;

    /// Сигнал остановки дизеля
    bool stop_diesel;

    /// Сигнал "Реверс: ВПЕРЕД"
    bool revers_fwd;

    /// Сигнал "Реверс: НАЗАД"
    bool revers_bwd;

    /// Сигнал "Реверс: НЕЙТРАЛЬ"
    bool revers_neutral;

    /// Уровень давления масла в дизеле для МФДУ
    int mfdu_oil_press_level;

    /// Желтая тревога
    bool is_yellow_alarm;

    /// Красная тревога
    bool is_red_alarm;

    /// Состояние дизелей
    int mfdu_disel_state_level;

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
    bool spt_state;

    /// Код ошибки
    int error_code;

    /// Сигнал наполнения ГДТ
    bool hydro_brake_ON;

    /// Сигнал отпуска пневматического тормоза (через КЭБ)
    bool release_PB;

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

    /// Общий уровень тягового усилия
    double trac_level;

    /// Общий уровень развиваемого тормозного усилия
    double brake_level;

    /// Тип торможения повагонно
    std::array<int, MAX_TRAIN_SIZE> unit_brakes;

    /// Сигнал отпуска тормозов кроме последней тележки
    bool sot;
    /// Сигнал отпуска тормозов последней тележки
    bool soth;

    /// Заданная для поддержания скорость (км/ч)
    int v_ref_kmh;

    /// Заданна тяга от регулятора скорости
    double auto_trac_level;

    /// Заданное тормозное усилие от регулятора скорости
    double auto_brake_level;

    /// Признак включения режима поддержания скорости
    bool is_speed_hold_ON;

    mpsu_output_t()
        : pos_in_train(1)
        , train_size(2)
        , train_length(48.48)
        , train_config({1, 2, 0, 0, 0, 0})
        , is_display_ON(false)
        , start_press_count(-1)
        , is_disel_started(false)
        , is_fuel_pump_ON(false)
        , is_starter_ON(false)
        , is_fuel_valve_open(false)
        , stop_diesel(false)
        , revers_fwd(false)
        , revers_bwd(false)
        , revers_neutral(true)
        , mfdu_oil_press_level(1)
        , is_yellow_alarm(false)
        , is_red_alarm(false)
        , mfdu_disel_state_level(2)
        , n_ref(800)
        , revers_finish(true)
        , motion_disable(true)
        , holding_brake_level(0.0)
        , is_holding_braked(false)
        , spt_state(false)
        , error_code(ERROR_NONE)
        , hydro_brake_ON(false)
        , release_PB(false)
        , pBC_max(0)
        , pBC_min(0)
        , brake_level_PB(0)
        , brake_ref_level_EPB(0)
        , brake_ref_level_GB(0)
        , brake_level(0)
        , sot(false)
        , soth (false)
        , v_ref_kmh(0)
        , auto_trac_level(0)
        , auto_brake_level(0)
        , is_speed_hold_ON(false)
    {
        std::fill(unit_brakes.begin(), unit_brakes.end(), 0);
    }

    int getReversorDir() const
    {
        return static_cast<int>(!revers_fwd) -
               static_cast<int>(!revers_bwd);
    }
};

#endif // MPSU_DATA_H
