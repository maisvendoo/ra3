#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::keyProcess()
{
    if (getKeyState(KEY_J))
    {
        if ( isShift() )
        {
            tumbler[TUMBLER_CABINE_CHANGE].set();
        }
        else
        {
            tumbler[TUMBLER_CABINE_CHANGE].reset();
        }
    }
}
