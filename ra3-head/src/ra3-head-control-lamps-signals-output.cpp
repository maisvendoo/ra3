#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::controlLampsSignalsOutput(double t, double dt)
{
    // "АКТИВНАЯ КАБИНА"
    analogSignal[ACTIVE_COCKPIT] = static_cast<float>(is_active);

    // "БАТАРЕЯ" (показывает что сеть питается от батареи)
    analogSignal[BATTERY] = static_cast<float>(hs_n(bat110->getCargeCurrent()));

    analogSignal[ALARM] = static_cast<float>(mpsu->getOutputData().is_red_alarm);
    analogSignal[ANXIETY] = static_cast<float>(mpsu->getOutputData().is_yellow_alarm);

    analogSignal[PARKING_BRAKE] = static_cast<float>(brake_mech[FWD_TROLLEY]->isParkingBrake());

    // Проверка наличия питания "БОРТСЕТЬ"
    bool is_power_on = static_cast<bool>(hs_p(Ucc - 99.0));

    // Активация ламп с учетом наличия питания
    for (size_t i = ACTIVE_COCKPIT; i <= KDP; ++i)
    {
        analogSignal[i] = analogSignal[i] && is_power_on;
    }
}
