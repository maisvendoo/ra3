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

    bool is_parking_braked = brake_module->isParkingBraked() &&
            static_cast<bool>(backward_inputs[SME_PARKING_BRAKE_STATE]);

    // Сигнализация стояночного тормоза
    analogSignal[PARKING_BRAKE] = static_cast<float>(is_parking_braked);

    // Сигнализация отпуска тележек всех вагонов, кроме последней телеги
    // хвостового вагона
    analogSignal[SOT] = (brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure() < 0.04) &&
            (brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure() < 0.04) &&
            (backward_inputs[SME_BWD_BC1] < 0.04);

    // Сигнализация отпуска последней тележки хвостового вагона
    analogSignal[SOTH] = (backward_inputs[SME_BWD_BC1] < 0.04);

    // Лампы контроля закрытия дверей
    analogSignal[KDL] = 1.0f;
    analogSignal[KDP] = 1.0f;

    // Лампы кнопок панели ПУ-4
    analogSignal[LEFT_CLOSE] = 1.0f;
    analogSignal[RIGHT_CLOSE] = 1.0f;
    analogSignal[SPEED_HOLD] = static_cast<float>(mpsu->getOutputData().is_speed_hold_ON);

    // Проверка наличия питания "БОРТСЕТЬ"
    bool is_power_on = static_cast<bool>(hs_p(Ucc - 99.0));

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
