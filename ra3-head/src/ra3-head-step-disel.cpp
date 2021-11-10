#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepDisel(double t, double dt)
{
    if (is_active)
        disel->setRefFreq(mpsu->getOutputData().n_ref);
    else
        disel->setRefFreq(forward_inputs[SME_DISEL_FREQ]);

    disel->setMV6state(mpsu->getOutputData().is_fuel_valve1_open ||
                       static_cast<bool>(forward_inputs[SME_BWD_FUEL_VALVE_OPEN]));

    disel->setFuelLevel((fuel_tank[0]->getFuelLevel() + fuel_tank[1]->getFuelLevel()) / 2.0);
    disel->setFuelPressure(fuel_pump->getFuelPressure());
    disel->setStarterTorque(starter->getTorque() * static_cast<double>(starter_relay->getContactState(0)));
    disel->setGenTorque(hydro_trans->getInputTorque());
    disel->step(t, dt);

    starter->setVoltage(Ucc_24 * static_cast<double>(starter_relay->getContactState(1)));
    starter->setOmega(disel->getStarterOmega() * static_cast<double>(starter_relay->getContactState(0)));
    starter->step(t, dt);

    bool is_starter_ralay_ON = mpsu->getOutputData().is_starter1_ON ||
            static_cast<bool>(forward_inputs[SME_BWD_STARTER_ON]);

    starter_relay->setVoltage(Ucc_24 * static_cast<double>(is_starter_ralay_ON));
    starter_relay->step(t, dt);
}
