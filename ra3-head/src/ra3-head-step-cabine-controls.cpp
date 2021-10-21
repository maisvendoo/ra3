#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepCabineControls(double t, double dt)
{
    km->setControl(keys);
    km->step(t, dt);
}
