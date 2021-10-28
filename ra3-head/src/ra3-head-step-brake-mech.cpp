#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeMech(double t, double dt)
{
    brake_mech[FWD_TROLLEY]->setParkingBrakeAirFlow(pb_split->getQ_out1());
    brake_mech[BWD_TROLLEY]->setParkingBrakeAirFlow(pb_split->getQ_out2());

    brake_mech[FWD_TROLLEY]->setAirFlow(bc_split->getQ_out1());
    brake_mech[BWD_TROLLEY]->setAirFlow(bc_split->getQ_out2());

    Q_r[1] = brake_mech[FWD_TROLLEY]->getBrakeTorque();
    Q_r[2] = brake_mech[FWD_TROLLEY]->getBrakeTorque();

    Q_r[3] = brake_mech[BWD_TROLLEY]->getBrakeTorque();
    Q_r[4] = brake_mech[BWD_TROLLEY]->getBrakeTorque();

    for (size_t i = 0; i < brake_mech.size(); ++i)
    {
        brake_mech[i]->step(t, dt);        
    }
}
