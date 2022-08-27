#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepMPSU(double t, double dt)
{
    mpsu_input_t mpsu_input;
    mpsu_input.is_power_on = static_cast<bool>(hs_p(Ucc_110 - 90.0));
    mpsu_input.orient = orient;
    mpsu_input.sme_train_config_fwd = forward_inputs[SME_TRAIN_CONFIG];
    mpsu_input.sme_train_config_bwd = backward_inputs[SME_TRAIN_CONFIG];

    mpsu_input.start_disel = tumbler[BUTTON_START].getState();
    mpsu_input.stop_disel = tumbler[BUTTON_STOP].getState();
    mpsu_input.start_disel_sme =
            static_cast<bool>(backward_inputs[SME_DISEL_START] == 1.0f) ||
            static_cast<bool>(forward_inputs[SME_DISEL_START] == 1.0f);
    mpsu_input.stop_disel_sme =
            static_cast<bool>(backward_inputs[SME_DISEL_STOP] == 1.0f) ||
            static_cast<bool>(forward_inputs[SME_DISEL_STOP] == 1.0f);

    mpsu_input.fuel_press = fuel_pump->getFuelPressure();
    mpsu_input.oil_press = disel->getOilPressure();

    mpsu_input.disel_shaft_freq = disel->getShaftFreq();

    mpsu_input.trac_min = km->getMinTracLevel();
    mpsu_input.brake_min = km->getMinBrakeLevel();

    mpsu_input.revers_state = hydro_trans->getReversState();

    mpsu_input.v_kmh = qAbs(wheel_omega[0] * wheel_diameter * Physics::kmh / 2.0);

    if (is_active)
    {
        mpsu_input.revers_handle = static_cast<int>(km->getReversHandlePos());
        mpsu_input.is_KM_zero = km->isZero();
        mpsu_input.is_KM_traction = km->isTraction();
        mpsu_input.is_KM_brake = km->isBrake();
        mpsu_input.trac_level_KM = km->getTractionLevel();
        mpsu_input.brake_level_KM = km->getBrakeLevel();

        mpsu_input.is_autostop_ON = epk->getStateKey();
    }
    else
    {
        if (mpsu->getOutputData().is_orient_same)
            mpsu_input.revers_handle =
                static_cast<int>(backward_inputs[SME_REVERS_HANDLE]) +
                static_cast<int>(forward_inputs[SME_REVERS_HANDLE]);
        else
            mpsu_input.revers_handle = -1 * (
                static_cast<int>(backward_inputs[SME_REVERS_HANDLE]) +
                static_cast<int>(forward_inputs[SME_REVERS_HANDLE]));
        mpsu_input.is_KM_zero =
                static_cast<bool>((backward_inputs[SME_KM_STATE] + forward_inputs[SME_KM_STATE]) == 0.0f);
        mpsu_input.is_KM_traction =
                static_cast<bool>((backward_inputs[SME_KM_STATE] + forward_inputs[SME_KM_STATE]) == 1.0f);
        mpsu_input.is_KM_brake =
                static_cast<bool>((backward_inputs[SME_KM_STATE] + forward_inputs[SME_KM_STATE]) == -1.0f);
        mpsu_input.trac_level_KM =
                static_cast<double>(forward_inputs[SME_KM_TRACTION_LEVEL]) +
                static_cast<double>(backward_inputs[SME_KM_TRACTION_LEVEL]);
        mpsu_input.brake_level_KM =
                static_cast<double>(forward_inputs[SME_KM_BRAKE_LEVEL]) +
                static_cast<double>(backward_inputs[SME_KM_BRAKE_LEVEL]);

        mpsu_input.is_autostop_ON =
                static_cast<bool>(backward_inputs[SME_IS_AUTOSTOP_ON]) ||
                static_cast<bool>(forward_inputs[SME_IS_AUTOSTOP_ON]);
    }

    // Обеспечение режима поддержания заданной скорости
    mpsu_input.button_speed_hold = button_speed_hold.getState();
    mpsu_input.button_speed_select = tumbler[BUTTON_SPEED_SELECTION].getState();
    mpsu_input.button_speed_plus = tumbler[BUTTON_SPEED_PLUS].getState();
    mpsu_input.button_speed_minus = tumbler[BUTTON_SPEED_MINUS].getState();

    mpsu_input.pBC_max = brake_module->getMaxBrakeCylinderPressure();
    mpsu_input.unit_level_GDB[0] = hydro_trans->getBrakeLevel();
    mpsu_input.unit_pBC[0] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
    mpsu_input.unit_pBC[1] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
    mpsu_input.unit_spt_state[0] = brake_module->isParkingBraked();

    for (size_t i = 1; i < MAX_TRAIN_SIZE; i++)
    {
        mpsu_input.unit_level_GDB[i] =
                static_cast<double>(forward_inputs[SME_UNIT_GDT_BRAKE_LEVEL + (i - 1) * SME_UNIT_STATE_SIZE]) +
                static_cast<double>(backward_inputs[SME_UNIT_GDT_BRAKE_LEVEL + (i - 1) * SME_UNIT_STATE_SIZE]);
        mpsu_input.unit_pBC[i * 2] =
                static_cast<double>(forward_inputs[SME_UNIT_BC1 + (i - 1) * SME_UNIT_STATE_SIZE]) +
                static_cast<double>(backward_inputs[SME_UNIT_BC1 + (i - 1) * SME_UNIT_STATE_SIZE]);
        mpsu_input.unit_pBC[i * 2 + 1] =
                static_cast<double>(forward_inputs[SME_UNIT_BC2 + (i - 1) * SME_UNIT_STATE_SIZE]) +
                static_cast<double>(backward_inputs[SME_UNIT_BC2 + (i - 1) * SME_UNIT_STATE_SIZE]);
        mpsu_input.unit_spt_state[i] =
                static_cast<bool>(backward_inputs[SME_UNIT_SPT_STATE + (i - 1) * SME_UNIT_STATE_SIZE]) ||
                static_cast<bool>(forward_inputs[SME_UNIT_SPT_STATE + (i - 1) * SME_UNIT_STATE_SIZE]);
    }

    mpsu_input.Kmax = brake_mech[FWD_TROLLEY]->getMaxShoeForce();
    mpsu_input.wheel_diam = wheel_diameter;
    mpsu_input.M_gb = hydro_trans->getBrakeTorque();
    mpsu_input.M_gb_max = hydro_trans->getMaxBrakeTorque();

    mpsu_input.is_emergency_brake =
            (pTM <= 0.3) ||
            km->isEmergencyBrake() ||
            emerg_brake_valve->isEmergencyBrake() ||
            static_cast<float>(backward_inputs[SME_IS_EMERGENCY_BRAKE]) ||
            static_cast<float>(forward_inputs[SME_IS_EMERGENCY_BRAKE]);

    mpsu->setInputData(mpsu_input);
    mpsu->step(t, dt);
}
