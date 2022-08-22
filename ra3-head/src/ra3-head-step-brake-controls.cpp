#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeControls(double t, double dt)
{
    if (is_active)
    {
        kru->setControl(keys);
        kru->setChargePressure(charge_press);
        kru->setFeedLinePressure(main_res->getPressure());
        kru->step(t, dt);

        p0 = kru->getBrakePipeInitPressure();
    }
}
