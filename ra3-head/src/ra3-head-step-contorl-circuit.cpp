#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepControlCircuit(double t, double dt)
{
    U_bat_110 = bat110->getVoltage();
    Ucc = static_cast<double>(KM_bat_110->getContactState(1)) * U_bat_110;

    bat110->step(t, dt);

    bat24->step(t, dt);

    bool is_KM_bat_110 = tumbler[BUTTON_PWR_ON].getState() ||
            (tumbler[BUTTON_PWR_OFF].getState() && KM_bat_110->getContactState(0)) ||
            static_cast<bool>(forward_inputs[SME_POWER_ON]);

    backward_outputs[SME_POWER_ON] = static_cast<float>(tumbler[BUTTON_PWR_ON].getState());

    KM_bat_110->setVoltage(U_bat_110 * static_cast<double>(is_KM_bat_110));
    KM_bat_110->step(t, dt);    
}
