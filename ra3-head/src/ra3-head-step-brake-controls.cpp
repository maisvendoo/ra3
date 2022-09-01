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
    // КОСТЫЛЬ под нынешнюю реализацию brakepipe
    else
    {
        if (idx == 0)
            p0 = static_cast<double>(backward_inputs[SME_P0]) +
                 static_cast<double>(forward_inputs[SME_P0]);
    }
}
