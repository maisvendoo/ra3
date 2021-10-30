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
    MFDU_ERROR_CODE = 62,

    BLOK_ACCELERATION = 97, // Ускорение
    BLOK_VIGILANCE = 98, // Проверка бдительности
    BLOK_DISPLAY_ON = 99, // Включение дисплея
    BLOK_TM_PRESS = 100,
    BLOK_UR_PRESS = 101,
    BLOK_TC_PRESS = 102,

    BLOK_RAILWAY_COORD = 103,
    BLOK_VELOCITY = 104,
    BLOK_VELOCITY_CURRENT_LIMIT = 105,
    BLOK_VELOCITY_NEXT_LIMIT = 106,
    BLOK_REVERS = 107,

    STRELKA_VOLTMETER110 = 108,
    STRELKA_VOLTMETER24 = 109,

    STRELKA_P_GR = 110,
    STRELKA_P_TM = 111,
    STRELKA_P_TC1 = 112,
    STRELKA_P_TC2 = 113,

    SW_PARKING_BRAKE = 114,

    HANDLE_KRU_091 = 115,

    SIG_BUTTON_TYPHON = 116,
    SIG_BUTTON_WHISTLE = 117,

    DRIVER_CONTROLLER = 118,

    DIRECTION_OF_MOVEMENT = 119,

    ACTIVE_COCKPIT = 150,
    ALARM = 151,
    ANXIETY = 152,
    SOTH = 153,
    SOT = 154,
    OVERHEATING_OF_AXLE_BOXES = 155,
    PARKING_BRAKE = 156,
    BATTERY = 157,
    CDL = 158,
    KDP = 159,

    LS_W = 160,
    LS_R = 161,
    LS_RY = 162,
    LS_Y = 163,
    LS_G1 = 164,
    LS_G2 = 165,
    LS_G3 = 166,
    LS_G4 = 167,

    LS_W_1 = 168,
    LS_R_1 = 169,
    LS_RY_1 = 170,
    LS_Y_1 = 171,
    LS_G1_1 = 172,
    LS_G2_1 = 173,
    LS_G3_1 = 174,
    LS_G4_1 = 175,

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
    SME_BWD_DISEL_STARTED = 8,
    SME_BWD_COMPRESSOR = 9,
    SME_BWD_GENERATOR = 10,
    SME_BWD_FUEL_PUMP_ON = 11,
    SME_PARKING_BRAKE_ON = 12,
    SME_PARKING_BRAKE_STATE = 13,
    SME_BRAKE_LEVEL = 14,
    SME_BRAKE_RELEASE = 15,
    SME_EPK_STATE = 16,
    SME_HYDRO_TRANS_FILL = 17,
    SME_DISEL_FREQ = 18,
    SME_REVERS_HANDLE = 19,
    SME_REVERS_STATE = 20
};

#endif // RA3_HEAD_SIGNALS_H
