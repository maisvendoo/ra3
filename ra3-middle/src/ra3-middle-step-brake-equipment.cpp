#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepBrakeEquipment(double t, double dt)
{
    bool is_parking_braked = static_cast<bool>(forward_inputs[SME_PARKING_BRAKE_ON]);

    brake_module->setVoltage(Ucc_110);
    brake_module->setParkingBrakeState(is_parking_braked);
    brake_module->setBrakeCylinderPressure(bc_split->getP_in());
    brake_module->setBrakepipePressure(pTM);

    // ДОБАВИТЬ ЗАПАСНЫЙ РЕЗЕРВУАР!!!!
    //brake_module->setAirSupplyPressure(aux_res->getPressure());

    brake_module->setParkingBrakePressure(pb_split->getP_in());
    brake_module->step(t, dt);

    pb_split->setQ_in(brake_module->getParkingBrakeAirFlow());
    pb_split->setP_out1(brake_mech[FWD_TROLLEY]->getParkingBrakePressure());
    pb_split->setP_out2(brake_mech[BWD_TROLLEY]->getParkingBrakePressure());
    pb_split->step(t, dt);

    bc_split->setQ_in(brake_module->getBrakeCylinderAirFlow());
    bc_split->setP_out1(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure());
    bc_split->setP_out2(brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure());
    bc_split->step(t, dt);
}
