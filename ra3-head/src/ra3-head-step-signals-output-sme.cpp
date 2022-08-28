#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSMESignalsOutput(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Напряжение зарядки АКБ на промежуточный вагон
    backward_outputs[SME_FWD_CHARGE_VOLTAGE] = aux_conv->getU_110();
    forward_outputs[SME_BWD_CHARGE_VOLTAGE] = aux_conv->getU_110();

    // Давление в ПМ для промежуточного вагона
    backward_outputs[SME_FWD_PM_PRESSURE] = main_res->getPressure();
    forward_outputs[SME_BWD_PM_PRESSURE] = main_res->getPressure();

    // Обнуляем опрос конфигурации СМЕ
    backward_outputs[SME_TRAIN_CONFIG] = 0.0f;
    forward_outputs[SME_TRAIN_CONFIG] = 0.0f;

    // Сигналы из активной кабины
    if (is_active)
    {
        // Опрос конфигурации СМЕ
        // Отправляем назад отрицательный сигнал -1
        backward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(SME_HEAD_BWD);
        // Отправляем вперёд отрицательный сигнал -2
        forward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(SME_HEAD_FWD);

        // КОСТЫЛЬ под нынешнюю реализацию brakepipe.
        // Если активная кабина не в начале,
        // то передаем давление от тормозного крана в сигналы СМЕ,
        // чтобы установить давление в начале тормозной магистрали.
        if (idx > 0)
        {
            backward_outputs[SME_P0] = kru->getBrakePipeInitPressure();
            forward_outputs[SME_P0] = kru->getBrakePipeInitPressure();
        }

        // Сигнал включения контактора "Бортсеть" на ведомые секции
        backward_outputs[SME_POWER_ON] = static_cast<float>(KM_power->getContactState(2));
        forward_outputs[SME_POWER_ON] = static_cast<float>(KM_power->getContactState(2));

        // Сигнал запрета включать другие кабины
        backward_outputs[SME_NO_ACTIVE] = 1.0f;
        forward_outputs[SME_NO_ACTIVE] = 1.0f;

        // Сигнал запуска дизеля на ведомые секции
        backward_outputs[SME_DISEL_START] = static_cast<float>(mpsu->getOutputData().start_press_count == 1);
        forward_outputs[SME_DISEL_START] = static_cast<float>(mpsu->getOutputData().start_press_count == 1);

        // Сигнал остановки дизеля на ведомые секции
        backward_outputs[SME_DISEL_STOP] = static_cast<float>(mpsu->getOutputData().stop_diesel);
        forward_outputs[SME_DISEL_STOP] = static_cast<float>(mpsu->getOutputData().stop_diesel);

        // Сигнал работы ЭПК на ведомые секции
        backward_outputs[SME_IS_AUTOSTOP_ON] = epk->getStateKey();
        forward_outputs[SME_IS_AUTOSTOP_ON] = epk->getStateKey();

        // Сигнал позиции реверсора на ведомые секции
        backward_outputs[SME_REVERS_HANDLE] = km->getReversHandlePos();
        forward_outputs[SME_REVERS_HANDLE] = km->getReversHandlePos();

        // Сигналы блок-контактов КМ на ведомые секции
        backward_outputs[SME_KM_STATE] = static_cast<float>(km->isTraction()) - static_cast<float>(km->isBrake());
        forward_outputs[SME_KM_STATE] = static_cast<float>(km->isTraction()) - static_cast<float>(km->isBrake());

        // Уровень тяги от КМ на ведомые секции
        backward_outputs[SME_KM_TRACTION_LEVEL] = max(km->getTractionLevel(), mpsu->getOutputData().trac_level);
        forward_outputs[SME_KM_TRACTION_LEVEL] = max(km->getTractionLevel(), mpsu->getOutputData().trac_level);

        // Уровень торможения от КМ на ведомые секции
        backward_outputs[SME_KM_BRAKE_LEVEL] = max(km->getBrakeLevel(), mpsu->getOutputData().brake_level);
        forward_outputs[SME_KM_BRAKE_LEVEL] = max(km->getBrakeLevel(), mpsu->getOutputData().brake_level);

        // Заданный уровень торможения ЭПТ на ведомые секции
        backward_outputs[SME_REF_BRAKE_LEVEL_EPB] = static_cast<float>(mpsu->getOutputData().brake_ref_level_EPB);
        forward_outputs[SME_REF_BRAKE_LEVEL_EPB] = static_cast<float>(mpsu->getOutputData().brake_ref_level_EPB);

        // Сигнал отпуска тормозов (КЭБ) на ведомые секции и промежуточные вагоны
        backward_outputs[SME_BRAKE_RELEASE] = static_cast<float>(mpsu->getOutputData().release_PB);
        forward_outputs[SME_BRAKE_RELEASE] = static_cast<float>(mpsu->getOutputData().release_PB);

        // Сигнал управления стояночным тормозом на ведомые секции
        backward_outputs[SME_PARKING_BRAKE_ON] = static_cast<float>(tumbler[SWITCH_PARKING_BRAKE].getState());
        forward_outputs[SME_PARKING_BRAKE_ON] = static_cast<float>(tumbler[SWITCH_PARKING_BRAKE].getState());

        // Сигнал экстренного торможения на ведомые секции
        backward_outputs[SME_IS_EMERGENCY_BRAKE] = static_cast<float>(
                    emerg_brake_valve->isEmergencyBrake() ||
                    km->isEmergencyBrake());
        forward_outputs[SME_IS_EMERGENCY_BRAKE] = static_cast<float>(
                    emerg_brake_valve->isEmergencyBrake() ||
                    km->isEmergencyBrake());
    }
    else
    {
        if (forward_inputs[SME_TRAIN_CONFIG] < 0)
        {
            // Если спереди получен отрицательный сигнал от активной кабины,
            // отправляемый назад, то ориентация совпадает
            is_orient_same = (static_cast<int>(forward_inputs[SME_TRAIN_CONFIG]) == SME_HEAD_BWD);

            // Отправляем сигнал к следующим вагонам
            backward_outputs[SME_TRAIN_CONFIG] = forward_inputs[SME_TRAIN_CONFIG];

            // Обратно отправляем сигнал от данного и следующих вагонов
            forward_outputs[SME_TRAIN_CONFIG] = 4 * backward_inputs[SME_TRAIN_CONFIG];
            if (is_orient_same)
                forward_outputs[SME_TRAIN_CONFIG] += static_cast<float>(SME_HEAD_ORIENT_SAME);
            else
                forward_outputs[SME_TRAIN_CONFIG] += static_cast<float>(SME_HEAD_ORIENT_OPPOSITE);

            // Обратно отправляем сигналы состояния следующих вагонов
            for (size_t i = SME_UNIT_STATE_BEGIN + SME_UNIT_STATE_SIZE; i < forward_outputs.size(); i++)
                forward_outputs[i] = backward_inputs[i - SME_UNIT_STATE_SIZE];
        }

        if (backward_inputs[SME_TRAIN_CONFIG] < 0)
        {
            // Если сзади получен отрицательный сигнал от активной кабины,
            // отправляемый вперёд, то ориентация совпадает
            is_orient_same = (static_cast<int>(backward_inputs[SME_TRAIN_CONFIG]) == SME_HEAD_FWD);

            // Отправляем сигнал к следующим вагонам
            forward_outputs[SME_TRAIN_CONFIG] = backward_inputs[SME_TRAIN_CONFIG];

            // Обратно отправляем сигнал от данного и следующих вагонов
            backward_outputs[SME_TRAIN_CONFIG] = 4 * forward_inputs[SME_TRAIN_CONFIG];
            if (is_orient_same)
                backward_outputs[SME_TRAIN_CONFIG] += static_cast<float>(SME_HEAD_ORIENT_SAME);
            else
                backward_outputs[SME_TRAIN_CONFIG] += static_cast<float>(SME_HEAD_ORIENT_OPPOSITE);

            // Обратно отправляем сигналы состояния следующих вагонов
            for (size_t i = SME_UNIT_STATE_BEGIN + SME_UNIT_STATE_SIZE; i < backward_outputs.size(); i++)
                backward_outputs[i] = forward_inputs[i - SME_UNIT_STATE_SIZE];
        }

        // Пропускаем дальше все сигналы из активной кабины
        for (size_t i = SME_ACTIVE_BEGIN; i < SME_ACTIVE_BEGIN + SME_ACTIVE_SIZE; ++i)
        {
            backward_outputs[i] = forward_inputs[i];
            forward_outputs[i] = backward_inputs[i];
        }

        // Пропускаем дальше сигнал-костыль p0
        backward_outputs[SME_P0] = forward_inputs[SME_P0];
        forward_outputs[SME_P0] = backward_inputs[SME_P0];

        // Сигнал номера вагона или отсутствия связи CAN в ведущую секцию
        backward_outputs[SME_UNIT_NUM] = static_cast<float>(num);
        forward_outputs[SME_UNIT_NUM] = static_cast<float>(num);

        // Сигнал температуры в салоне вагона в ведущую секцию
        backward_outputs[SME_UNIT_T] = 25.1f;
        forward_outputs[SME_UNIT_T] = 25.1f;

        // Сигнал состояния вагонного оборудования в ведущую секцию
        backward_outputs[SME_UNIT_EQUIP] = 1.0f;
        forward_outputs[SME_UNIT_EQUIP] = 1.0f;

        // Сигнал состояния дизеля в ведущую секцию
        backward_outputs[SME_UNIT_DIESEL] = static_cast<float>(mpsu->getOutputData().mfdu_disel_state_level + 1);
        forward_outputs[SME_UNIT_DIESEL] = static_cast<float>(mpsu->getOutputData().mfdu_disel_state_level + 1);

        // Передаем состояние топливного насоса в ведущую секцию
        backward_outputs[SME_UNIT_FUEL_PUMP] = static_cast<float>(fuel_pump->isStarted());
        forward_outputs[SME_UNIT_FUEL_PUMP] = static_cast<float>(fuel_pump->isStarted());

        // Передаем состояние генератора в ведущую секцию
        backward_outputs[SME_UNIT_GENERATOR] = static_cast<float>(generator->isActive());
        forward_outputs[SME_UNIT_GENERATOR] = static_cast<float>(generator->isActive());

        // Передаем состояние компрессора в ведущую секцию
        backward_outputs[SME_UNIT_COMPRESSOR] = static_cast<float>(motor_compr->isPowered());
        forward_outputs[SME_UNIT_COMPRESSOR] = static_cast<float>(motor_compr->isPowered());

        // Передаем состояние гидропередачи в ведущую секцию
        backward_outputs[SME_UNIT_GDT_REVERS_STATE] = hydro_trans->getReversState();
        forward_outputs[SME_UNIT_GDT_REVERS_STATE] = hydro_trans->getReversState();
        backward_outputs[SME_UNIT_GDT_BRAKE_LEVEL] = hydro_trans->getBrakeLevel();
        forward_outputs[SME_UNIT_GDT_BRAKE_LEVEL] = hydro_trans->getBrakeLevel();

        if (is_orient_same)
        {
            // Передаем давление в тормозных цилиндрах в ведущую секцию
            backward_outputs[SME_UNIT_BC1] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
            forward_outputs[SME_UNIT_BC1] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
            backward_outputs[SME_UNIT_BC2] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
            forward_outputs[SME_UNIT_BC2] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
            // Передаем состояние дверей в ведущую секцию
            backward_outputs[SME_UNIT_DOOR_R] = static_cast<float>(door_R_state);
            forward_outputs[SME_UNIT_DOOR_R] = static_cast<float>(door_R_state);
            backward_outputs[SME_UNIT_DOOR_L] = static_cast<float>(door_L_state);
            forward_outputs[SME_UNIT_DOOR_L] = static_cast<float>(door_L_state);
        }
        else
        {
            // Передаем давление в тормозных цилиндрах в ведущую секцию
            backward_outputs[SME_UNIT_BC1] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
            forward_outputs[SME_UNIT_BC1] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
            backward_outputs[SME_UNIT_BC2] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
            forward_outputs[SME_UNIT_BC2] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
            // Передаем состояние дверей в ведущую секцию
            backward_outputs[SME_UNIT_DOOR_R] = static_cast<float>(door_L_state);
            forward_outputs[SME_UNIT_DOOR_R] = static_cast<float>(door_L_state);
            backward_outputs[SME_UNIT_DOOR_L] = static_cast<float>(door_R_state);
            forward_outputs[SME_UNIT_DOOR_L] = static_cast<float>(door_R_state);
        }

        // Передаем состояние стояночного пружинного тормоза в ведущую секцию
        backward_outputs[SME_UNIT_SPT_STATE] = static_cast<float>(brake_module->isParkingBraked());
        forward_outputs[SME_UNIT_SPT_STATE] = static_cast<float>(brake_module->isParkingBraked());
    }
}
