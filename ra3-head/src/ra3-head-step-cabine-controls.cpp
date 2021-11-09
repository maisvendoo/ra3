#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepCabineControls(double t, double dt)
{
    if (is_active)
    {
        km->setControl(keys);
        km->setFwdKey(tumbler[SWITCH_REVERS_FWD].getState());
        km->setBwdKey(tumbler[SWITCH_REVERS_BWD].getState());
        km->setBrakePipePressure(pTM);
        km->step(t, dt);
    }
}
