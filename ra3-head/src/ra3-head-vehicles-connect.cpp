#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepVehiclesConnect()
{
    for (size_t i = 0; i < forward_inputs.size(); ++i)
    {
        // Соединяемся с предыдущим вагоном
        if (prev_vehicle != Q_NULLPTR)
        {
            float tmp = prev_vehicle->getBwdOutput(i);
            forward_inputs[i] = tmp;
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
