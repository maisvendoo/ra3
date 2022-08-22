#ifndef     RA3_SME_SIGNALS_H
#define     RA3_SME_SIGNALS_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    // Общие сигналы для межвагонных связей
    SME_FWD_CHARGE_VOLTAGE = 1,
    SME_BWD_CHARGE_VOLTAGE = 2,
    SME_FWD_PM_PRESSURE = 3,
    SME_BWD_PM_PRESSURE = 4,

    // Общие сигналы с ведущей секции
    SME_BWD_POWER_ON = 10,
    SME_REVERS_HANDLE = 11,
    SME_IS_KM_ZERO = 12,
    SME_IS_KM_TRACTION = 13,
    SME_IS_KM_BRAKE = 14,
    SME_KM_TRACTION_LEVEL = 15,
    SME_DISEL_FREQ = 16,
    SME_KM_BRAKE_LEVEL = 17,
    SME_REF_BRAKE_LEVEL_EPB = 18,
    SME_BRAKE_RELEASE = 19,
    SME_PARKING_BRAKE_ON = 20,
    SME_IS_EMERGENCY_BRAKE = 21,
    SME_EPK_STATE = 22,
    SME_NO_ACTIVE = 23,

    // Сигналы с ведущей секции к ведомой секции
    SME_BWD_FUEL_PUMP = 40,
    SME_BWD_FUEL_VALVE_OPEN = 41,
    SME_BWD_STARTER_ON = 42,
    SME_BWD_DISEL_STARTED = 43,

    // Сигналы с ведомой секции к ведущей секции
    SME_BWD_OIL_PRESS = 45,
    SME_BWD_FUEL_PRESS = 46,
    SME_BWD_FUEL_PUMP_ON = 47,
    SME_BWD_OMEGA = 48,
    SME_BWD_GENERATOR = 49,
    SME_BWD_COMPRESSOR = 50,
    SME_REVERS_STATE = 51,
    SME_BWD_BRAKE_LEVEL = 52,
    SME_BWD_BC1 = 53,
    SME_BWD_BC2 = 54,
    SME_PARKING_BRAKE_STATE = 55,
    SME_BWD_CAN = 56

};

#endif // RA3_SME_SIGNALS_H
