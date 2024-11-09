#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::controlLampsSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    // Контрольные лампы на блоке индикации БИ-4

    // Проверка наличия питания "БОРТСЕТЬ"
    if ((Ucc_110 - 99.0) < 0.0)
    {
        analogSignal[INDICATOR_DOORS_CLOSED_L] = 0.0f;
        analogSignal[INDICATOR_DOORS_CLOSED_R] = 0.0f;
        analogSignal[INDICATOR_PARKING_BRAKE] = 0.0f;
        analogSignal[INDICATOR_BATTERY] = 0.0f;
        analogSignal[INDICATOR_OVERHEATING_AXLE_BOXES] = 0.0f;
        analogSignal[INDICATOR_RELEASE_BRAKES] = 0.0f;
        analogSignal[INDICATOR_ALARM_LOW] = 0.0f;
        analogSignal[INDICATOR_RELEASE_BRAKES_TAIL] = 0.0f;
        analogSignal[INDICATOR_ALARM_HIGH] = 0.0f;
        analogSignal[INDICATOR_ACTIVE_CABINE] = 0.0f;
        return;
    }

    // Лампы контроля закрытия дверей
    bool kdp = (door_R->getDoorControlState() == 1);
    bool kdl = (door_L->getDoorControlState() == 1);
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
    analogSignal[INDICATOR_DOORS_CLOSED_L] = static_cast<float>(kdl);
    analogSignal[INDICATOR_DOORS_CLOSED_R] = static_cast<float>(kdp);

    // Сигнализация стояночного тормоза
    analogSignal[INDICATOR_PARKING_BRAKE] = static_cast<float>(mpsu->getOutputData().spt_state);

    // "БАТАРЕЯ" (показывает что сеть питается от батареи)
    analogSignal[INDICATOR_BATTERY] = static_cast<float>(hs_n(bat110->getChargeCurrent()));

    // Сигнализация перегрева букс
    analogSignal[INDICATOR_OVERHEATING_AXLE_BOXES] = 0.0f;

    // Сигнализация отпуска тележек всех вагонов,
    // кроме последней тележки хвостового вагона
    analogSignal[INDICATOR_RELEASE_BRAKES] = static_cast<float>(mpsu->getOutputData().sot);

    // Тревога - предупреждение
    analogSignal[INDICATOR_ALARM_LOW] = static_cast<float>(mpsu->getOutputData().is_yellow_alarm);

    // Сигнализация отпуска последней тележки хвостового вагона
    analogSignal[INDICATOR_RELEASE_BRAKES_TAIL] = static_cast<float>(mpsu->getOutputData().soth);

    // Тревога - авария
    analogSignal[INDICATOR_ALARM_HIGH] = static_cast<float>(mpsu->getOutputData().is_red_alarm);

    // "АКТИВНАЯ КАБИНА"
    analogSignal[INDICATOR_ACTIVE_CABINE] = static_cast<float>(active_cab_relay->getContactState(1));
}
