#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepDisel(double t, double dt)
{
    disel->setRefFreq(mpsu->getOutputData().n_ref);
    disel->setMV6state(mpsu->getOutputData().is_fuel_valve_open);

    disel->setFuelLevel((fuel_tank[0]->getFuelLevel() + fuel_tank[1]->getFuelLevel()) / 2.0);
    disel->setFuelPressure(fuel_pump->getFuelPressure());
    disel->setStarterTorque(starter->getTorque() * static_cast<double>(starter_relay->getContactState(0)));
    disel->setGenTorque(hydro_trans->getInputTorque());
    disel->step(t, dt);

    starter->setVoltage(Ucc_24 * static_cast<double>(starter_relay->getContactState(1)));
    starter->setOmega(disel->getStarterOmega() * static_cast<double>(starter_relay->getContactState(0)));
    starter->step(t, dt);

    starter_relay->setVoltage(Ucc_24 * static_cast<double>(mpsu->getOutputData().is_starter_ON));
    starter_relay->step(t, dt);
}
