#ifndef     RA3_MIDDLE_SIGNALS_H
#define     RA3_MIDDLE_SIGNALS_H

#include    "ra3-sme-signals.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
/*
    // === АНИМАЦИИ КУЗОВА ===
    // Резерв - бортовой номер
    //SERIAL_NUMBER = 0,

    // Колёсные пары
    WHEELSET_1 = 1,
    WHEELSET_2 = 2,
    WHEELSET_3 = 3,
    WHEELSET_4 = 4,

    // Резерв сигналов под поворот тележек в кривых
    //TROLLEY_FWD_ANGLE = 5,
    //TROLLEY_BWD_ANGLE = 6,

    // Двери: предупреждающий сигнал, ступенька, выдвижная направляющая, створки
    // Дверь левая передняя
    DOOR_L_FWD_WARNING_INDICATOR = 7,
    DOOR_L_FWD_STEP = 8,
    DOOR_L_FWD_SKID = 9,
    DOOR_L_FWD_LEFT = 10,
    DOOR_L_FWD_RIGHT = 11,
    // Дверь левая задняя
    DOOR_L_BWD_WARNING_INDICATOR = 12,
    DOOR_L_BWD_STEP = 13,
    DOOR_L_BWD_SKID = 14,
    DOOR_L_BWD_LEFT = 15,
    DOOR_L_BWD_RIGHT = 16,
    // Дверь правая передняя
    DOOR_R_FWD_WARNING_INDICATOR = 17,
    DOOR_R_FWD_STEP = 18,
    DOOR_R_FWD_SKID = 19,
    DOOR_R_FWD_LEFT = 20,
    DOOR_R_FWD_RIGHT = 21,
    // Дверь правая задняя
    DOOR_R_BWD_WARNING_INDICATOR = 22,
    DOOR_R_BWD_STEP = 23,
    DOOR_R_BWD_SKID = 24,
    DOOR_R_BWD_LEFT = 25,
    DOOR_R_BWD_RIGHT = 26,

    // Резерв сигналов под анимации поворота сцепного устройства спереди
    //COUPLING_FWD_SHIFT = 27,
    //COUPLING_FWD_ANGLE = 28,

    // Резерв сигналов под анимации поворота сцепного устройства сзади
    //COUPLING_BWD_SHIFT = 26,
    //COUPLING_BWD_ANGLE = 27,

    // Резерв сигналов под анимации концевых кранов тормозной магистрали
    //ANGLECOCK_BP_FWD_HANDLE = 28,
    //ANGLECOCK_BP_BWD_HANDLE = 29,

    // Резерв сигналов под анимации концевых кранов питательной магистрали
    //ANGLECOCK_FL_FWD_HANDLE = 30,
    //ANGLECOCK_FL_BWD_HANDLE = 31,
*/
    // Углы поворота колесных пар
    WHEEL_1 = 194,
    WHEEL_2 = 195,
    WHEEL_3 = 196,
    WHEEL_4 = 197
};

#endif // RA3_MIDDLE_SIGNALS_H
