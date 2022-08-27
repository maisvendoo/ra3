#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::controlLampsSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    // "АКТИВНАЯ КАБИНА"
    analogSignal[ACTIVE_COCKPIT] = static_cast<float>(is_active);

    // "БАТАРЕЯ" (показывает что сеть питается от батареи)
    analogSignal[BATTERY] = static_cast<float>(hs_n(bat110->getCargeCurrent()));

    analogSignal[ALARM] = static_cast<float>(mpsu->getOutputData().is_red_alarm);
    analogSignal[ANXIETY] = static_cast<float>(mpsu->getOutputData().is_yellow_alarm);

    // Сигнализация стояночного тормоза
    analogSignal[PARKING_BRAKE] = static_cast<float>(mpsu->getOutputData().spt_state);

    // Сигнализация отпуска тележек всех вагонов,
    // кроме последней телеги хвостового вагона
    analogSignal[SOT] = static_cast<float>(mpsu->getOutputData().sot);
    // Сигнализация отпуска последней тележки хвостового вагона
    analogSignal[SOTH] = static_cast<float>(mpsu->getOutputData().soth);

    // Лампы контроля закрытия дверей
    analogSignal[KDL] = 1.0f;
    analogSignal[KDP] = 1.0f;

    // Лампы кнопок панели ПУ-4
    analogSignal[LEFT_CLOSE] = 1.0f;
    analogSignal[RIGHT_CLOSE] = 1.0f;
    analogSignal[SPEED_HOLD] = static_cast<float>(mpsu->getOutputData().is_speed_hold_ON);

    // Проверка наличия питания "БОРТСЕТЬ"
    bool is_power_on = static_cast<bool>(hs_p(Ucc_110 - 99.0));

    // Активация ламп с учетом наличия питания
    for (size_t i = ACTIVE_COCKPIT; i <= KDP; ++i)
    {
        analogSignal[i] = analogSignal[i] * static_cast<float>(is_power_on);
    }

    // Активация ламп в кнопках ПУ-4 с учетом наличия питания
    for (size_t i = SPEED_HOLD; i <= RIGHT_CLOSE; ++i)
    {
        analogSignal[i] = analogSignal[i] * static_cast<float>(is_power_on);
    }
}
