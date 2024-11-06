#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::keyProcess()
{
/*    if (!is_active)
        return;*/

    if (is_autostart)
        return;

    // БОРТСЕТЬ ВКЛ.
    if (getKeyState(KEY_U))
        tumbler[IS_BUTTON_PWR_ON].set();
    else
        tumbler[IS_BUTTON_PWR_ON].reset();

    // БОРТСЕТЬ ОТКЛ.
    if (getKeyState(KEY_I))
        tumbler[NO_BUTTON_PWR_OFF].reset();
    else
        tumbler[NO_BUTTON_PWR_OFF].set();

    // СТАРТ
    if (getKeyState(KEY_K))
        tumbler[IS_BUTTON_START].set();
    else
        tumbler[IS_BUTTON_START].reset();

    // СТОП
    if (getKeyState(KEY_H))
        tumbler[IS_BUTTON_STOP].set();
    else
        tumbler[IS_BUTTON_STOP].reset();

    // СПТ
    if (getKeyState(KEY_Leftbracket) && !getKeyState(KEY_Rightbracket))
    {
        tumbler[IS_SWITCH_PARKING_BRAKE].reset();
    }

    if (getKeyState(KEY_Rightbracket) && !getKeyState(KEY_Leftbracket))
    {
        tumbler[IS_SWITCH_PARKING_BRAKE].set();
    }

    // РБ
    if (getKeyState(KEY_M))
        tumbler[IS_BUTTON_RB].set();
    else
        tumbler[IS_BUTTON_RB].reset();

    // РБС
    if (getKeyState(KEY_Z))
        tumbler[IS_BUTTON_RBS].set();
    else
        tumbler[IS_BUTTON_RBS].reset();

    // Выбор скорости
    if (getKeyState((KEY_F)))
        tumbler[IS_BUTTON_SPEED_SELECTION].set();
    else
        tumbler[IS_BUTTON_SPEED_SELECTION].reset();

    // Скорость +
    if (getKeyState((KEY_Q)))
        tumbler[IS_BUTTON_SPEED_PLUS].set();
    else
        tumbler[IS_BUTTON_SPEED_PLUS].reset();

    // Скорость -
    if (getKeyState((KEY_E)))
        tumbler[IS_BUTTON_SPEED_MINUS].set();
    else
        tumbler[IS_BUTTON_SPEED_MINUS].reset();

    // Кнопка "Поддержание скорости"
    button_speed_hold.setState(getKeyState(KEY_G));

    // ЭПК
    if (getKeyState(KEY_N))
    {
        if (isShift())
            tumbler[IS_KEY_EPK].set();
        else
            tumbler[IS_KEY_EPK].reset();
    }

    // Реверсивный переключатель
    if (getKeyState(KEY_W))
        tumbler[IS_SWITCH_REVERS_FWD].set();
    else
        tumbler[IS_SWITCH_REVERS_FWD].reset();

    if (getKeyState(KEY_S))
        tumbler[IS_SWITCH_REVERS_BWD].set();
    else
        tumbler[IS_SWITCH_REVERS_BWD].reset();
}
