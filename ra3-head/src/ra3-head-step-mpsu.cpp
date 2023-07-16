#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepMPSU(double t, double dt)
{
    mpsu_input_t mpsu_input;
    mpsu_input.sme_train_config_fwd = sme_fwd->getSignal(SME_TRAIN_CONFIG);
    mpsu_input.sme_train_config_bwd = sme_bwd->getSignal(SME_TRAIN_CONFIG);

    mpsu_input.is_power_on = static_cast<bool>(hs_p(Ucc_110 - 90.0));

    mpsu_input.start_disel = tumbler[BUTTON_START].getState();
    mpsu_input.stop_disel = tumbler[BUTTON_STOP].getState();
    mpsu_input.start_disel_sme = (sme_fwd->getSignal(SME_DIESEL_START_STOP) == 1.0f)
                               ||(sme_bwd->getSignal(SME_DIESEL_START_STOP) == 1.0f);
    mpsu_input.stop_disel_sme = (sme_fwd->getSignal(SME_DIESEL_START_STOP) == -1.0f)
                              ||(sme_bwd->getSignal(SME_DIESEL_START_STOP) == -1.0f);
    mpsu_input.fuel_press = fuel_pump->getFuelPressure();
    mpsu_input.oil_press = disel->getOilPressure();

    mpsu_input.disel_shaft_freq = disel->getShaftFreq();

    mpsu_input.trac_min = km->getMinTracLevel();
    mpsu_input.brake_min = km->getMinBrakeLevel();

    mpsu_input.revers_state = hydro_trans->getReversState();

    mpsu_input.v_kmh = qAbs(wheel_omega[0] * wheel_diameter[0] * Physics::kmh / 2.0);

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
        // Сигнал позиции реверсора принимаем спереди наоборот, сзади правильно
        mpsu_input.revers_handle =
              - static_cast<int>(sme_fwd->getSignal(SME_REVERS_HANDLE))
              + static_cast<int>(sme_bwd->getSignal(SME_REVERS_HANDLE));

        mpsu_input.is_KM_zero =
                ( (sme_fwd->getSignal(SME_KM_STATE) + sme_bwd->getSignal(SME_KM_STATE)) == 0.0);
        mpsu_input.is_KM_traction =
                ( (sme_fwd->getSignal(SME_KM_STATE) + sme_bwd->getSignal(SME_KM_STATE)) == 1.0);
        mpsu_input.is_KM_brake =
                ( (sme_fwd->getSignal(SME_KM_STATE) + sme_bwd->getSignal(SME_KM_STATE)) == -1.0);
        mpsu_input.trac_level_KM =
                (sme_fwd->getSignal(SME_TRACTION_LEVEL) + sme_bwd->getSignal(SME_TRACTION_LEVEL));
        mpsu_input.brake_level_KM =
                (sme_fwd->getSignal(SME_BRAKE_LEVEL) + sme_bwd->getSignal(SME_BRAKE_LEVEL));

        mpsu_input.is_autostop_ON =
                static_cast<bool>(sme_fwd->getSignal(SME_IS_AUTOSTOP_ON)) ||
                static_cast<bool>(sme_bwd->getSignal(SME_IS_AUTOSTOP_ON));
    }

    // Обеспечение режима поддержания заданной скорости
    mpsu_input.button_speed_hold = button_speed_hold.getState();
    mpsu_input.button_speed_select = tumbler[BUTTON_SPEED_SELECTION].getState();
    mpsu_input.button_speed_plus = tumbler[BUTTON_SPEED_PLUS].getState();
    mpsu_input.button_speed_minus = tumbler[BUTTON_SPEED_MINUS].getState();

    mpsu_input.pBC_max = brake_module->getMaxBCpressure();

    int pos = mpsu->getOutputData().pos_in_train - 1;
    // Состояние тормозов вагонов спереди
    // Давление в ТЦ тележек от вагонов спереди принимаем в обратном порядке
    if (pos > 0)
        for (int i = 0; i < pos; i++)
        {
            int bias = (pos - i - 1) * SME_UNIT_STATE_SIZE;
            mpsu_input.unit_level_GDB[i] = sme_fwd->getSignal(SME_UNIT_GDT_BRAKE_LEVEL + bias);
            mpsu_input.unit_pBC[i * 2]     = sme_fwd->getSignal(SME_UNIT_BC2 + bias);
            mpsu_input.unit_pBC[i * 2 + 1] = sme_fwd->getSignal(SME_UNIT_BC1 + bias);
            mpsu_input.unit_spt_state[i] = static_cast<bool>(sme_fwd->getSignal(SME_UNIT_SPT_STATE + bias));
        }

    // Состояние тормозов данного вагона
    mpsu_input.unit_level_GDB[pos] = hydro_trans->getBrakeLevel();
    mpsu_input.unit_pBC[pos * 2] = brake_mech[TROLLEY_FWD]->getBCpressure();
    mpsu_input.unit_pBC[pos * 2 + 1] = brake_mech[TROLLEY_BWD]->getBCpressure();
    mpsu_input.unit_spt_state[pos] = brake_module->isParkingBraked();

    // Состояние тормозов вагонов сзади
    if (pos < MAX_TRAIN_SIZE)
        for (int i = 1; i < (MAX_TRAIN_SIZE - pos); i++)
        {
            int bias = (i - 1) * SME_UNIT_STATE_SIZE;
            mpsu_input.unit_level_GDB[pos + i] = sme_bwd->getSignal(SME_UNIT_GDT_BRAKE_LEVEL + bias);
            mpsu_input.unit_pBC[(pos + i) * 2]     = sme_bwd->getSignal(SME_UNIT_BC1 + bias);
            mpsu_input.unit_pBC[(pos + i) * 2 + 1] = sme_bwd->getSignal(SME_UNIT_BC2 + bias);
            mpsu_input.unit_spt_state[pos + i] = static_cast<bool>(sme_bwd->getSignal(SME_UNIT_SPT_STATE + bias));
        }

    mpsu_input.Kmax = brake_mech[TROLLEY_FWD]->getMaxShoeForce();
    mpsu_input.wheel_diam = wheel_diameter[0];
    mpsu_input.M_gb = hydro_trans->getBrakeTorque();
    mpsu_input.M_gb_max = hydro_trans->getMaxBrakeTorque();

    mpsu_input.is_emergency_brake =
            (brakepipe->getPressure() <= 0.3) ||
            km->isEmergencyBrake() ||
            emerg_brake_valve->isEmergencyBrake() ||
            static_cast<bool>(sme_fwd->getSignal(SME_IS_EMERGENCY_BRAKE)) ||
            static_cast<bool>(sme_bwd->getSignal(SME_IS_EMERGENCY_BRAKE));

    mpsu->setInputData(mpsu_input);
    mpsu->step(t, dt);
}
