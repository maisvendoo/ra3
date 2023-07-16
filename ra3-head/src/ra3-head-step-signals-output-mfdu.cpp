#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::mdfuSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    analogSignal[MFDU_DISPLAY_ON] = static_cast<float>(mpsu->getOutputData().is_display_ON);

    analogSignal[MFDU_REVERS_FWD] = static_cast<float>(!mpsu->getOutputData().revers_fwd);
    analogSignal[MFDU_REVERS_BWD] = static_cast<float>(!mpsu->getOutputData().revers_bwd);
    analogSignal[MFDU_REVERS_NEUTRAL] = static_cast<float>(!mpsu->getOutputData().revers_neutral);

    analogSignal[MFDU_PRESSURE_PM] = static_cast<float>(main_reservoir->getPressure());


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
    bool is_parking_braked = mpsu->getOutputData().spt_state;
    analogSignal[MFDU_XREN2] = static_cast<float>(!is_parking_braked);

    // Удерживающий тормоз
    analogSignal[MFDU_XREN3] = static_cast<float>(!mpsu->getOutputData().is_holding_braked);

    // Статус давления масла в дизеле
    analogSignal[MFDU_PRESSURE_OIL_MOTOR] = mpsu->getOutputData().mfdu_oil_press_level;

    analogSignal[MFDU_I_AKB_110] = static_cast<float>(Icc_110);
    analogSignal[MFDU_I_AKB_24] = static_cast<float>(Icc_24);

    analogSignal[MFDU_PRESSURE_TM] = static_cast<float>(brakepipe->getPressure());

    analogSignal[MFDU_S_SPEED_LIMIT] = static_cast<float>(min(120.0, blok->getCurrentSpeedLimit()));
    analogSignal[MFDU_S_SPEED] = static_cast<float>(Physics::kmh * wheel_omega[0] * wheel_diameter[0] / 2.0);

    analogSignal[MFDU_TRACTION_BRAKING] = static_cast<float>(100.0 * (mpsu->getOutputData().trac_level) * hydro_trans->getTractionLevel()
                                                              - 100 * mpsu->getOutputData().brake_level);

    analogSignal[MFDU_ERROR_CODE] = static_cast<float>(mpsu->getOutputData().error_code);

    analogSignal[MFDU_PRESSURE_TC_MIN] = mpsu->getOutputData().pBC_min;
    analogSignal[MFDU_PRESSURE_TC_MAX] = mpsu->getOutputData().pBC_max;

    analogSignal[MFDU_TEMPERATURE_KAB] = 25.1f;

    analogSignal[MFDU_S_GREEN_DIGIT] = mpsu->getOutputData().v_ref_kmh;

    analogSignal[MFDU_TRAIN_SIZE] = static_cast<float>(mpsu->getOutputData().train_size);
    analogSignal[MFDU_POS_IN_TRAIN] = static_cast<float>(mpsu->getOutputData().pos_in_train);

    // Конфигурация поезда и состояние тормозов из МПСУ
    for (size_t i = 0; i < MAX_TRAIN_SIZE; i++)
    {
        analogSignal[MFDU_TRAIN_UNIT + i * MFDU_UNIT_SIGNALS_SIZE] =
                static_cast<float>(mpsu->getOutputData().train_config[i]);
        analogSignal[MFDU_TRAIN_UNIT_BRAKES + i * MFDU_UNIT_SIGNALS_SIZE] =
                static_cast<float>(mpsu->getOutputData().unit_brakes[i]);
    }

    int pos = mpsu->getOutputData().pos_in_train - 1;
    bool is_generator_active = false;
    bool is_fuel_pump_active = false;
    // Состояние вагонов спереди
    // Состояние дверей спереди принимаем зеркально
    if (pos > 0)
        for (int i = 0; i < pos; i++)
        {
            int bias_mfdu = i * MFDU_UNIT_SIGNALS_SIZE;
            int bias_sme = (pos - i - 1) * SME_UNIT_STATE_SIZE;
            analogSignal[MFDU_TRAIN_UNIT_NUM + bias_mfdu] =
                    static_cast<float>(sme_fwd->getSignal(SME_UNIT_NUM + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_DOOR_R + bias_mfdu] =
                    static_cast<float>(sme_fwd->getSignal(SME_UNIT_DOOR_L + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_DOOR_L + bias_mfdu] =
                    static_cast<float>(sme_fwd->getSignal(SME_UNIT_DOOR_R + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_T + bias_mfdu] =
                    static_cast<float>(sme_fwd->getSignal(SME_UNIT_T + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_EQUIP + bias_mfdu] =
                    static_cast<float>(sme_fwd->getSignal(SME_UNIT_EQUIP + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_DIESEL + bias_mfdu] =
                    static_cast<float>(sme_fwd->getSignal(SME_UNIT_DIESEL + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_COMPRESSOR + bias_mfdu] =
                    static_cast<float>(sme_fwd->getSignal(SME_UNIT_COMPRESSOR + bias_sme));
            is_generator_active |= static_cast<bool>(sme_fwd->getSignal(SME_UNIT_GENERATOR + bias_sme));
            is_fuel_pump_active |= static_cast<bool>(sme_fwd->getSignal(SME_UNIT_FUEL_PUMP + bias_sme));
        }

    // Состояние данного вагона
    int bias_mfdu = pos * MFDU_UNIT_SIGNALS_SIZE;
    analogSignal[MFDU_TRAIN_UNIT_NUM + bias_mfdu] = static_cast<float>(num);
    analogSignal[MFDU_TRAIN_UNIT_DOOR_R + bias_mfdu] = static_cast<float>(door_R_state);
    analogSignal[MFDU_TRAIN_UNIT_DOOR_L + bias_mfdu] = static_cast<float>(door_L_state);
    analogSignal[MFDU_TRAIN_UNIT_T + bias_mfdu] = 25.1f;
    analogSignal[MFDU_TRAIN_UNIT_EQUIP + bias_mfdu] = 1.0f;
    analogSignal[MFDU_TRAIN_UNIT_DIESEL + bias_mfdu] = static_cast<float>(mpsu->getOutputData().mfdu_disel_state_level + 1);
    analogSignal[MFDU_TRAIN_UNIT_COMPRESSOR + bias_mfdu] = static_cast<float>(motor_compressor->isPowered());
    is_generator_active |= generator->isActive();
    is_fuel_pump_active |= fuel_pump->isStarted();

    // Состояние вагонов сзади
    if (pos < MAX_TRAIN_SIZE)
        for (int i = 1; i < (MAX_TRAIN_SIZE - pos); i++)
        {
            int bias_mfdu = (pos + i) * MFDU_UNIT_SIGNALS_SIZE;
            int bias_sme = (i - 1) * SME_UNIT_STATE_SIZE;
            analogSignal[MFDU_TRAIN_UNIT_NUM + bias_mfdu] =
                    static_cast<float>(sme_bwd->getSignal(SME_UNIT_NUM + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_DOOR_R + bias_mfdu] =
                    static_cast<float>(sme_bwd->getSignal(SME_UNIT_DOOR_R + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_DOOR_L + bias_mfdu] =
                    static_cast<float>(sme_bwd->getSignal(SME_UNIT_DOOR_L + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_T + bias_mfdu] =
                    static_cast<float>(sme_bwd->getSignal(SME_UNIT_T + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_EQUIP + bias_mfdu] =
                    static_cast<float>(sme_bwd->getSignal(SME_UNIT_EQUIP + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_DIESEL + bias_mfdu] =
                    static_cast<float>(sme_bwd->getSignal(SME_UNIT_DIESEL + bias_sme));
            analogSignal[MFDU_TRAIN_UNIT_COMPRESSOR + bias_mfdu] =
                    static_cast<float>(sme_bwd->getSignal(SME_UNIT_COMPRESSOR + bias_sme));
            is_generator_active |= static_cast<bool>(sme_bwd->getSignal(SME_UNIT_GENERATOR + bias_sme));
            is_fuel_pump_active |= static_cast<bool>(sme_bwd->getSignal(SME_UNIT_FUEL_PUMP + bias_sme));
        }

    // Статус генератора
    analogSignal[MFDU_GENERATOR] = static_cast<float>(!is_generator_active);
    // Статус топливоподкачивающего насоса
    analogSignal[MFDU_TPN] = static_cast<float>(!is_fuel_pump_active);

}
