#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepSMESignalsOutput(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Обнуляем опрос конфигурации СМЕ
    backward_outputs[SME_TRAIN_CONFIG] = 0.0f;
    forward_outputs[SME_TRAIN_CONFIG] = 0.0f;

    // Ориентация вагона
    float sme_input = min(forward_inputs[SME_TRAIN_CONFIG], forward_inputs[SME_TRAIN_CONFIG]);
    if ((sme_input < 0) && (((orient > 0) && (sme_input > -1.5f )) ||
                            ((orient < 0) && (sme_input < -1.5f ))))
        is_orient_same = true;
    else
        is_orient_same = false;

    // Определяем, с какой стороны пришёл отрицательный сигнал от активной кабины
    if (forward_inputs[SME_TRAIN_CONFIG] < 0)
    {
        // Отправляем сигнал к следующим вагонам
        backward_outputs[SME_TRAIN_CONFIG] = forward_inputs[SME_TRAIN_CONFIG];

        // Обратно отправляем сигнал от данного и следующих вагонов
        forward_outputs[SME_TRAIN_CONFIG] =
                4 * backward_inputs[SME_TRAIN_CONFIG] +
                static_cast<float>(SME_MIDDLE);
    }

    if (backward_inputs[SME_TRAIN_CONFIG] < 0)
    {
        // Отправляем сигнал к следующим вагонам
        forward_outputs[SME_TRAIN_CONFIG] = backward_inputs[SME_TRAIN_CONFIG];

        // Обратно отправляем сигнал от данного и следующих вагонов
        backward_outputs[SME_TRAIN_CONFIG] =
                4 * forward_inputs[SME_TRAIN_CONFIG] +
                static_cast<float>(SME_MIDDLE);
    }

    for (size_t i = SME_UNIT_STATE_BEGIN + SME_UNIT_STATE_SIZE; i < backward_outputs.size(); i++)
    {
        backward_outputs[i] = forward_inputs[i - SME_UNIT_STATE_SIZE];
        forward_outputs[i] = backward_inputs[i - SME_UNIT_STATE_SIZE];
    }

    // Пропускаем дальше все сигналы из активной кабины
    for (size_t i = SME_ACTIVE_BEGIN; i < SME_ACTIVE_BEGIN + SME_ACTIVE_SIZE; i++)
    {
        forward_outputs[i] = backward_inputs[i];
        backward_outputs[i] = forward_inputs[i];
    }

    // Пропускаем дальше сигнал-костыль p0
    backward_outputs[SME_P0] = forward_inputs[SME_P0];
    forward_outputs[SME_P0] = backward_inputs[SME_P0];

    // Сигнал номера вагона или отсутствия связи CAN в ведущую секцию
    backward_outputs[SME_UNIT_NUM] = 4003.0f;
    forward_outputs[SME_UNIT_NUM] = 4003.0f;

    // Сигнал температуры в салоне вагона в ведущую секцию
    backward_outputs[SME_UNIT_T] = 25.1f;
    forward_outputs[SME_UNIT_T] = 25.1f;

    // Сигнал состояния вагонного оборудования в ведущую секцию
    backward_outputs[SME_UNIT_EQUIP] = 1.0f;
    forward_outputs[SME_UNIT_EQUIP] = 1.0f;

    // Передаем давление в тормозных цилиндрах в ведущую секцию
    if (is_orient_same)
    {
        backward_outputs[SME_UNIT_BC1] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
        forward_outputs[SME_UNIT_BC1] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
        backward_outputs[SME_UNIT_BC2] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
        forward_outputs[SME_UNIT_BC2] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
    }
    else
    {
        backward_outputs[SME_UNIT_BC1] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
        forward_outputs[SME_UNIT_BC1] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
        backward_outputs[SME_UNIT_BC2] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
        forward_outputs[SME_UNIT_BC2] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
    }

    // Передаем состояние стояночного пружинного тормоза в ведущую секцию
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
