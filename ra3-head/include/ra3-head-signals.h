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


    // МФДУ (МНОГОФУНКЦИОНАЛЬНЫЙ ДИСПЛЕЙ УПРАВЛЕНИЯ)
    MFDU_DISPLAY_ON = 6,
    MFDU_S_SPEED,       // Спидометр. Скорость
    MFDU_S_SPEED_LIMIT, // Спидометр. Ограничение скорости
    MFDU_S_GREEN_DIGIT, // Спидометр. Зеленое число
    MFDU_S_WHITE_DIGIT, // Спидометр. Белое число
    MFDU_ACTIVE_CHARGE,     // Подпитка
    MFDU_PVU,               // Подвагонное управление
    MFDU_EPK,               // ЭПК
    MFDU_MANEUVER_LIGHTS1,  // Маневровые огни 1
    MFDU_MANEUVER_LIGHTS2,  // Маневровые огни 2
    MFDU_PTF,               // ПТФ
    MFDU_PZD,               // ПЖД
    MFDU_PUMP,              // Помпы
    MFDU_TPN,               // ТПН
    MFDU_FIRE,              // Пожар
    MFDU_OZ,                // Пониженный уровень ОЖ контура ПЖД
    MFDU_DOOR,              // Аварийное открытие дверей
    MFDU_GENERATOR,         // Генератор
    MFDU_VIP,               // ВИП
    MFDU_INC_OZ_MOTOR,      // Повышена температура ОЖ двигателя
    MFDU_DEC_OZ_MOTOR,      // Пониженный уровень ОЖ контура двигателя
    MFDU_WC,                // Туалет
    MFDU_ANTY_YUZ,          // Противоюз
    MFDU_REVERS,            // Реверс двигателя не завершён
    MFDU_TRANSMISSION,      // Ошибка трансмиссии
    MFDU_OIL_MOTOR,         // Уровень масла двигателя
    MFDU_PRESSURE_OIL_MOTOR,// Пониженное давление масла двигателя
    MFDU_MOTOR,             // Двигатель
    MFDU_COMPRESSOR,    // Компрессор
    MFDU_COMPRESSOR_1,  // Компрессор 1
    MFDU_COMPRESSOR_2,  // Компрессор 2
    MFDU_ATTENTION,     // Внимание!
    MFDU_STOP,          // СТОП
    MFDU_REVERS_FWD,    // Реверсор вперед
    MFDU_REVERS_BWD,    // Реверсор назад
    MFDU_REVERS_NEUTRAL,// Реверсор нейтальное положение
    MFDU_XREN1,         //
    MFDU_XREN2,         //
    MFDU_XREN3,         //
    MFDU_TRACTION_BRAKING,// Тяга/торможение
    MFDU_PRESSURE_PM,       // Давление ПМ
    MFDU_PRESSURE_TM,       // Давление ТМ
    MFDU_PRESSURE_TC_MAX,   // Давление ТЦ max
    MFDU_PRESSURE_TC_MIN,   // Давление ТЦ min
    MFDU_TEMPERATURE_KAB,   // Температура кабины
    MFDU_I_AKB_24,          // Ток акб 24
    MFDU_I_AKB_110,         // Ток акб 110
    MFDU_VAGON_EQUIPMENT_LEFT,  // Вагонное оборудование
    MFDU_VAGON_EQUIPMENT_RIGHT, // Вагонное оборудование
    MFDU_PZD_MINI_LEFT,         // ПЖД
    MFDU_PZD_MINI_RIGHT,        // ПЖД
    MFDU_BRAKES_LEFT,           // Тормоза
    MFDU_BRAKES_RIGHT,          // Тормоза
    MFDU_CAN_RIGHT,             // Отсутствие свзи с вагоном
    MFDU_T_LEFT,                //
    MFDU_T_RIGHT = 61,          //

    BLOK_TM_PRESS = 100,
    BLOK_UR_PRESS = 101,
    BLOK_TC_PRESS = 102,

    BLOK_RAILWAY_COORD = 103,
    BLOK_VELOCITY = 104,
    BLOK_VELOCITY_CURRENT_LIMIT = 105,
    BLOK_VELOCITY_NEXT_LIMIT = 106,
    BLOK_REVERS = 107,

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
