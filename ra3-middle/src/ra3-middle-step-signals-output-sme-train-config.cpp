#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepSMETrainConfig(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)
    backward_outputs[SME_TRAIN_CONFIG] = 0.0f;
    forward_outputs[SME_TRAIN_CONFIG] = 0.0f;

    // Определяем, с какой стороны пришёл отрицательный сигнал от активной кабины
    if (forward_inputs[SME_TRAIN_CONFIG] < 0)
    {
        // Отправляем сигнал к следующим вагонам
        backward_outputs[SME_TRAIN_CONFIG] = forward_inputs[SME_TRAIN_CONFIG];

        // Обратно отправляем сигнал от данного и следующих вагонов
        forward_outputs[SME_TRAIN_CONFIG] =
                4 * backward_inputs[SME_TRAIN_CONFIG] +
                static_cast<float>(SME_MIDDLE);
    }

    if (backward_inputs[SME_TRAIN_CONFIG] < 0)
    {
        // Отправляем сигнал к следующим вагонам
        forward_outputs[SME_TRAIN_CONFIG] = backward_inputs[SME_TRAIN_CONFIG];

        // Обратно отправляем сигнал от данного и следующих вагонов
        backward_outputs[SME_TRAIN_CONFIG] =
                4 * forward_inputs[SME_TRAIN_CONFIG] +
                static_cast<float>(SME_MIDDLE);
    }
}
