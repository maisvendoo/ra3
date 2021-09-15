#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepFuelSystem(double t, double dt)
{
    for (FuelTank *fuel_tank : fuel_tank)
    {
        fuel_tank->setFuelConsumption(0.0);
        fuel_tank->step(t, dt);
    }
}
