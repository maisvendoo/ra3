#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepDisel(double t, double dt)
{
    double U_bat24 = bat24->getVoltage();

    disel->setRefFreq(800);
    disel->setMV6state(true);
    disel->setFuelLevel((fuel_tank[0]->getFuelLevel() + fuel_tank[1]->getFuelLevel()) / 2.0);
    disel->setFuelPressure(fuel_pump->getFuelPressure());
    disel->setStarterTorque(starter->getTorque() * static_cast<double>(starter_relay->getContactState(0)));
    disel->step(t, dt);

    // Передаем давление масла в ведущую секцию
    forward_outputs[SME_BWD_OIL_PRESS] = static_cast<float>(disel->getOilPressure());

    starter->setVoltage(U_bat24 * static_cast<double>(starter_relay->getContactState(1)));
    starter->setOmega(disel->getStarterOmega() * static_cast<double>(starter_relay->getContactState(0)));
    starter->step(t, dt);

    bool is_starter_ralay_ON = mpsu->getOutputData().is_starter1_ON;

    starter_relay->setVoltage(U_bat24 * static_cast<double>(is_starter_ralay_ON));
    starter_relay->step(t, dt);
}
