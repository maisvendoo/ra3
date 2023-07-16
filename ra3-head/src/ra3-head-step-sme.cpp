#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSME(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Опрос конфигурации СМЕ
    // Отправляем сигнал вперёд от данного
    // и не более чем 4 следующих вагонов
    sme_fwd->setSignal(SME_TRAIN_CONFIG,
            SME_MULTIPLIER * (static_cast<int>(sme_bwd->getSignal(SME_TRAIN_CONFIG)) % SME_LIMIT) + SME_HEAD_FWD);
    // Отправляем сигнал назад от данного
    // и не более чем 4 предыдущих вагонов
    sme_bwd->setSignal(SME_TRAIN_CONFIG,
           SME_MULTIPLIER * (static_cast<int>(sme_fwd->getSignal(SME_TRAIN_CONFIG)) % SME_LIMIT) + SME_HEAD_BWD);

    // Напряжение зарядки АКБ на промежуточный вагон
    sme_fwd->setSignal(SME_CHARGE_VOLTAGE, aux_conv->getU_110());
    sme_bwd->setSignal(SME_CHARGE_VOLTAGE, aux_conv->getU_110());

    // Сигналы из активной кабины
    if (is_active)
    {
        // Сигнал запрета включать другие кабины
        sme_fwd->setSignal(SME_NO_ACTIVE, 1.0);
        sme_bwd->setSignal(SME_NO_ACTIVE, 1.0);

        // Сигнал включения контактора "Бортсеть" на ведомые секции
        sme_fwd->setSignal(SME_POWER_ON, static_cast<double>(KM_power->getContactState(2)));
        sme_bwd->setSignal(SME_POWER_ON, static_cast<double>(KM_power->getContactState(2)));

        // Сигналы запуска и остановки дизеля на ведомые секции
        double tmp = static_cast<double>(mpsu->getOutputData().start_press_count == 1)
                   - static_cast<double>(mpsu->getOutputData().stop_diesel);
        sme_fwd->setSignal(SME_DIESEL_START_STOP, tmp);
        sme_bwd->setSignal(SME_DIESEL_START_STOP, tmp);

        // Сигнал работы ЭПК на ведомые секции
        sme_fwd->setSignal(SME_IS_AUTOSTOP_ON, static_cast<double>(epk->getStateKey()));
        sme_bwd->setSignal(SME_IS_AUTOSTOP_ON, static_cast<double>(epk->getStateKey()));

        // Сигнал позиции реверсора на ведомые секции
        // Вперёд отправляем правильно, назад наоборот
        sme_fwd->setSignal(SME_REVERS_HANDLE, static_cast<double>(km->getReversHandlePos()));
        sme_bwd->setSignal(SME_REVERS_HANDLE, static_cast<double>(-km->getReversHandlePos()));

        // Сигналы блок-контактов КМ на ведомые секции
        tmp = static_cast<double>(km->isTraction())
            - static_cast<double>(km->isBrake());
        sme_fwd->setSignal(SME_KM_STATE, tmp);
        sme_bwd->setSignal(SME_KM_STATE, tmp);

        // Уровень тяги на ведомые секции
        tmp = max(km->getTractionLevel(), mpsu->getOutputData().trac_level);
        sme_fwd->setSignal(SME_TRACTION_LEVEL, tmp);
        sme_bwd->setSignal(SME_TRACTION_LEVEL, tmp);

        // Уровень торможения на ведомые секции
        tmp = max(km->getBrakeLevel(), mpsu->getOutputData().brake_level);
        sme_fwd->setSignal(SME_BRAKE_LEVEL, tmp);
        sme_bwd->setSignal(SME_BRAKE_LEVEL, tmp);
/*
        // Заданный уровень торможения ЭПТ на ведомые секции
        backward_outputs[SME_REF_BRAKE_LEVEL_EPB] = static_cast<float>(mpsu->getOutputData().brake_ref_level_EPB);
        forward_outputs[SME_REF_BRAKE_LEVEL_EPB] = static_cast<float>(mpsu->getOutputData().brake_ref_level_EPB);
*/
        // Сигнал управления стояночным тормозом на ведомые секции
        sme_fwd->setSignal(SME_PARKING_BRAKE_ON, static_cast<double>(tumbler[SWITCH_PARKING_BRAKE].getState()));
        sme_bwd->setSignal(SME_PARKING_BRAKE_ON, static_cast<double>(tumbler[SWITCH_PARKING_BRAKE].getState()));

        // Сигнал экстренного торможения на ведомые секции
        bool is_emergency = (  emerg_brake_valve->isEmergencyBrake()
                            || km->isEmergencyBrake() );
        sme_fwd->setSignal(SME_IS_EMERGENCY_BRAKE, static_cast<double>(is_emergency));
        sme_bwd->setSignal(SME_IS_EMERGENCY_BRAKE, static_cast<double>(is_emergency));
    }
    // Обработка сигналов неактивной кабиной
    else
    {
        // Пропускаем дальше все сигналы из активной кабины
        for (size_t i = SME_ACTIVE_BEGIN; i < SME_ACTIVE_BEGIN + SME_ACTIVE_SIZE; ++i)
        {
            sme_fwd->setSignal(i, sme_bwd->getSignal(i));
            sme_bwd->setSignal(i, sme_fwd->getSignal(i));
        }
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

    // Сигнал состояния дизеля
    sme_fwd->setSignal(SME_UNIT_DIESEL, static_cast<double>(mpsu->getOutputData().mfdu_disel_state_level + 1));
    sme_bwd->setSignal(SME_UNIT_DIESEL, static_cast<double>(mpsu->getOutputData().mfdu_disel_state_level + 1));

    // Сигнал состояния топливного насоса
    sme_fwd->setSignal(SME_UNIT_FUEL_PUMP, static_cast<double>(fuel_pump->isStarted()));
    sme_bwd->setSignal(SME_UNIT_FUEL_PUMP, static_cast<double>(fuel_pump->isStarted()));

    // Сигнал состояния генератора
    sme_fwd->setSignal(SME_UNIT_GENERATOR, static_cast<double>(generator->isActive()));
    sme_bwd->setSignal(SME_UNIT_GENERATOR, static_cast<double>(generator->isActive()));

    // Сигнал состояния компрессора
    sme_fwd->setSignal(SME_UNIT_COMPRESSOR, static_cast<double>(motor_compressor->isPowered()));
    sme_bwd->setSignal(SME_UNIT_COMPRESSOR, static_cast<double>(motor_compressor->isPowered()));

    // Сигнал состояния гидропередачи
    sme_fwd->setSignal(SME_UNIT_GDT_REVERS_STATE, static_cast<double>(hydro_trans->getReversState()));
    sme_bwd->setSignal(SME_UNIT_GDT_REVERS_STATE, static_cast<double>(hydro_trans->getReversState()));
    sme_fwd->setSignal(SME_UNIT_GDT_BRAKE_LEVEL, hydro_trans->getBrakeLevel());
    sme_bwd->setSignal(SME_UNIT_GDT_BRAKE_LEVEL, hydro_trans->getBrakeLevel());

    // Давление в тормозных цилиндрах
    // Вперёд отправляем в правильном порядке
    // Назад отправляем в обратном порядке
    sme_fwd->setSignal(SME_UNIT_BC1, brake_mech[TROLLEY_FWD]->getBCpressure());
    sme_fwd->setSignal(SME_UNIT_BC2, brake_mech[TROLLEY_BWD]->getBCpressure());
    sme_bwd->setSignal(SME_UNIT_BC1, brake_mech[TROLLEY_BWD]->getBCpressure());
    sme_bwd->setSignal(SME_UNIT_BC2, brake_mech[TROLLEY_FWD]->getBCpressure());

    // Состояние дверей
    // Вперёд отправляем правильно
    // Назад отправляем зеркально
    sme_fwd->setSignal(SME_UNIT_DOOR_R, static_cast<double>(door_R_state));
    sme_fwd->setSignal(SME_UNIT_DOOR_L, static_cast<double>(door_L_state));
    sme_bwd->setSignal(SME_UNIT_DOOR_R, static_cast<double>(door_L_state));
    sme_bwd->setSignal(SME_UNIT_DOOR_L, static_cast<double>(door_R_state));

    // Состояние стояночного пружинного тормоза в ведущую секцию
    sme_fwd->setSignal(SME_UNIT_SPT_STATE, static_cast<double>(brake_module->isParkingBraked()));
    sme_bwd->setSignal(SME_UNIT_SPT_STATE, static_cast<double>(brake_module->isParkingBraked()));
}
