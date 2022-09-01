#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepVehiclesConnect()
{
    for (size_t i = 0; i < forward_inputs.size(); i++)
    {
        // Соединяемся с предыдущим вагоном
        if (prev_vehicle != Q_NULLPTR)
        {
            // Обмениваемся с сигналами предыдущего вагона
            // в соответствии с его ориентацией
            if (prev_vehicle->getOrientation() == orient)
            {
                forward_inputs[i] = prev_vehicle->getBwdOutput(i);
                prev_vehicle->setBwdInput(i, forward_outputs[i]);
            }
            else
            {
                forward_inputs[i] = prev_vehicle->getFwdOutput(i);
                prev_vehicle->setFwdInput(i, forward_outputs[i]);
            }
        }

        // Соединяемся со следующим вагоном
        if (next_vehicle != Q_NULLPTR)
        {
            // Обмениваемся с сигналами следующего вагона
            // в соответствии с его ориентацией
            if (next_vehicle->getOrientation() == orient)
            {
                next_vehicle->setFwdInput(i, backward_outputs[i]);
                backward_inputs[i] = next_vehicle->getFwdOutput(i);
            }
            else
            {
                next_vehicle->setBwdInput(i, backward_outputs[i]);
                backward_inputs[i] = next_vehicle->getBwdOutput(i);
            }
        }
    }
}
