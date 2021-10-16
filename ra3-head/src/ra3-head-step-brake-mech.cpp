#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeMech(double t, double dt)
{
    for (size_t i = 0; i < brake_mech.size(); ++i)
    {
        brake_mech[i]->step(t, dt);

        Q_r[i+1] = brake_mech[i]->getBrakeTorque();
        Q_r[i+2] = brake_mech[i]->getBrakeTorque();
    }
}
