#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepSMESignalsOutput(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)
/*
    // Опрос конфигурации СМЕ
    // Отправляем сигнал назад от данного
    // и не более чем 4 предыдущих вагонов
    backward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(
            SME_MULTIPLIER * (static_cast<int>(forward_inputs[SME_TRAIN_CONFIG]) % SME_LIMIT) + SME_MIDDLE);
    // Отправляем сигнал вперёд от данного
    // и не более чем 4 следующих вагонов
    forward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(
            SME_MULTIPLIER * (static_cast<int>(backward_inputs[SME_TRAIN_CONFIG]) % SME_LIMIT) + SME_MIDDLE);
*/
    // Пропускаем дальше все сигналы из активной кабины
    for (size_t i = SME_ACTIVE_BEGIN; i < SME_ACTIVE_BEGIN + SME_ACTIVE_SIZE; ++i)
    {
        backward_outputs[i] = forward_inputs[i];
        forward_outputs[i] = backward_inputs[i];
    }

    // Пропускаем сигналы состояния следующих вагонов со смещением
    for (size_t i = SME_UNIT_STATE_BEGIN + SME_UNIT_STATE_SIZE; i < backward_outputs.size(); i++)
    {
        backward_outputs[i] = forward_inputs[i - SME_UNIT_STATE_SIZE];
        forward_outputs[i] = backward_inputs[i - SME_UNIT_STATE_SIZE];
    }

    // Сигналы состояния данного вагона
    // Сигнал отсутствия связи CAN или номер вагона (если больше 100)
    backward_outputs[SME_UNIT_NUM] = static_cast<float>(num);
    forward_outputs[SME_UNIT_NUM] = static_cast<float>(num);

    // Температура в салоне вагона
    backward_outputs[SME_UNIT_T] = 25.1f;
    forward_outputs[SME_UNIT_T] = 25.1f;

    // Сигнал состояния вагонного оборудования
    backward_outputs[SME_UNIT_EQUIP] = 1.0f;
    forward_outputs[SME_UNIT_EQUIP] = 1.0f;

    // Давление в тормозных цилиндрах
    // Назад отправляем в обратном порядке
    // Вперёд отправляем в правильном порядке
    backward_outputs[SME_UNIT_BC1] = brake_mech[TROLLEY_BWD]->getBCpressure();
    backward_outputs[SME_UNIT_BC2] = brake_mech[TROLLEY_FWD]->getBCpressure();
    forward_outputs[SME_UNIT_BC1] = brake_mech[TROLLEY_BWD]->getBCpressure();
    forward_outputs[SME_UNIT_BC2] = brake_mech[TROLLEY_FWD]->getBCpressure();

    // Состояние дверей
    // Назад отправляем зеркально
    // Вперёд отправляем правильно
    backward_outputs[SME_UNIT_DOOR_R] = static_cast<float>(door_L_state);
    backward_outputs[SME_UNIT_DOOR_L] = static_cast<float>(door_R_state);
    forward_outputs[SME_UNIT_DOOR_R] = static_cast<float>(door_R_state);
    forward_outputs[SME_UNIT_DOOR_L] = static_cast<float>(door_L_state);

    // Состояние стояночного пружинного тормоза в ведущую секцию
    backward_outputs[SME_UNIT_SPT_STATE] = static_cast<float>(brake_module->isParkingBraked());
    forward_outputs[SME_UNIT_SPT_STATE] = static_cast<float>(brake_module->isParkingBraked());

    // Обнуляем сигналы отсуствующего на вагоне оборудования
    backward_outputs[SME_UNIT_DIESEL] = 0.0f;
    forward_outputs[SME_UNIT_DIESEL] = 0.0f;
    backward_outputs[SME_UNIT_FUEL_PUMP] = 0.0f;
    forward_outputs[SME_UNIT_FUEL_PUMP] = 0.0f;
    backward_outputs[SME_UNIT_GENERATOR] = 0.0f;
    forward_outputs[SME_UNIT_GENERATOR] = 0.0f;
    backward_outputs[SME_UNIT_COMPRESSOR] = 0.0f;
    forward_outputs[SME_UNIT_COMPRESSOR] = 0.0f;
    backward_outputs[SME_UNIT_GDT_REVERS_STATE] = 0.0f;
    forward_outputs[SME_UNIT_GDT_REVERS_STATE] = 0.0f;
    backward_outputs[SME_UNIT_GDT_BRAKE_LEVEL] = 0.0f;
    forward_outputs[SME_UNIT_GDT_BRAKE_LEVEL] = 0.0f;
}
