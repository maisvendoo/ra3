#ifndef     RA3_TUMBLERS_DEFINE_H
#define     RA3_TUMBLERS_DEFINE_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    /// Общее количество элементов управления
    TUMBLERS_NUM = 100,

    /// Кнопка "БОРТСЕТЬ ВКЛ."
    BUTTON_PWR_ON = 0,
    /// Кнопка ЭБОРТСЕТЬ ОТКЛ."
    BUTTON_PWR_OFF = 1,

    /// Кнопка "СТАРТ" (запуск дизелей)
    BUTTON_START = 2,
    /// Кнопка "СТОП" (остановка дизелей)
    BUTTON_STOP = 3,

    /// Выключатель СПТ
    SWITCH_PARKING_BRAKE = 4,

    /// Рукоятка бдительности (РБ)
    BUTTON_RB = 5,

    /// Рукоятка бдительности специальная (РБС)
    BUTTON_RBS = 6,

    /// Кнопка "Выбор скорости"
    BUTTON_SPEED_SELECTION = 7,

    /// Кнопка "Скорость +"
    BUTTON_SPEED_PLUS = 8,

    /// Кнопка "Скорость -"
    BUTTON_SPEED_MINUS = 9,

    /// Кнопка "Поддержание скорости"
    BUTTON_SPEED_HOLD = 10,

    /// Ключ ЭПК
    KEY_EPK = 11
};

#endif // RA3_TUMBLERS_DEFINE_H
