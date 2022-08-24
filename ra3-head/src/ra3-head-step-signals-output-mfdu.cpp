#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::mdfuSignalsOutput(double t, double dt)
{
    analogSignal[MFDU_DISPLAY_ON] = static_cast<float>(mpsu->getOutputData().is_display_ON);

    analogSignal[MFDU_REVERS_FWD] = static_cast<float>(!mpsu->getOutputData().revers_fwd);
    analogSignal[MFDU_REVERS_BWD] = static_cast<float>(!mpsu->getOutputData().revers_bwd);
    analogSignal[MFDU_REVERS_NEUTRAL] = static_cast<float>(!mpsu->getOutputData().revers_neutral);

    analogSignal[MFDU_PRESSURE_PM] = static_cast<float>(main_res->getPressure());

    // Статус компрессора
    bool is_compressor2_on =
            !static_cast<bool>(backward_inputs[SME_BWD_COMPRESSOR]) ||
            !static_cast<bool>(forward_inputs[SME_BWD_COMPRESSOR]);
    bool is_compressor_on = motor_compr->isPowered() || is_compressor2_on;
    analogSignal[MFDU_COMPRESSOR] = static_cast<float>(!is_compressor_on);
    analogSignal[MFDU_COMPRESSOR_1] = static_cast<float>(!motor_compr->isPowered());
    analogSignal[MFDU_COMPRESSOR_2] = static_cast<float>(!is_compressor2_on);


    // Статус генератора
    bool is_generator_active = generator->isActive() ||
            static_cast<bool>(backward_inputs[SME_BWD_GENERATOR]) ||
            static_cast<bool>(forward_inputs[SME_BWD_GENERATOR]);
    analogSignal[MFDU_GENERATOR] = static_cast<float>(!is_generator_active);

    // Неактивные подсистемы
    analogSignal[MFDU_VIP] = 1.0f;
    analogSignal[MFDU_FIRE] = 1.0f;
    analogSignal[MFDU_WC] = 1.0f;
    analogSignal[MFDU_DOOR] = 1.0f;
    analogSignal[MFDU_PZD] = 3.0f;
    analogSignal[MFDU_PUMP] = 2.0f;
    analogSignal[MFDU_PTF] = 1.0f;
    analogSignal[MFDU_ANTY_YUZ] = 2.0f;
    analogSignal[MFDU_PZD] = 3.0f;
    analogSignal[MFDU_PVU] = 1.0f;
    analogSignal[MFDU_OZ] = 2.0f;
    analogSignal[MFDU_INC_OZ_MOTOR] = 2.0f;
    analogSignal[MFDU_OIL_MOTOR] = 2.0f;
    analogSignal[MFDU_DEC_OZ_MOTOR] = 2.0f;
    analogSignal[MFDU_ACTIVE_CHARGE] = 3.0f;

    analogSignal[MFDU_CAN_RIGHT] = static_cast<float>(
                 static_cast<bool>(backward_inputs[SME_BWD_CAN]) ||
                 static_cast<bool>(forward_inputs[SME_BWD_CAN]));

    analogSignal[MFDU_BRAKES_LEFT] = 1.0f;
    analogSignal[MFDU_BRAKES_RIGHT] = 1.0f;

    // Состояние трансмиссии (ВРЕМЕННО)
    analogSignal[MFDU_TRANSMISSION] = 1.0f;
    analogSignal[MFDU_REVERS] = static_cast<float>(
                static_cast<int>(km->getReversHandlePos()) == hydro_trans->getReversState());

    // Статус запрета движения (ВРЕМЕННО)
    if (mpsu->getOutputData().motion_disable)
    {
        if (!km->isTraction())
        {
            analogSignal[MFDU_ATTENTION] = 0.0f;
            analogSignal[MFDU_STOP] = 1.0f;
        }
        else
        {
            analogSignal[MFDU_ATTENTION] = 0.0f;
            analogSignal[MFDU_STOP] = 0.0f;
        }
    }
    else
    {
        analogSignal[MFDU_ATTENTION] = 1.0f;
        analogSignal[MFDU_STOP] = 1.0f;
    }

    // ЭПК
    analogSignal[MFDU_EPK] = static_cast<float>(!epk->getStateKey());

    // Экстренное
    analogSignal[MFDU_XREN1] = static_cast<float>(!(km->isEmergencyBrake() || emerg_brake_valve->isEmergencyBrake()));

    // СПТ
    bool is_parking_braked = mpsu->getOutputData().is_parking_braked;
    analogSignal[MFDU_XREN2] = static_cast<float>(!is_parking_braked);

    // Удерживающий тормоз
    analogSignal[MFDU_XREN3] = static_cast<float>(!mpsu->getOutputData().is_holding_braked);

    // Статус топливоподкачивающего насоса
    bool is_fuel_pump_active = fuel_pump->isStarted() ||
            static_cast<bool>(backward_inputs[SME_BWD_FUEL_PUMP_ON]) ||
            static_cast<bool>(forward_inputs[SME_BWD_FUEL_PUMP_ON]);
    analogSignal[MFDU_TPN] = static_cast<float>(!is_fuel_pump_active);

    // Статус давления масла в дизеле
    analogSignal[MFDU_PRESSURE_OIL_MOTOR] = mpsu->getOutputData().mfdu_oil_press_level;

    // Общий статус дизеля
    analogSignal[MFDU_MOTOR] = mpsu->getOutputData().mfdu_disel_state_level;

    analogSignal[MFDU_PZD_MINI_LEFT] = static_cast<float>(!mpsu->getOutputData().mfdu_disel_state_level1);
    analogSignal[MFDU_PZD_MINI_RIGHT] = static_cast<float>(!mpsu->getOutputData().mfdu_disel_state_level2);

    analogSignal[MFDU_I_AKB_110] = static_cast<float>(Icc_110);
    analogSignal[MFDU_I_AKB_24] = static_cast<float>(Icc_24);

    analogSignal[MFDU_PRESSURE_TM] = static_cast<float>(pTM);

    analogSignal[MFDU_S_SPEED_LIMIT] = static_cast<float>(blok->getCurrentSpeedLimit());
    analogSignal[MFDU_S_SPEED] = static_cast<float>(blok->getVelocityKmh());

    analogSignal[MFDU_TRACTION_BRAKING] = static_cast<float>(100.0 * (km->getTractionLevel() + mpsu->getOutputData().auto_trac_level) * hydro_trans->getTractionLevel()
                                                             - 100 * mpsu->getOutputData().brake_level);

    analogSignal[MFDU_ERROR_CODE] = static_cast<float>(mpsu->getOutputData().error_code);

    analogSignal[MFDU_PRESSURE_TC_MIN] = mpsu->getOutputData().pBC_min;
    analogSignal[MFDU_PRESSURE_TC_MAX] = mpsu->getOutputData().pBC_max;

    analogSignal[MFDU_BRAKES_LEFT] = mpsu->getOutputData().brake_type1;
    analogSignal[MFDU_BRAKES_RIGHT] = mpsu->getOutputData().brake_type1;

    analogSignal[MFDU_TEMPERATURE_KAB] = 25.1f;

    analogSignal[MFDU_S_GREEN_DIGIT] = mpsu->getOutputData().v_ref_kmh;
}
