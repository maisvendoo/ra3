#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepControlCircuit(double t, double dt)
{
    U_bat_110 = bat110->getVoltage();
    Ucc_110 = static_cast<double>(KM_power->getContactState(1)) * U_bat_110;

    U_bat_24 = bat24->getVoltage();
    Ucc_24 = static_cast<double>(KM_power->getContactState(2) * U_bat_24);

    Icc_110 = Ucc_110 / 22.0;

    Icc_24 = Ucc_24 / 4.16 + starter->getCurrent();

    bat110->setLoadCurrent(Icc_110);
    bat110->setChargeVoltage(aux_conv->getU_110());
    bat110->step(t, dt);

    bat24->setLoadCurrent(Icc_24);
    bat24->setChargeVoltage(aux_conv->getU_27());
    bat24->step(t, dt);

    // Включение контактора "Бортсеть"
    bool is_KM_bat_110 = tumbler[BUTTON_PWR_ON].getState() ||
            (tumbler[BUTTON_PWR_OFF].getState() && KM_power->getContactState(0)) ||
            static_cast<bool>(backward_inputs[SME_BWD_POWER_ON]) ||
            static_cast<bool>(forward_inputs[SME_BWD_POWER_ON]);

    KM_power->setVoltage(U_bat_110 * static_cast<double>(is_KM_bat_110));
    KM_power->step(t, dt);

    // Главный генератор
    generator->setHydroStaticPress(hydro_pump->getPressure());
    generator->step(t, dt);

    // ПСН
    aux_conv->setPowerON(mpsu->getOutputData().is_disel1_started ||
                         static_cast<bool>(backward_inputs[SME_BWD_DISEL_STARTED])||
                         static_cast<bool>(forward_inputs[SME_BWD_DISEL_STARTED]));

    aux_conv->setBatteryVoltage(Ucc_110);
    aux_conv->setInputVoltage(generator->getVoltage());
    aux_conv->step(t, dt);
}
