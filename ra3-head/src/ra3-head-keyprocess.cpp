#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::keyProcess()
{
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

    if (getKeyState(KEY_B))
        soundPlay("Tifon");
    else
        soundStop("Tifon");
}
