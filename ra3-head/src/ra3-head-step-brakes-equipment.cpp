#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakesEquipment(double t, double dt)
{
    // Тормозная магистраль
    double BP_flow = 0.0;
    if (active_cab_relay->getContactState(1))
    {
        BP_flow += km->getBPflow();
        BP_flow += kru->getBPflow();
        BP_flow += epk->getBPflow();
    }
    BP_flow += emerg_brake_valve->getBPflow();
    BP_flow += brake_module->getBPflow();

    anglecock_bp_fwd->setHoseFlow(hose_bp_fwd->getFlow());
    BP_flow += anglecock_bp_fwd->getFlowToPipe();

    anglecock_bp_bwd->setHoseFlow(hose_bp_bwd->getFlow());
    BP_flow += anglecock_bp_bwd->getFlowToPipe();

    brakepipe->setFlow(BP_flow);
    brakepipe->step(t, dt);

    // Блок тормозного оборудования
    brake_module->setPowerVoltage(Ucc_110);
    brake_module->setRefEPBlevel(mpsu->getOutputData().brake_ref_level_EPB);
    brake_module->releaseBrakes(mpsu->getOutputData().release_PB);

    bool is_parking_braked =
            ( key_tumbler[IS_SWITCH_PARKING_BRAKE].getState() && active_cab_relay->getContactState(1) ) ||
            static_cast<bool>(sme_fwd->getSignal(SME_PARKING_BRAKE_ON)) ||
            static_cast<bool>(sme_bwd->getSignal(SME_PARKING_BRAKE_ON));
    brake_module->setParkingBrakeState(is_parking_braked);

    brake_module->setSRpressure(supply_reservoir->getPressure());
    brake_module->setBPpressure(brakepipe->getPressure());
    brake_module->setBCpressure1(brake_mech[TROLLEY_FWD]->getBCpressure());
    brake_module->setBCpressure2(brake_mech[TROLLEY_BWD]->getBCpressure());
    brake_module->setPBpressure(pb_split->getInputPressure());
    brake_module->step(t, dt);

    // Тройники
    pb_split->setInputFlow(brake_module->getPBflow());
    pb_split->setPipePressure1(brake_mech[TROLLEY_FWD]->getPBpressure());
    pb_split->setPipePressure2(brake_mech[TROLLEY_BWD]->getPBpressure());
    pb_split->step(t, dt);

    // Тормозные рычажные передачи тележек
    brake_mech[TROLLEY_FWD]->setPBflow(pb_split->getPipeFlow1());
    brake_mech[TROLLEY_FWD]->setBCflow(brake_module->getBCflow1());
    brake_mech[TROLLEY_FWD]->setAngularVelocity(0, wheel_omega[0]);
    brake_mech[TROLLEY_FWD]->setAngularVelocity(1, wheel_omega[1]);
    brake_mech[TROLLEY_FWD]->step(t, dt);

    brake_mech[TROLLEY_BWD]->setPBflow(pb_split->getPipeFlow2());
    brake_mech[TROLLEY_BWD]->setBCflow(brake_module->getBCflow2());
    brake_mech[TROLLEY_BWD]->setAngularVelocity(0, wheel_omega[2]);
    brake_mech[TROLLEY_BWD]->setAngularVelocity(1, wheel_omega[3]);
    brake_mech[TROLLEY_BWD]->step(t, dt);

    Q_r[1] = brake_mech[TROLLEY_FWD]->getBrakeTorque(0);
    Q_r[2] = brake_mech[TROLLEY_FWD]->getBrakeTorque(1);

    Q_r[3] = brake_mech[TROLLEY_BWD]->getBrakeTorque(0);
    Q_r[4] = brake_mech[TROLLEY_BWD]->getBrakeTorque(1);

    // Концевые краны тормозной магистрали
    anglecock_bp_fwd->setPipePressure(brakepipe->getPressure());
    anglecock_bp_fwd->setControl(keys);
    anglecock_bp_fwd->step(t, dt);
    anglecock_bp_bwd->setPipePressure(brakepipe->getPressure());
    //anglecock_bp_bwd->setControl(keys);
    anglecock_bp_bwd->step(t, dt);

    // Рукава тормозной магистрали
    hose_bp_fwd->setPressure(anglecock_bp_fwd->getPressureToHose());
    hose_bp_fwd->setFlowCoeff(anglecock_bp_fwd->getFlowCoeff());
    hose_bp_fwd->setCoord(train_coord + dir * orient * (length / 2.0 - anglecock_bp_fwd->getShiftCoord()));
    hose_bp_fwd->setShiftSide(anglecock_bp_fwd->getShiftSide());
    hose_bp_fwd->setControl(keys);
    hose_bp_fwd->step(t, dt);
    hose_bp_bwd->setPressure(anglecock_bp_bwd->getPressureToHose());
    hose_bp_bwd->setFlowCoeff(anglecock_bp_bwd->getFlowCoeff());
    hose_bp_bwd->setCoord(train_coord - dir * orient * (length / 2.0 - anglecock_bp_bwd->getShiftCoord()));
    hose_bp_bwd->setShiftSide(anglecock_bp_bwd->getShiftSide());
    //hose_bp_bwd->setControl(keys);
    hose_bp_bwd->step(t, dt);
}
