#ifndef     RA3_SME_SIGNALS_H
#define     RA3_SME_SIGNALS_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    /// Количество сигналов в соединениях СМЕ
    NUM_RA3_SME_SIGNALS = 100,

    /// наибольшее число вагонов в СМЕ
    MAX_TRAIN_SIZE = 6,
    /// множитель накопительного сигнала конфигурации
    SME_MULTIPLIER = 4,
    /// ограничение накопительного сигнала конфигурации
    SME_LIMIT = 256,
    /// головной вагон, сигнал вперёд
    SME_HEAD_FWD = 1,
    /// головной вагон, сигнал назад
    SME_HEAD_BWD = 2,
    /// промежуточный вагон любой ориентации
    SME_MIDDLE = 3,
    /// активная кабина
    SME_ACTIVE = -1,

    /// начало массива сигналов СМЕ от активной кабины
    SME_ACTIVE_BEGIN = 10,
    /// размер массива сигналов СМЕ от активной кабины
    SME_ACTIVE_SIZE = 15,
    /// начало массива сигналов СМЕ от вагонов
    SME_UNIT_STATE_BEGIN = SME_ACTIVE_BEGIN + SME_ACTIVE_SIZE,
    /// размер массива сигналов СМЕ от вагонов
    SME_UNIT_STATE_SIZE = 15,
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    /// Сигнал управления соединением СМЕ
    SME_OUTPUT_REF_STATE = 0,
    /// Сигнал состояния соединения СМЕ
    SME_INPUT_IS_CONNECTED = 0,

    /// Сигнал опроса конфигурации поезда
    SME_TRAIN_CONFIG = 1,

    // Общие сигналы для межвагонных связей
    SME_CHARGE_VOLTAGE = 2,     ///< Напряжение бортовой сети
    SME_CHARGE_CURRENT = 3,     ///< Потребляемый ток из бортовой сети

    // Общие сигналы с ведущей секции
    SME_NO_ACTIVE = SME_ACTIVE_BEGIN,   ///< Сигнал запрета включать другие кабины
    SME_POWER_ON,               ///< Сигнал включения бортсети
    SME_DISEL_START,            ///< Сигнал включения дизеля
    SME_DISEL_STOP,             ///< Сигнал выключения дизеля
    SME_IS_AUTOSTOP_ON,         ///< Сигнал наличия включённого ЭПК
    SME_REVERS_HANDLE,          ///< Сигнал состояния реверсора
    SME_KM_STATE,               ///< Сигнал положения рукоятки контроллера
    SME_KM_TRACTION_LEVEL,      ///< Сигнал уровня тяги
    SME_KM_BRAKE_LEVEL,         ///< Сигнал уровня торможения
    SME_REF_BRAKE_LEVEL_EPB,    ///< Сигнал уровня ЭПТ
    SME_PARKING_BRAKE_ON,       ///< Сигнал включения стояночного тормоза
    SME_IS_EMERGENCY_BRAKE,     ///< Сигнал экстренного торможения

    // Сигналы состояния вагонов
    SME_UNIT_NUM = SME_UNIT_STATE_BEGIN, ///< Сигнал серийного номера
    SME_UNIT_T,                 ///< Сигнал температуры в салоне
    SME_UNIT_DOOR_R,            ///< Сигнал состояния дверей справа
    SME_UNIT_DOOR_L,            ///< Сигнал состояния дверей слева
    SME_UNIT_EQUIP,             ///< Сигнал состояния бортового оборудования
    SME_UNIT_DIESEL,            ///< Сигнал состояния дизеля
    SME_UNIT_FUEL_PUMP,         ///< Сигнал состояния топливного насоса
    SME_UNIT_GENERATOR,         ///< Сигнал состояния генератора
    SME_UNIT_COMPRESSOR,        ///< Сигнал состояния компрессора
    SME_UNIT_GDT_REVERS_STATE,  ///< Сигнал реверсирования гидропередачи
    SME_UNIT_GDT_BRAKE_LEVEL,   ///< Сигнал уровня гидродинамического тормоза
    SME_UNIT_BC1,               ///< Сигнал давления в ТЦ первой тележки
    SME_UNIT_BC2,               ///< Сигнал давления в ТЦ второй тележки
    SME_UNIT_SPT_STATE,         ///< Сигнал применения стояночного тормоза
};

#endif // RA3_SME_SIGNALS_H
