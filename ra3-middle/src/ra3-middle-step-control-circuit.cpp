#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepControlCircuit(double t, double dt)
{
    U_bat_110 = bat110->getVoltage();
    Ucc_110 = static_cast<double>(KM_power->getContactState(1)) * U_bat_110;

    double U_charge_110 = max(sme_fwd->getSignal(SME_CHARGE_VOLTAGE),
                              sme_bwd->getSignal(SME_CHARGE_VOLTAGE) );

    double Icc_110 = Ucc_110 / 22.0;

    bat110->setLoadCurrent(Icc_110);
    bat110->setChargeVoltage(U_charge_110);
    bat110->step(t, dt);

    bool is_KM_bat_110 = static_cast<bool>(sme_fwd->getSignal(SME_POWER_ON))
                      || static_cast<bool>(sme_bwd->getSignal(SME_POWER_ON));

    KM_power->setVoltage(U_bat_110 * static_cast<double>(is_KM_bat_110));
    KM_power->step(t, dt);
}
