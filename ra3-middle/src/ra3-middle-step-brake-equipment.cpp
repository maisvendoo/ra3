#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepBrakeEquipment(double t, double dt)
{


    pb_split->setQ_in(brake_module->getParkingBrakeAirFlow());
    pb_split->setP_out1(brake_mech[FWD_TROLLEY]->getParkingBrakePressure());
    pb_split->setP_out2(brake_mech[BWD_TROLLEY]->getParkingBrakePressure());
    pb_split->step(t, dt);

    bc_split->setQ_in(brake_module->getBrakeCylinderAirFlow());
    bc_split->setP_out1(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure());
    bc_split->setP_out2(brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure());
    bc_split->step(t, dt);
}
