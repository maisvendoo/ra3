#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::keyProcess()
{
    if (is_autostart)
        return;

    // БОРТСЕТЬ ВКЛ.
    if (getKeyState(KEY_U))
        key_tumbler[IS_BUTTON_PWR_ON].set();
    else
        key_tumbler[IS_BUTTON_PWR_ON].reset();

    // БОРТСЕТЬ ОТКЛ.
    if (getKeyState(KEY_I))
        key_tumbler[NO_BUTTON_PWR_OFF].reset();
    else
        key_tumbler[NO_BUTTON_PWR_OFF].set();

    // СТАРТ
    if (getKeyState(KEY_K))
        key_tumbler[IS_BUTTON_START].set();
    else
        key_tumbler[IS_BUTTON_START].reset();

    // СТОП
    if (getKeyState(KEY_H))
        key_tumbler[IS_BUTTON_STOP].set();
    else
        key_tumbler[IS_BUTTON_STOP].reset();

    // СПТ
    if (getKeyState(KEY_Rightbracket))
    {
        key_tumbler[IS_SWITCH_PARKING_BRAKE].set();
    }
    else
    {
        if (getKeyState(KEY_Leftbracket))
        {
            key_tumbler[IS_SWITCH_PARKING_BRAKE].reset();
        }
        else
        {
            // Если клавиши были кратковременно нажаты и отпущены,
            // обновляем текущее состояние для сброса таймеров срабатывания
            if (key_tumbler[IS_SWITCH_PARKING_BRAKE].getState())
                key_tumbler[IS_SWITCH_PARKING_BRAKE].set();
            else
                key_tumbler[IS_SWITCH_PARKING_BRAKE].reset();
        }
    }

    // РБ
    if (getKeyState(KEY_M))
        key_tumbler[IS_BUTTON_RB].set();
    else
        key_tumbler[IS_BUTTON_RB].reset();

    // РБС
    if (getKeyState(KEY_Z))
        key_tumbler[IS_BUTTON_RBS].set();
    else
        key_tumbler[IS_BUTTON_RBS].reset();

    // Выбор скорости
    if (getKeyState(KEY_F))
        tumbler[IS_BUTTON_SPEED_SELECTION].set();
    else
        tumbler[IS_BUTTON_SPEED_SELECTION].reset();

    // Скорость +
    if (getKeyState(KEY_Q))
        tumbler[IS_BUTTON_SPEED_PLUS].set();
    else
        tumbler[IS_BUTTON_SPEED_PLUS].reset();

    // Скорость -
    if (getKeyState(KEY_E))
        tumbler[IS_BUTTON_SPEED_MINUS].set();
    else
        tumbler[IS_BUTTON_SPEED_MINUS].reset();

    // Песок
    if (getKeyState(KEY_Delete))
        tumbler[IS_SAND].set();
    else
        tumbler[IS_SAND].reset();

    // ЭПК
    if (getKeyState(KEY_N))
    {
        if (isShift())
            key_tumbler[IS_KEY_EPK].set();
        else
            key_tumbler[IS_KEY_EPK].reset();
    }
    else
    {
        // Если клавиша была кратковременно нажата и отпущена,
        // обновляем текущее состояние для сброса таймеров срабатывания
        if (key_tumbler[IS_KEY_EPK].getState())
            key_tumbler[IS_KEY_EPK].set();
        else
            key_tumbler[IS_KEY_EPK].reset();
    }

    // Реверсивный переключатель
    if (getKeyState(KEY_W))
        key_tumbler[IS_SWITCH_REVERS_FWD].set();
    else
        key_tumbler[IS_SWITCH_REVERS_FWD].reset();

    if (getKeyState(KEY_S))
        key_tumbler[IS_SWITCH_REVERS_BWD].set();
    else
        key_tumbler[IS_SWITCH_REVERS_BWD].reset();

    // Кнопка "Поддержание скорости"
    if (getKeyState(KEY_G))
    {
        key_tumbler[IS_BUTTON_SPEED_HOLD].set();
    }
    else
    {
        key_tumbler[IS_BUTTON_SPEED_HOLD].reset();

        if (key_tumbler[IS_BUTTON_SPEED_HOLD].getState())
        {
            // При отпускании кнопки - меняем статус фиксации нажатого положения
            if (tumbler[IS_FIXED_SPEED_HOLD].getState())
                tumbler[IS_FIXED_SPEED_HOLD].reset();
            else
                tumbler[IS_FIXED_SPEED_HOLD].set();
        }
    }

    // Кнопка "ступени"
    if (isShift() && (getKeyState(KEY_R)))
    {
        key_tumbler[IS_BUTTON_STEP].set();
    }
    else
    {
        key_tumbler[IS_BUTTON_STEP].reset();

        if (key_tumbler[IS_BUTTON_STEP].getState())
        {
            // При отпускании кнопки - меняем статус фиксации нажатого положения
            if (tumbler[IS_FIXED_STEP].getState())
                tumbler[IS_FIXED_STEP].reset();
            else
                tumbler[IS_FIXED_STEP].set();
        }
    }

    // Кнопка "Открыть двери левые"
    if (isControl() && (getKeyState(KEY_T)))
        key_tumbler[IS_BUTTON_DOOR_L_OPEN].set();
    else
        key_tumbler[IS_BUTTON_DOOR_L_OPEN].reset();

    // Кнопка "Закрыть двери левые"
    if (isShift() && (getKeyState(KEY_T)))
    {
        key_tumbler[IS_BUTTON_DOOR_L_CLOSE].set();
    }
    else
    {
        key_tumbler[IS_BUTTON_DOOR_L_CLOSE].reset();

        if (key_tumbler[IS_BUTTON_DOOR_L_CLOSE].getState())
        {
            // При отпускании кнопки - меняем статус фиксации нажатого положения
            if (tumbler[IS_FIXED_DOOR_L_CLOSE].getState())
                tumbler[IS_FIXED_DOOR_L_CLOSE].reset();
            else
                tumbler[IS_FIXED_DOOR_L_CLOSE].set();
        }
    }

    // Кнопка "Открыть двери левые"
    if (isControl() && (getKeyState(KEY_Y)))
        key_tumbler[IS_BUTTON_DOOR_R_OPEN].set();
    else
        key_tumbler[IS_BUTTON_DOOR_R_OPEN].reset();

    // Кнопка "Закрыть двери левые"
    if (isShift() && (getKeyState(KEY_Y)))
    {
        key_tumbler[IS_BUTTON_DOOR_R_CLOSE].set();
    }
    else
    {
        key_tumbler[IS_BUTTON_DOOR_R_CLOSE].reset();

        if (key_tumbler[IS_BUTTON_DOOR_R_CLOSE].getState())
        {
            // При отпускании кнопки - меняем статус фиксации нажатого положения
            if (tumbler[IS_FIXED_DOOR_R_CLOSE].getState())
                tumbler[IS_FIXED_DOOR_R_CLOSE].reset();
            else
                tumbler[IS_FIXED_DOOR_R_CLOSE].set();
        }
    }
}
