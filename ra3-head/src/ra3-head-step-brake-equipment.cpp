#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeEquipment(double t, double dt)
{
    bool is_parking_braked = tumbler[SWITCH_PARKING_BRAKE].getState() ||
            static_cast<bool>(forward_inputs[SME_PARKING_BRAKE]);

    brake_module->setVoltage(Ucc);
    brake_module->setParkingBrakeState(is_parking_braked);
    brake_module->setBrakeCylinderPressure(0.0);
    brake_module->setBrakepipePressure(pTM);
    brake_module->setAirSupplyPressure(aux_res->getPressure());
    brake_module->setParkingBrakePressure(pb_split->getP_in());
    brake_module->step(t, dt);

    pb_split->setQ_in(brake_module->getParkingBrakeAirFlow());
    pb_split->setP_out1(brake_mech[FWD_TROLLEY]->getParkingBrakePressure());
    pb_split->setP_out2(brake_mech[BWD_TROLLEY]->getParkingBrakePressure());
    pb_split->step(t, dt);
}
