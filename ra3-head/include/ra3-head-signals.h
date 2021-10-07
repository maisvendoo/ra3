#ifndef     RA3_HEAD_SIGNALS_H
#define     RA3_HEAD_SIGNALS_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    // Кнопка "БОРТСЕТЬ ВКЛ."
    SIG_BUTTON_ON = 0,
    // Кнопка "БОРТСЕТЬ ОТКЛ."
    SIG_BUTTON_OFF = 1,

    // Подача питания на МФДУ
    SIG_MFDU_ON = 2,
    // Подача питания на дисплей БЛОК-М
    SIG_BLOK_ON = 3,

    SIG_BUTTON_START = 4,
    SIG_BUTTON_STOP = 5,

    // Углы поворота колесных пар
    WHEEL_1 = 194,
    WHEEL_2 = 195,
    WHEEL_3 = 196,
    WHEEL_4 = 197
};

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
    SME_BWD_DISEL_STARTED = 8
};

#endif // RA3_HEAD_SIGNALS_H
