#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepVehiclesConnect()
{
    for (size_t i = 0; i < forward_inputs.size(); ++i)
    {
        forward_outputs[i] = backward_inputs[i];

        if (prev_vehicle != Q_NULLPTR)
        {
            forward_inputs[i] = prev_vehicle->getBwdOutput(i);
            prev_vehicle->setBwdInput(i, forward_outputs[i]);
        }

        backward_outputs[i] = forward_inputs[i];

        if (next_vehicle != Q_NULLPTR)
        {
            next_vehicle->setFwdInput(i, backward_outputs[i]);
            backward_inputs[i] = next_vehicle->getFwdOutput(i);
        }
    }
}
