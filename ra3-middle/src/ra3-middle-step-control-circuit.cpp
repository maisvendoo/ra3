#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepControlCircuit(double t, double dt)
{
    U_bat_110 = bat110->getVoltage();
    Ucc_110 = static_cast<double>(KM_power->getContactState(1)) * U_bat_110;

    bat110->step(t, dt);

    KM_power->setVoltage(U_bat_110 * forward_inputs[SME_BWD_POWER_ON]);
    KM_power->step(t, dt);
}
