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

    bool is_compressor_on = motor_compr->isPowered() ||
            static_cast<bool>(backward_inputs[SME_BWD_COMPRESSOR]);

    analogSignal[MFDU_COMPRESSOR] = static_cast<float>(!is_compressor_on);
    analogSignal[MFDU_COMPRESSOR_1] = static_cast<float>(!motor_compr->isPowered());
    analogSignal[MFDU_COMPRESSOR_2] = static_cast<float>(!static_cast<bool>(backward_inputs[SME_BWD_COMPRESSOR]));

    // Статус генератора
    bool is_generator_active = generator->isActive() ||
            static_cast<bool>(backward_inputs[SME_BWD_GENERATOR]);


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

    // Состояние трансмиссии (ВРЕМЕННО)
    analogSignal[MFDU_TRANSMISSION] = 1.0f;
    analogSignal[MFDU_REVERS] = static_cast<float>(mpsu->getOutputData().revers_finish);

    // Статус запрета движения (ВРЕМЕННО)
    analogSignal[MFDU_ATTENTION] = 1.0f;
    analogSignal[MFDU_STOP] = 1.0f;

    // ЭПК
    analogSignal[MFDU_EPK] = static_cast<float>(!epk->getStateKey());

    // Экстренное и стояночный тормоз
    analogSignal[MFDU_XREN1] = 1.0f;
    analogSignal[MFDU_XREN2] = 1.0f;
    analogSignal[MFDU_XREN3] = 1.0f;

    // Статус топливоподкачивающего насоса
    bool is_fuel_pump_active = fuel_pump->isStarted() ||
            static_cast<bool>(backward_inputs[SME_BWD_FUEL_PUMP_ON]);

    analogSignal[MFDU_TPN] = static_cast<float>(!is_fuel_pump_active);

    // Статус давления масла в дизеле
    analogSignal[MFDU_PRESSURE_OIL_MOTOR] = mpsu->getOutputData().mfdu_oil_press_level;

    // Общий статус дизеля
    analogSignal[MFDU_MOTOR] = mpsu->getOutputData().mfdu_disel_state_level;

    analogSignal[MFDU_PZD_MINI_LEFT] = static_cast<float>(!mpsu->getOutputData().mfdu_disel_state_level1);
    analogSignal[MFDU_PZD_MINI_RIGHT] = static_cast<float>(!mpsu->getOutputData().mfdu_disel_state_level2);

    analogSignal[MFDU_I_AKB_110] = static_cast<float>(Icc);

    analogSignal[MFDU_PRESSURE_TM] = static_cast<float>(pTM);
}
