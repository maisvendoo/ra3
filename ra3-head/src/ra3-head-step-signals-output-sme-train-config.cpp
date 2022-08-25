#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSMETrainConfig(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)
    backward_outputs[SME_TRAIN_CONFIG] = 0.0f;
    forward_outputs[SME_TRAIN_CONFIG] = 0.0f;

    if (is_active)
    {
        // Отправляем в обе стороны отрицательный сигнал с ориентацией кабины
        if (orient > 0)
        {
            backward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(SME_HEAD_ORIENT_FWD);
            forward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(SME_HEAD_ORIENT_FWD);
        }
        else
        {
            backward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(SME_HEAD_ORIENT_BWD);
            forward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(SME_HEAD_ORIENT_BWD);
        }
    }
    else
    {
        // Определяем, с какой стороны пришёл отрицательный сигнал от активной кабины
        if (forward_inputs[SME_TRAIN_CONFIG] < 0)
        {
            // Отправляем сигнал к следующим вагонам
            backward_outputs[SME_TRAIN_CONFIG] = forward_inputs[SME_TRAIN_CONFIG];

            // Обратно отправляем сигнал от данного и следующих вагонов
            forward_outputs[SME_TRAIN_CONFIG] =
                    4 * backward_inputs[SME_TRAIN_CONFIG] +
                    mpsu->getOutputData().sme_train_config;
        }

        if (backward_inputs[SME_TRAIN_CONFIG] < 0)
        {
            // Отправляем сигнал к следующим вагонам
            forward_outputs[SME_TRAIN_CONFIG] = backward_inputs[SME_TRAIN_CONFIG];

            // Обратно отправляем сигнал от данного и следующих вагонов
            backward_outputs[SME_TRAIN_CONFIG] =
                    4 * forward_inputs[SME_TRAIN_CONFIG] +
                    mpsu->getOutputData().sme_train_config;
        }
    }
}
