#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::mdfuSignalsOutput(double t, double dt)
{
    analogSignal[MFDU_DISPLAY_ON] = static_cast<float>(mpsu->getOutputData().is_display_ON);

    analogSignal[MFDU_REVERS_FWD] = static_cast<float>(mpsu->getOutputData().revers_fwd);
    analogSignal[MFDU_REVERS_BWD] = static_cast<float>(mpsu->getOutputData().revers_bwd);
    analogSignal[MFDU_REVERS_NEUTRAL] = static_cast<float>(mpsu->getOutputData().revers_neutral);

    analogSignal[MFDU_PRESSURE_PM] = static_cast<float>(main_res->getPressure());

    bool is_compressor_on = motor_compr->isPowered() ||
            static_cast<bool>(backward_inputs[SME_BWD_COMPRESSOR]);

    analogSignal[MFDU_COMPRESSOR] = static_cast<float>(!is_compressor_on);
    analogSignal[MFDU_COMPRESSOR_1] = static_cast<float>(!motor_compr->isPowered());
    analogSignal[MFDU_COMPRESSOR_2] = static_cast<float>(!static_cast<bool>(backward_inputs[SME_BWD_COMPRESSOR]));

    bool is_generator_active = generator->isActive() ||
            static_cast<bool>(backward_inputs[SME_BWD_GENERATOR]);

    analogSignal[MFDU_GENERATOR] = static_cast<float>(!is_generator_active);

    analogSignal[MFDU_VIP] = 1.0f;
    analogSignal[MFDU_FIRE] = 1.0f;
    analogSignal[MFDU_WC] = 1.0f;
}
