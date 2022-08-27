#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeEquipment(double t, double dt)
{
    bool is_parking_braked =
            (is_active && tumbler[SWITCH_PARKING_BRAKE].getState()) ||
            static_cast<bool>(backward_inputs[SME_PARKING_BRAKE_ON]) ||
            static_cast<bool>(forward_inputs[SME_PARKING_BRAKE_ON]);

    brake_module->setRefPressureLevel(mpsu->getOutputData().brake_ref_level_EPB);
    brake_module->releaseBrakes(mpsu->getOutputData().release_PB);

    brake_module->setVoltage(Ucc_110);
    brake_module->setParkingBrakeState(is_parking_braked);
    brake_module->setBrakeCylinderPressure(bc_split->getP_in());
    brake_module->setBrakepipePressure(pTM);
    brake_module->setAirSupplyPressure(aux_res->getPressure());
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

    if (is_active)
    {
        emerg_brake_valve->setControl(keys);
        emerg_brake_valve->setBrakePipePressure(pTM);
        emerg_brake_valve->step(t, dt);
    }

    auxRate = epk->getEmergencyBrakeRate() +
            emerg_brake_valve->getEmergencyRate() +
            km->getEmergencyRate();
}
