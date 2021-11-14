#ifndef     RA3_SME_SIGNALS_H
#define     RA3_SME_SIGNALS_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    SME_BWD_POWER_ON = 0,
    SME_FWD_POWER_ON = 1,
    SME_BWD_FUEL_PUMP = 2,
    SME_BWD_FUEL_PRESS = 3,
    SME_BWD_OIL_PRESS = 4,
    SME_BWD_STARTER_ON = 5,
    SME_BWD_OMEGA = 6,
    SME_BWD_FUEL_VALVE_OPEN = 7,
    SME_BWD_DISEL_STARTED = 8,
    SME_BWD_COMPRESSOR = 9,
    SME_BWD_GENERATOR = 10,
    SME_BWD_FUEL_PUMP_ON = 11,
    SME_PARKING_BRAKE_ON = 12,
    SME_PARKING_BRAKE_STATE = 13,
    SME_REF_BRAKE_LEVEL = 14,
    SME_BRAKE_RELEASE = 15,
    SME_EPK_STATE = 16,
    SME_IS_KM_TRACTION = 17,
    SME_DISEL_FREQ = 18,
    SME_REVERS_HANDLE = 19,
    SME_REVERS_STATE = 20,
    SME_BWD_BC1 = 21,
    SME_BWD_BC2 = 22,
    SME_BWD_BRAKE_LEVEL = 23,
    SME_IS_KM_BRAKE = 24,
    SME_IS_KM_ZERO = 25,
    SME_KM_TRACTION_LEVEL = 26,
    SME_KM_BRAKE_LEVEL = 27,
    SME_IS_EMERGENCY_BRAKE = 28,
    SME_BWD_CAN = 29,
    SME_NO_ACTIVE = 30
};

#endif // RA3_SME_SIGNALS_H
