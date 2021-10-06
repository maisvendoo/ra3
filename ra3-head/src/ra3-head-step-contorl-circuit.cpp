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

    // Включение контактора "Бортсеть"
    bool is_KM_bat_110 = tumbler[BUTTON_PWR_ON].getState() ||
            (tumbler[BUTTON_PWR_OFF].getState() && KM_bat_110->getContactState(0)) ||
           static_cast<bool>(forward_inputs[SME_BWD_POWER_ON]);

    // Сигнал включения контактора "Бортсеть" на ведомую секцию
    backward_outputs[SME_BWD_POWER_ON] = static_cast<float>(KM_bat_110->getContactState(2));

    KM_bat_110->setVoltage(U_bat_110 * static_cast<double>(is_KM_bat_110));
    KM_bat_110->step(t, dt);    

    // Сигнал включения топливного насоса на ведомом дизеле
    backward_outputs[SME_BWD_FUEL_PUMP] = static_cast<float>(mpsu->getOutputData().is_fuel_pump2_ON);

    // Сигнал включения стартера на ведомом дизеле
    backward_outputs[SME_BWD_STARTER_ON] = static_cast<float>(mpsu->getOutputData().is_starter2_ON);

    // Сигнал открытия топливного клапана на ведомом дизеле
    backward_outputs[SME_BWD_FUEL_VALVE_OPEN] = static_cast<float>(mpsu->getOutputData().is_fuel_valve2_open);

    // Главный генератор
    generator->setDiselOmega(disel->getOmega());
    generator->step(t, dt);

    // ПСН
    if (is_active)
        aux_conv->setPowerON(mpsu->getOutputData().is_disel1_started);
    else
        aux_conv->setPowerON(mpsu->getOutputData().is_disel2_started);

    aux_conv->setBatteryVoltage(Ucc);
    aux_conv->setInputVoltage(generator->getVoltage());
    aux_conv->step(t, dt);
}
