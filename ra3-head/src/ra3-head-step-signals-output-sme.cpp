#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSMESignalsOutput(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Напряжение зарядки АКБ на промежуточный вагон
    backward_outputs[SME_CHARGE_VOLTAGE] = aux_conv->getU_110();
    forward_outputs[SME_CHARGE_VOLTAGE] = aux_conv->getU_110();

    // Давление в ПМ для промежуточного вагона
    backward_outputs[SME_PM_PRESSURE] = main_res->getPressure();
    forward_outputs[SME_PM_PRESSURE] = main_res->getPressure();

    // Опрос конфигурации СМЕ
    // Отправляем сигнал назад от данного
    // и не более чем 4 предыдущих вагонов
    backward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(
            SME_MULTIPLIER * (static_cast<int>(forward_inputs[SME_TRAIN_CONFIG]) % SME_LIMIT) + SME_HEAD_BWD);
    // Отправляем сигнал вперёд от данного
    // и не более чем 4 следующих вагонов
    forward_outputs[SME_TRAIN_CONFIG] = static_cast<float>(
            SME_MULTIPLIER * (static_cast<int>(backward_inputs[SME_TRAIN_CONFIG]) % SME_LIMIT) + SME_HEAD_FWD);

    // Сигналы из активной кабины
    if (is_active)
    {
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
        // Отправляем вперёд и назад разные занчения,
        // чтобы остальные вагоны могли определить
        // свою ориентацию относительно активной кабины
        backward_outputs[SME_NO_ACTIVE] = static_cast<float>(SME_ACTIVE_BWD);
        forward_outputs[SME_NO_ACTIVE] = static_cast<float>(SME_ACTIVE_FWD);

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
    // Обработка сигналов неактивной кабиной
    else
    {
        // Определяем ориентацию относительно активной кабины
        if (forward_inputs[SME_NO_ACTIVE] < 0)
        {
            // Если спереди получен сигнал от активной кабины,
            // отправляемый назад, то ориентация совпадает
            is_orient_same = (static_cast<int>(forward_inputs[SME_NO_ACTIVE]) == SME_ACTIVE_BWD);
        }
        if (backward_inputs[SME_NO_ACTIVE] < 0)
        {
            // Если сзади получен сигнал от активной кабины,
            // отправляемый вперёд, то ориентация совпадает
            is_orient_same = (static_cast<int>(backward_inputs[SME_NO_ACTIVE]) == SME_ACTIVE_FWD);
        }
        // Отправляем сигнал дальше
        backward_outputs[SME_NO_ACTIVE] = forward_inputs[SME_NO_ACTIVE];
        forward_outputs[SME_NO_ACTIVE] = backward_inputs[SME_NO_ACTIVE];

        // Пропускаем дальше все сигналы из активной кабины
        for (size_t i = SME_ACTIVE_BEGIN; i < SME_ACTIVE_BEGIN + SME_ACTIVE_SIZE; ++i)
        {
            backward_outputs[i] = forward_inputs[i];
            forward_outputs[i] = backward_inputs[i];
        }
        // Пропускаем дальше сигнал-костыль p0
        backward_outputs[SME_P0] = forward_inputs[SME_P0];
        forward_outputs[SME_P0] = backward_inputs[SME_P0];
    }

    // Пропускаем сигналы состояния следующих вагонов со смещением
    for (size_t i = SME_UNIT_STATE_BEGIN + SME_UNIT_STATE_SIZE; i < forward_outputs.size(); i++)
    {
        forward_outputs[i] = backward_inputs[i - SME_UNIT_STATE_SIZE];
        backward_outputs[i] = forward_inputs[i - SME_UNIT_STATE_SIZE];
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

    // Сигнал состояния дизеля
    backward_outputs[SME_UNIT_DIESEL] = static_cast<float>(mpsu->getOutputData().mfdu_disel_state_level + 1);
    forward_outputs[SME_UNIT_DIESEL] = static_cast<float>(mpsu->getOutputData().mfdu_disel_state_level + 1);

    // Сигнал состояния топливного насоса
    backward_outputs[SME_UNIT_FUEL_PUMP] = static_cast<float>(fuel_pump->isStarted());
    forward_outputs[SME_UNIT_FUEL_PUMP] = static_cast<float>(fuel_pump->isStarted());

    // Сигнал состояния генератора
    backward_outputs[SME_UNIT_GENERATOR] = static_cast<float>(generator->isActive());
    forward_outputs[SME_UNIT_GENERATOR] = static_cast<float>(generator->isActive());

    // Сигнал состояния компрессора
    backward_outputs[SME_UNIT_COMPRESSOR] = static_cast<float>(motor_compr->isPowered());
    forward_outputs[SME_UNIT_COMPRESSOR] = static_cast<float>(motor_compr->isPowered());

    // Сигнал состояния гидропередачи
    backward_outputs[SME_UNIT_GDT_REVERS_STATE] = hydro_trans->getReversState();
    forward_outputs[SME_UNIT_GDT_REVERS_STATE] = hydro_trans->getReversState();
    backward_outputs[SME_UNIT_GDT_BRAKE_LEVEL] = hydro_trans->getBrakeLevel();
    forward_outputs[SME_UNIT_GDT_BRAKE_LEVEL] = hydro_trans->getBrakeLevel();

    // Давление в тормозных цилиндрах
    // Назад отправляем в обратном порядке
    // Вперёд отправляем в правильном порядке
    backward_outputs[SME_UNIT_BC1] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();
    backward_outputs[SME_UNIT_BC2] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
    forward_outputs[SME_UNIT_BC1] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
    forward_outputs[SME_UNIT_BC2] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();

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

}
