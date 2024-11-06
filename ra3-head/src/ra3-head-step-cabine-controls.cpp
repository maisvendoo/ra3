#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepCabineControls(double t, double dt)
{
    // Включение реле активной кабины
    // Если другие активные кабины в составе - отключаем и не проверяем включение
    if ( (sme_fwd->getSignal(SME_NO_ACTIVE) != 0.0) ||
         (sme_bwd->getSignal(SME_NO_ACTIVE) != 0.0) )
    {
        active_cab_relay->setVoltage(0.0);
    }
    else
    {
        // Включаем вместе с борсетью и проверяем самоподпитку
        bool is_active = tumbler[IS_BUTTON_PWR_ON].getState() ||
                         active_cab_relay->getContactState(0);

        // Подаём напряжение для включения
        active_cab_relay->setVoltage(Ucc_110 * static_cast<double>(is_active));
    }
    active_cab_relay->step(t, dt);

    // Контроллер машиниста
    km->setControl(keys);
    km->setFwdKey(tumbler[IS_SWITCH_REVERS_FWD].getState());
    km->setBwdKey(tumbler[IS_SWITCH_REVERS_BWD].getState());
    km->setBPpressure(static_cast<double>(active_cab_relay->getContactState(0)) * brakepipe->getPressure());
    km->step(t, dt);
}
