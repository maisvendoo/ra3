#ifndef     RA3_HEAD_SIGNALS_H
#define     RA3_HEAD_SIGNALS_H

#include    "ra3-sme-signals.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    /// начало массива сигналов для передачи состояния вагона на дисплей МФДУ
    MFDU_UNIT_SIGNALS_BEGIN = 52,
    /// размер массива сигналов для передачи состояния вагона на дисплей МФДУ
    MFDU_UNIT_SIGNALS_SIZE = 9
};

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
    MFDU_ERROR_CODE,

    MFDU_TRAIN_SIZE = 50,   // Количество вагонов
    MFDU_POS_IN_TRAIN = 51,   // Количество вагонов
    // Сигналы 52..105 - состояние вагонов, 9 сигналов на каждый вагон
    MFDU_TRAIN_UNIT = MFDU_UNIT_SIGNALS_BEGIN,  // Тип вагона
    MFDU_TRAIN_UNIT_NUM,    // Номер вагона или отсутствие связи CAN
    MFDU_TRAIN_UNIT_T,      // Температура в вагоне
    MFDU_TRAIN_UNIT_DIESEL, // Состояние дизеля
    MFDU_TRAIN_UNIT_COMPRESSOR, // Состояние дизеля
    MFDU_TRAIN_UNIT_EQUIP,  // Состояние вагонного оборудования
    MFDU_TRAIN_UNIT_BRAKES, // Состояние тормоза
    MFDU_TRAIN_UNIT_DOOR_R, // Состояние дверей правых
    MFDU_TRAIN_UNIT_DOOR_L, // Состояние дверей левых

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

    BLOK_DISPLAY_ON = 130,      // Включение дисплея
    BLOK_STATION_INDEX = 131,   // Номер станции в списке
    BLOK_ACCELERATION = 132,    // Ускорение
    BLOK_VIGILANCE = 133,       // Проверка бдительности
    BLOK_TM_PRESS = 134,
    BLOK_UR_PRESS = 135,
    BLOK_TC_PRESS = 136,

    BLOK_RAILWAY_COORD = 137,
    BLOK_VELOCITY = 138,
    BLOK_VELOCITY_CURRENT_LIMIT = 139,
    BLOK_VELOCITY_NEXT_LIMIT = 140,
    BLOK_REVERS = 141,

    ACTIVE_COCKPIT = 150,
    ALARM = 151,
    ANXIETY = 152,
    SOTH = 153,
    SOT = 154,
    OVERHEATING_OF_AXLE_BOXES = 155,
    PARKING_BRAKE = 156,
    BATTERY = 157,
    KDL = 158,
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

    EMERGENCY_STOP_BUTTON = 176,

    RB = 177,
    RBS = 178,
    EPK = 179,

    SPEED_SELECTION = 180,
    SPEED_PLUS = 181,
    SPEED_MINUS = 182,
    SPEED_HOLD = 183,
    LEFT_OPEN = 184,
    LEFT_CLOSE = 185,
    STEPS = 186,
    RIGHT_OPEN = 187,
    RIGHT_CLOSE = 188,
    HOLD_SPEED = 189,

    // Угол вращения кардана 1
    SHAFT_1 = 192,

    // Угол вращения кардана 2
    SHAFT_2 = 193,

    // Углы поворота колесных пар
    WHEEL_1 = 194,
    WHEEL_2 = 195,
    WHEEL_3 = 196,
    WHEEL_4 = 197
};

#endif // RA3_HEAD_SIGNALS_H
