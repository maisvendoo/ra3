#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepMPSU(double t, double dt)
{
    mpsu_input_t mpsu_input;
    mpsu_input.is_power_on = static_cast<bool>(hs_p(Ucc - 90.0));
    mpsu_input.start_disel = tumbler[BUTTON_START].getState();
    mpsu_input.stop_disel = tumbler[BUTTON_STOP].getState();
    mpsu_input.fuel_press1 = fuel_pump->getFuelPressure();
    mpsu_input.fuel_press2 = static_cast<double>(backward_inputs[SME_BWD_FUEL_PRESS]);
    mpsu_input.oil_press1 = disel->getOilPressure();
    mpsu_input.oil_press2 = static_cast<double>(backward_inputs[SME_BWD_OIL_PRESS]);
    mpsu_input.disel1_shaft_freq = disel->getShaftFreq();
    mpsu_input.disel2_shaft_freq = static_cast<double>(backward_inputs[SME_BWD_OMEGA]);
    mpsu_input.trac_min = km->getMinTracLevel();
    mpsu_input.brake_min = km->getMinBrakeLevel();

    mpsu_input.trac_level_KM = km->getTractionLevel() + forward_inputs[SME_KM_TRACTION_LEVEL];
    mpsu_input.brake_level_KM = km->getBrakeLevel() + forward_inputs[SME_KM_BRAKE_LEVEL];

    mpsu_input.revers_state1 = hydro_trans->getReversState();
    mpsu_input.revers_state2 = static_cast<int>(backward_inputs[SME_REVERS_STATE]);
    mpsu_input.is_autostop_ON = epk->getStateKey();

    mpsu_input.revers_handle = static_cast<int>(km->getReversHandlePos()) +
            static_cast<int>(forward_inputs[SME_REVERS_HANDLE]);

    mpsu_input.is_parking_braked1 = brake_module->isParkingBraked();
    mpsu_input.is_parking_braked2 = static_cast<bool>(backward_inputs[SME_PARKING_BRAKE_STATE]);
    mpsu_input.v_kmh = qAbs(wheel_omega[0] * wheel_diameter * Physics::kmh / 2.0);

    if (is_active)
    {
        mpsu_input.is_KM_zero = km->isZero();
        mpsu_input.is_KM_brake = km->isBrake();
        mpsu_input.is_KM_traction = km->isTraction();
    }
    else
    {
        mpsu_input.is_KM_zero = static_cast<bool>(forward_inputs[SME_IS_KM_ZERO]);
        mpsu_input.is_KM_brake = static_cast<bool>(forward_inputs[SME_IS_KM_BRAKE]);
        mpsu_input.is_KM_traction = static_cast<bool>(forward_inputs[SME_IS_KM_TRACTION]);
    }

    mpsu_input.pBC_max = brake_module->getMaxBrakeCylinderPressure();
    mpsu_input.brake_level_GB1 = hydro_trans->getBrakeLevel();
    mpsu_input.brake_level_GB2 = backward_inputs[SME_BWD_BRAKE_LEVEL];

    mpsu_input.pBC[0] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
    mpsu_input.pBC[1] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
    mpsu_input.pBC[2] = backward_inputs[SME_BWD_BC1];
    mpsu_input.pBC[3] = backward_inputs[SME_BWD_BC2];

    mpsu_input.Kmax = brake_mech[FWD_TROLLEY]->getMaxShoeForce();
    mpsu_input.wheel_diam = wheel_diameter;
    mpsu_input.M_gb = hydro_trans->getBrakeTorque();
    mpsu_input.M_gb_max = hydro_trans->getMaxBrakeTorque();

    mpsu_input.is_emergency_brake = emerg_brake_valve->isEmergencyBrake() ||
            km->isEmergencyBrake() ||
            static_cast<float>(forward_inputs[SME_IS_EMERGENCY_BRAKE]) ||
            (pTM <= 0.3);

    // Обеспечение режима поддержания заданной скорости
    mpsu_input.button_speed_hold = button_speed_hold.getState();
    mpsu_input.button_speed_select = tumbler[BUTTON_SPEED_SELECTION].getState();
    mpsu_input.button_speed_plus = tumbler[BUTTON_SPEED_PLUS].getState();
    mpsu_input.button_speed_minus = tumbler[BUTTON_SPEED_MINUS].getState();

    mpsu->setInputData(mpsu_input);
    mpsu->step(t, dt);    
}
