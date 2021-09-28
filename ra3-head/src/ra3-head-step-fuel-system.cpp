#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepFuelSystem(double t, double dt)
{
    double common_fuel_level = 0.0;

    for (FuelTank *fuel_tank : fuel_tank)
    {
        fuel_tank->setFuelConsumption(0.0);
        fuel_tank->step(t, dt);
        common_fuel_level += fuel_tank->getFuelLevel();
    }

    fuel_pump->setFuelLevel(common_fuel_level / 2.0);
    fuel_pump->step(t, dt);
}
