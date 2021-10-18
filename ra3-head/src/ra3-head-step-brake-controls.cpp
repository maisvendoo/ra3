#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeControls(double t, double dt)
{
    kru->setControl(keys);
    kru->step(t, dt);
}
