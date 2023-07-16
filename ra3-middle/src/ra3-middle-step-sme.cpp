#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepSME(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Опрос конфигурации СМЕ
    // Отправляем сигнал вперёд от данного
    // и не более чем 4 следующих вагонов
    sme_fwd->setSignal(SME_TRAIN_CONFIG, static_cast<double>(
            SME_MULTIPLIER * (static_cast<int>(sme_bwd->getSignal(SME_TRAIN_CONFIG)) % SME_LIMIT) + SME_MIDDLE));
    // Отправляем сигнал назад от данного
    // и не более чем 4 предыдущих вагонов
    sme_bwd->setSignal(SME_TRAIN_CONFIG, static_cast<double>(
            SME_MULTIPLIER * (static_cast<int>(sme_fwd->getSignal(SME_TRAIN_CONFIG)) % SME_LIMIT) + SME_MIDDLE));

    // Пропускаем дальше все сигналы из активной кабины
    for (size_t i = SME_ACTIVE_BEGIN; i < SME_ACTIVE_BEGIN + SME_ACTIVE_SIZE; ++i)
    {
        sme_fwd->setSignal(i, sme_bwd->getSignal(i));
        sme_bwd->setSignal(i, sme_fwd->getSignal(i));
    }

    // Пропускаем сигналы состояния следующих вагонов со смещением
    for (size_t i = SME_UNIT_STATE_BEGIN + SME_UNIT_STATE_SIZE; i < NUM_RA3_SME_SIGNALS; i++)
    {
        sme_fwd->setSignal(i, sme_bwd->getSignal(i - SME_UNIT_STATE_SIZE));
        sme_bwd->setSignal(i, sme_fwd->getSignal(i - SME_UNIT_STATE_SIZE));
    }

    // Сигналы состояния данного вагона
    // Сигнал отсутствия связи CAN или номер вагона (если больше 100)
    sme_fwd->setSignal(SME_UNIT_NUM, static_cast<double>(num));
    sme_bwd->setSignal(SME_UNIT_NUM, static_cast<double>(num));

    // Температура в салоне вагона
    sme_fwd->setSignal(SME_UNIT_T, 25.1);
    sme_bwd->setSignal(SME_UNIT_T, 25.1);

    // Сигнал состояния вагонного оборудования
    sme_fwd->setSignal(SME_UNIT_EQUIP, 1.0);
    sme_bwd->setSignal(SME_UNIT_EQUIP, 1.0);

    // Давление в тормозных цилиндрах
    // Вперёд отправляем в правильном порядке
    sme_fwd->setSignal(SME_UNIT_BC1, brake_mech[TROLLEY_FWD]->getBCpressure());
    sme_fwd->setSignal(SME_UNIT_BC2, brake_mech[TROLLEY_BWD]->getBCpressure());
    // Назад отправляем в обратном порядке
    sme_bwd->setSignal(SME_UNIT_BC1, brake_mech[TROLLEY_BWD]->getBCpressure());
    sme_bwd->setSignal(SME_UNIT_BC2, brake_mech[TROLLEY_FWD]->getBCpressure());

    // Состояние дверей
    // Вперёд отправляем правильно
    sme_fwd->setSignal(SME_UNIT_DOOR_R, static_cast<double>(door_R_state));
    sme_fwd->setSignal(SME_UNIT_DOOR_L, static_cast<double>(door_L_state));
    // Назад отправляем зеркально
    sme_bwd->setSignal(SME_UNIT_DOOR_R, static_cast<double>(door_L_state));
    sme_bwd->setSignal(SME_UNIT_DOOR_L, static_cast<double>(door_R_state));

    // Состояние стояночного пружинного тормоза в ведущую секцию
    sme_fwd->setSignal(SME_UNIT_SPT_STATE, static_cast<double>(brake_module->isParkingBraked()));
    sme_bwd->setSignal(SME_UNIT_SPT_STATE, static_cast<double>(brake_module->isParkingBraked()));

    // Обнуляем сигналы отсутсвующего на вагоне оборудования
    sme_fwd->setSignal(SME_UNIT_DIESEL, 0.0);
    sme_bwd->setSignal(SME_UNIT_DIESEL, 0.0);
    sme_fwd->setSignal(SME_UNIT_FUEL_PUMP, 0.0);
    sme_bwd->setSignal(SME_UNIT_FUEL_PUMP, 0.0);
    sme_fwd->setSignal(SME_UNIT_GENERATOR, 0.0);
    sme_bwd->setSignal(SME_UNIT_GENERATOR, 0.0);
    sme_fwd->setSignal(SME_UNIT_COMPRESSOR, 0.0);
    sme_bwd->setSignal(SME_UNIT_COMPRESSOR, 0.0);
    sme_fwd->setSignal(SME_UNIT_GDT_REVERS_STATE, 0.0);
    sme_bwd->setSignal(SME_UNIT_GDT_REVERS_STATE, 0.0);
    sme_fwd->setSignal(SME_UNIT_GDT_BRAKE_LEVEL, 0.0);
    sme_bwd->setSignal(SME_UNIT_GDT_BRAKE_LEVEL, 0.0);
}
