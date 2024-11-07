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
{/*
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

    // Карданные валы
    DRIVESHAFT = 7,
    INTERAXLE_DRIVESHAFT = 8,

    // Двери: предупреждающий сигнал, ступенька, выдвижная направляющая, створки
    // Дверь левая
    DOOR_L_WARNING_INDICATOR = 9,
    DOOR_L_STEP = 10,
    DOOR_L_SKID = 11,
    DOOR_L_LEFT = 12,
    DOOR_L_RIGHT = 13,
    // Дверь правая
    DOOR_R_WARNING_INDICATOR = 14,
    DOOR_R_STEP = 15,
    DOOR_R_SKID = 16,
    DOOR_R_LEFT = 17,
    DOOR_R_RIGHT = 18,

    // Резерв сигналов под анимации автосцепки СА-3 спереди
    //COUPLING_FWD_SHIFT = 19,
    //COUPLING_FWD_ANGLE = 20,
    //COUPLING_FWD_SA3_LOCK = 21,
    //COUPLING_FWD_SA3_LOCKKEEPER = 22,
    //COUPLING_FWD_SA3_SHAFT = 23,
    //COUPLING_FWD_SA3_OPERATING_CHAIN = 24,
    //COUPLING_FWD_SA3_OPERATING_ROD = 25,

    // Резерв сигналов под анимации поворота сцепного устройства сзади
    //COUPLING_BWD_SHIFT = 26,
    //COUPLING_BWD_ANGLE = 27,

    // Резерв сигналов под анимации концевых кранов тормозной магистрали
    //ANGLECOCK_BP_FWD_HANDLE = 28,
    //ANGLECOCK_BP_BWD_HANDLE = 29,

    // Резерв сигналов под анимации рукава тормозной магистрали спереди
    //HOSE_BP_FWD_STATE = 30,
    //HOSE_BP_FWD_SIDE_ANGLE = 31,
    //HOSE_BP_FWD_DOWN_ANGLE = 32,

    // Резерв сигналов под анимации концевых кранов питательной магистрали
    //ANGLECOCK_FL_FWD_HANDLE = 33,
    //ANGLECOCK_FL_BWD_HANDLE = 34,

    // Резерв сигналов под анимации рукава питательной магистрали спереди
    //HOSE_FL_FWD_STATE = 35,
    //HOSE_FL_FWD_SIDE_ANGLE = 36,
    //HOSE_FL_FWD_DOWN_ANGLE = 37,

    // Резерв сигналов под прожектор и буферные огни
    //HEADLIGHT_FWD = 38,
    //BUFFERLIGHT_WHITE_L_FWD = 39,
    //BUFFERLIGHT_RED_L_FWD = 40,
    //BUFFERLIGHT_WHITE_R_FWD = 41,
    //BUFFERLIGHT_RED_R_FWD = 42,

    // 43-49 резерв на прочие анимации кузова - подсветку, двери в кабину и т.п.

    // === АНИМАЦИИ КАБИНЫ ===
    // Панель органов управления ПОУ
    BUTTON_BOARDNET_ON = 50,
    BUTTON_BOARDNET_OFF = 51,
    //BUTTON_TRANSIT = 52,
    //BUTTON_TRANSIT_PROTECTIVE_COVER = 53,
    //BUTTON_TRANSIT_INDICATOR = 54,
    //TOOGLE_EMERGENCY_CONTROL = 55,
    //BUTTON_POWER_SUPPLY = 56,
    //BUTTON_POWER_SUPPLY_PROTECTIVE_COVER = 57,
    //BUTTON_POWER_SUPPLY_INDICATOR = 58,
    ARROW_VOLTMETER_24V = 59,
    ARROW_VOLTMETER_110V = 60,
    TOOGLE_TROLLEY_LIGHTING = 61,
    TOOGLE_PZD = 62,
    TOOGLE_RESERV = 63,
    TOOGLE_GLASS_HEATING = 64,
    TOOGLE_SALON_CLIMATE_CONTROL = 65,
    TOOGLE_CABINE_VENTILATION = 66,
    TOOGLE_CABINE_CONDITIONER = 67,
    TOOGLE_CABINE_HEATER = 68,
    //CONTROL_GEAR_CABINE_TEMPERATURE = 69,

    // Блок защиты и коммутации БЗК
    AZV_1_HEATING_TF1_MTU = 70,
    AZV_2_HEATING_TF2_MTU = 71,
    AZV_3_CONTROL_MTU = 72,
    AZV_4_CONTROL_GMP = 73,
    AZV_5_STARTER = 74,
    AZV_6_GENERATOR_POWER_SUPPLY = 75,
    AZV_7_PUMP = 76,
    AZV_8_PZD1 = 77,
    AZV_9_PZD2 = 78,
    AZV_10_BREAKING = 79,
    AZV_11_110V_SU = 80,
    AZV_12_CONSUMERS_SU_PK = 81,
    AZV_13_CONTROL_PANEL_MFDU = 82,
    AZV_14_24V_CONTROL_CIRCUITS = 83,
    AZV_15_BLOK = 84,
    AZV_16_KVARC = 85,
    AZV_17_CIK_P = 86,
    AZV_18_CIK_L = 87,
    AZV_19_BOARDNET = 88,
    AZV_20_CONTROL_CIRCUITS = 89,
    AZV_21_HEADLIGHT = 90,
    AZV_22_LANTERNS = 91,
    AZV_23_RADIO_STATION = 92,
    AZV_24_ADD_EQUIPMENT = 93,
    AZV_25_MIRRORS = 94,
    AZV_26_WINDSCREEN_WIPERS = 95,
    AZV_27_SOCKETS_24V = 96,
    AZV_28_CONTROL_DOORS = 97,
    AZV_29_ASOTP = 98,
    AZV_30_RESERVE1 = 99,
    AZV_31_RESERVE2 = 100,

    // Рукоятка контроллера тяги/торможения
    TRACTION_CONTROLLER_HANDLE = 101,

    // Рукоятка крана резервного управления тормозами
    BRAKES_CONTROLLER_HANDLE = 102,

    // Клапан аварийного экстренного торможения
    BUTTON_EMERGENCY_STOP = 103,

    // Рукоятки бдительности
    BUTTON_RBS = 104,
    BUTTON_RB = 105,

    // Ключ ЭПК
    TOOGLE_EPK = 106,

    // Панель управления ПУ-1
    BUTTON_EMERGENCY_CONTROL = 107,
    //BUTTON_EMERGENCY_CONTROL_PROTECTIVE_COVER = 108,
    BUTTON_DIESEL_START = 109,
    BUTTON_DISEL_STOP = 110,
    //BUTTON_REPEAT = 111,
    TOOGLE_BUFFERLIGHTS_MANEUROUS_OR_MOTION = 112,
    TOOGLE_BUFFERLIGHTS_WHITE_OR_REDWHITE = 113,
    TOOGLE_DIRECTION_OF_MOVEMENT = 114,
    BUTTON_PLAY_RECORD = 115,
    BUTTON_MICROPHONE = 116,

    // Панель управления ПУ-2
    TOOGLE_WINDSCREEN_WIPERS = 117,
    BUTTON_WINDSCREEN_WASHERS = 118,
    BUTTON_WHISTLE_M = 119,
    BUTTON_TYPHON_M = 120,

    // Панель управления ПУ-3
    BUTTON_RBP = 121,
    BUTTON_WHISTLE_MP = 122,
    BUTTON_TYPHON_MP = 123,

    // Панель управления ПУ-4
    BUTTON_OPEN_L_DOORS = 124,
    BUTTON_OPEN_L_DOORS_INDICATOR = 125,
    BUTTON_CLOSE_L_DOORS = 126,
    BUTTON_CLOSE_L_DOORS_INDICATOR = 127,
    //BUTTON_SAND = 128,
    TOOGLE_HEADLIGHT = 129,
    TOOGLE_SALON_LIGHTING = 130,
    BUTTON_STEPS = 131,
    BUTTON_STEPS_INDICATOR = 132,
    BUTTON_OPEN_R_DOORS = 133,
    BUTTON_OPEN_R_DOORS_INDICATOR = 134,
    BUTTON_CLOSE_R_DOORS = 135,
    BUTTON_CLOSE_R_DOORS_INDICATOR = 136,
    BUTTON_SPEED_MAINTAINING = 137,
    BUTTON_SPEED_MAINTAINING_INDICATOR = 138,
    BUTTON_SPEED_SELECTION = 139,
    BUTTON_SPEED_PLUS = 140,
    BUTTON_SPEED_MINUS = 141,

    // Панель управления ПУ-5
    TOOGLE_CONTROL_PANEL_LIGHTING_MP = 142,
    //CONTROL_GEAR_CONTROL_PANEL_BRIGTNESS_MP = 143,

    // Панель управления ПУ-6
    TOOGLE_CABINE_LIGHTING = 144,
    TOOGLE_CONTROL_PANEL_LIGHTING_M = 145,
    //CONTROL_GEAR_CONTROL_PANEL_BRIGTNESS_M = 146,

    // Лампы локомотивного светофора на блоке индикации БИ-2
    INDICATOR_LS_W_MP = 147,
    INDICATOR_LS_R_MP = 148,
    INDICATOR_LS_RY_MP = 149,
    INDICATOR_LS_Y_MP = 150,
    INDICATOR_LS_G1_MP = 151,
    INDICATOR_LS_G2_MP = 152,
    INDICATOR_LS_G3_MP = 153,
    INDICATOR_LS_G4_MP = 154,

    // Лампы локомотивного светофора на блоке индикации БИ-4
    INDICATOR_LS_W_M = 155,
    INDICATOR_LS_R_M = 156,
    INDICATOR_LS_RY_M = 157,
    INDICATOR_LS_Y_M = 158,
    INDICATOR_LS_G1_M = 159,
    INDICATOR_LS_G2_M = 160,
    INDICATOR_LS_G3_M = 161,
    INDICATOR_LS_G4_M = 162,

    // Контрольные лампы на блоке индикации БИ-4
    INDICATOR_DOORS_CLOSED_L = 163,
    INDICATOR_DOORS_CLOSED_R = 164,
    INDICATOR_PARKING_BRAKE = 165,
    INDICATOR_BATTERY = 166,
    INDICATOR_OVERHEATING_AXLE_BOXES = 167,
    INDICATOR_RELEASE_BRAKES = 168,
    INDICATOR_ALARM_LOW = 169,
    INDICATOR_RELEASE_BRAKES_TAIL = 170,
    INDICATOR_ALARM_HIGH = 171,
    INDICATOR_ACTIVE_CABINE = 172,

    // Блок индикации БИ-5
    ARROW_FL_PRESSURE = 173,
    ARROW_BP_PRESSURE = 174,
    ARROW_BC_FWD_PRESSURE = 175,
    ARROW_BC_BWD_PRESSURE = 176,
    TOOGLE_PARKING_BRAKE = 177,
    BUTTON_MIRRORS_HEATING = 178,
    BUTTON_MIRRORS_HEATING_INDICATOR = 179,
    //JOYSTIK_MIRROR_SELECTION = 180,
    //JOYSTIK_MIRROR_HORIZONTAL_AXIS = 181,
    //JOYSTIK_MIRROR_VERTICAL_AXIS = 182,
    //CONTROL_GEAR_MANOMETER_BRIGTHNESS = 183,

// TODO // МФДУ
// TODO // БЛОК
// TODO // Звуки
*/
    // Кнопка "БОРТСЕТЬ ВКЛ."
    SIG_BUTTON_ON = 0,
    // Кнопка "БОРТСЕТЬ ОТКЛ."
    SIG_BUTTON_OFF = 1,

    SIG_BUTTON_START = 4,
    SIG_BUTTON_STOP = 5,

    // МФДУ (МНОГОФУНКЦИОНАЛЬНЫЙ ДИСПЛЕЙ УПРАВЛЕНИЯ) сигналы 6..49
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

    // Дисплей БЛОК сигналы 130..141
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

    // Контрольные лампы
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

    // Лампы локомотивного светофора
    LS_W = 160,
    LS_R = 161,
    LS_RY = 162,
    LS_Y = 163,
    LS_G1 = 164,
    LS_G2 = 165,
    LS_G3 = 166,
    LS_G4 = 167,

    // Лампы локомотивного светофора
    LS_W_1 = 168,
    LS_R_1 = 169,
    LS_RY_1 = 170,
    LS_Y_1 = 171,
    LS_G1_1 = 172,
    LS_G2_1 = 173,
    LS_G3_1 = 174,
    LS_G4_1 = 175,

    // Кнопка экстренного торможения
    EMERGENCY_STOP_BUTTON = 176,

    // Кнопки бдительности
    RB = 177,
    RBS = 178,
    // Ключ ЭПК
    EPK = 179,

    // Кнопки пульта
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
    WHEEL_4 = 197,

    // Звуки
    SOUND_SVISTOK = 201,
    SOUND_TIFON = 202,

    SOUND_REVERSOR = 203,
    SOUND_CONTROLLER = 204,
    SOUND_KM_EMERGENCY = 205,
    SOUND_EMERGENCY_VALVE = 206,

    SOUND_BLOK_BUTTON = 207,
    SOUND_BLOK_SPEED_LIMIT = 208,

    SOUND_PARKING_BRAKE_SWITCHER = 209,
    SOUND_PARKING_BRAKE_FLOW = 210,

    SOUND_BRAKE_CRANE_BP_FILL_FLOW = 215,
    SOUND_BRAKE_CRANE_BP_DRAIN_FLOW = 216,

    SOUND_EPK_WHISTLE = 220,
/*
    SOUND_5_10 = 221,
    SOUND_10_20 = 222,
    SOUND_20_30 = 223,
    SOUND_30_40 = 224,
    SOUND_40_50 = 225,
    SOUND_50_60 = 226,
    SOUND_60_70 = 227,
    SOUND_70_80 = 228,
    SOUND_80_90 = 229,
    SOUND_90_100 = 230,
    SOUND_100_110 = 231,
    SOUND_110_X = 232,
*/
    SOUND_RELAY_POWER = 235,
    SOUND_RELAY_ACTIVE_CAB = 236,

    SOUND_FUEL_PUMP = 237,
    SOUND_DISEL_STARTER = 238,
    SOUND_DISEL_NOM_FREQ = 239,
    SOUND_DISEL_HIGH_FREQ = 240,
    SOUND_DISEL_STOP = 241,

    SOUND_SAND_DELIVERY = 242
};

#endif // RA3_HEAD_SIGNALS_H
