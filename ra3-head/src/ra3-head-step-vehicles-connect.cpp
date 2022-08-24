#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepVehiclesConnect()
{
    // Отправляем сигнал опроса конфигурации поезда
    if (prev_vehicle != Q_NULLPTR)
    {
        forward_inputs[SME_TRAIN_CONFIG] = prev_vehicle->getBwdOutput(SME_TRAIN_CONFIG);
        prev_vehicle->setBwdInput(SME_TRAIN_CONFIG, forward_outputs[SME_TRAIN_CONFIG]);
    }
    if (next_vehicle != Q_NULLPTR)
    {
        next_vehicle->setFwdInput(SME_TRAIN_CONFIG, backward_outputs[SME_TRAIN_CONFIG]);
        backward_inputs[SME_TRAIN_CONFIG] = next_vehicle->getFwdOutput(SME_TRAIN_CONFIG);
    }

    // Отправляем все остальные сигналы
    for (size_t i = 1; i < forward_inputs.size(); ++i)
    {
        // Соединяемся с предыдущим вагоном
        if (prev_vehicle != Q_NULLPTR)
        {
            forward_inputs[i] = prev_vehicle->getBwdOutput(i);
            prev_vehicle->setBwdInput(i, forward_outputs[i]);
        }

        // Соединяемся со следующим вагоном
        if (next_vehicle != Q_NULLPTR)
        {
            next_vehicle->setFwdInput(i, backward_outputs[i]);
            backward_inputs[i] = next_vehicle->getFwdOutput(i);
        }
    }
}
