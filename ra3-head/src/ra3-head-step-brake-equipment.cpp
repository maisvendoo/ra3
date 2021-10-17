#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeEquipment(double t, double dt)
{
    brake_module->step(t, dt);
}
