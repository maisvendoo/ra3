#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::keyProcess()
{
    if (!is_active)
        return;

    // БОРТСЕТЬ ВКЛ.
    if (getKeyState(KEY_U))
        tumbler[BUTTON_PWR_ON].set();
    else
        tumbler[BUTTON_PWR_ON].reset();

    // БОРТСЕТЬ ОТКЛ.
    if (getKeyState(KEY_I))
        tumbler[BUTTON_PWR_OFF].reset();
    else
        tumbler[BUTTON_PWR_OFF].set();

    // СТАРТ
    if (getKeyState(KEY_K))
        tumbler[BUTTON_START].set();
    else
        tumbler[BUTTON_START].reset();

    // СТОП
    if (getKeyState(KEY_H))
        tumbler[BUTTON_STOP].set();
    else
        tumbler[BUTTON_STOP].reset();
}
