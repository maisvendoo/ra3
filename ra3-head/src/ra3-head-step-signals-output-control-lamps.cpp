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
    // кроме последней тележки хвостового вагона
    analogSignal[SOT] = static_cast<float>(mpsu->getOutputData().sot);
    // Сигнализация отпуска последней тележки хвостового вагона
    analogSignal[SOTH] = static_cast<float>(mpsu->getOutputData().soth);

    // Лампы контроля закрытия дверей
    bool kdp = (door_R_state == 1);
    bool kdl = (door_L_state == 1);
    int pos = mpsu->getOutputData().pos_in_train - 1;
    // Проверяем состояние дверей вагонов спереди, принимаем сигналы зеркально
    if (pos > 0)
        for (int i = 0; i < pos; i++)
        {
            int bias = (pos - i - 1) * SME_UNIT_STATE_SIZE;
            kdp &= (sme_fwd->getSignal(SME_UNIT_DOOR_L + bias) == 1.0);
            kdl &= (sme_fwd->getSignal(SME_UNIT_DOOR_R + bias) == 1.0);
        }
    // Проверяем состояние дверей вагонов сзади
    if (pos < mpsu->getOutputData().train_size)
        for (int i = 1; i < (mpsu->getOutputData().train_size - pos); i++)
        {
            int bias = (i - 1) * SME_UNIT_STATE_SIZE;
            kdp &= (sme_bwd->getSignal(SME_UNIT_DOOR_R + bias) == 1.0);
            kdl &= (sme_bwd->getSignal(SME_UNIT_DOOR_L + bias) == 1.0);
        }

    analogSignal[KDL] = static_cast<float>(kdl);
    analogSignal[KDP] = static_cast<float>(kdp);

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
