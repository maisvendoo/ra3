#ifndef     RA3_SME_SIGNALS_H
#define     RA3_SME_SIGNALS_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    /// наибольшее число вагонов в СМЕ
    MAX_TRAIN_SIZE = 6,
    /// активная кабина, сигнал назад
    SME_HEAD_BWD = -1,
    /// активная кабина, сигнал вперёд
    SME_HEAD_FWD = -2,
    /// неактивный головной вагон, ориентация совпадает с активной кабиной
    SME_HEAD_ORIENT_SAME = 1,
    /// неактивный головной вагон, ориентация противоположна активной кабине
    SME_HEAD_ORIENT_OPPOSITE = 2,
    /// промежуточный вагон любой ориентации
    SME_MIDDLE = 3,
    /// начало массива сигналов СМЕ от активной кабины
    SME_ACTIVE_BEGIN = 10,
    /// размер массива сигналов СМЕ от активной кабины
    SME_ACTIVE_SIZE = 15,
    /// начало массива сигналов СМЕ от вагонов
    SME_UNIT_STATE_BEGIN = 25,
    /// размер массива сигналов СМЕ от вагонов
    SME_UNIT_STATE_SIZE = 15,
    /// начало массива сигналов для передачи состояния вагона на дисплей МФДУ
    MFDU_UNIT_SIGNALS_BEGIN = 56,
    /// размер массива сигналов для передачи состояния вагона на дисплей МФДУ
    MFDU_UNIT_SIGNALS_SIZE = 6
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    // Опрос конфигурации поезда
    SME_TRAIN_CONFIG = 0,

    // КОСТЫЛЬ под нынешнюю реализацию brakepipe
    SME_P0 = 1,

    // Общие сигналы для межвагонных связей
    SME_FWD_CHARGE_VOLTAGE = 2,
    SME_BWD_CHARGE_VOLTAGE = 3,
    SME_FWD_PM_PRESSURE = 4,
    SME_BWD_PM_PRESSURE = 5,

    // Общие сигналы с ведущей секции
    SME_POWER_ON = SME_ACTIVE_BEGIN,
    SME_NO_ACTIVE,
    SME_DISEL_START,
    SME_DISEL_STOP,
    SME_IS_AUTOSTOP_ON,
    SME_REVERS_HANDLE,
    SME_KM_STATE,
    SME_KM_TRACTION_LEVEL,
    SME_KM_BRAKE_LEVEL,
    SME_REF_BRAKE_LEVEL_EPB,
    SME_BRAKE_RELEASE,
    SME_PARKING_BRAKE_ON,
    SME_IS_EMERGENCY_BRAKE,

    // Сигналы с вагонов к ведущей секции
    SME_UNIT_NUM = SME_UNIT_STATE_BEGIN,
    SME_UNIT_T,
    SME_UNIT_EQUIP,
    SME_UNIT_DIESEL,
    SME_UNIT_FUEL_PUMP,
    SME_UNIT_GENERATOR,
    SME_UNIT_COMPRESSOR,
    SME_UNIT_GDT_REVERS_STATE,
    SME_UNIT_GDT_BRAKE_LEVEL,
    SME_UNIT_BC1,
    SME_UNIT_BC2,
    SME_UNIT_SPT_STATE,
};

#endif // RA3_SME_SIGNALS_H
