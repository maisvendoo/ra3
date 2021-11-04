#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepCabineControls(double t, double dt)
{
    if (is_active)
    {
        km->setControl(keys);
        km->setBrakePipePressure(pTM);
        km->step(t, dt);
    }
}
