#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepCabineControls(double t, double dt)
{
    is_active = is_active_ref &&
            !static_cast<bool>(backward_inputs[SME_NO_ACTIVE])&&
            !static_cast<bool>(forward_inputs[SME_NO_ACTIVE]);

    if (is_active)
    {
        km->setControl(keys);
        km->setFwdKey(tumbler[SWITCH_REVERS_FWD].getState());
        km->setBwdKey(tumbler[SWITCH_REVERS_BWD].getState());
        km->setBrakePipePressure(pTM);
        km->step(t, dt);
    }
}
