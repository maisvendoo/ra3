#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepCabineControls(double t, double dt)
{
    is_active = is_active_ref
              && (static_cast<int>(sme_fwd->getSignal(SME_NO_ACTIVE)) != 1.0)
              && (static_cast<int>(sme_bwd->getSignal(SME_NO_ACTIVE)) != 1.0);

    if (is_active)
    {
        km->setControl(keys);
        km->setFwdKey(tumbler[SWITCH_REVERS_FWD].getState());
        km->setBwdKey(tumbler[SWITCH_REVERS_BWD].getState());
        km->setBPpressure(brakepipe->getPressure());
        km->step(t, dt);
    }
}
