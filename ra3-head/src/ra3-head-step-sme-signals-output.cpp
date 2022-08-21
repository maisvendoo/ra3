#include    "ra3-head.h"

#include <ra3-head.h>

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


    // Сигнал включения контактора "Бортсеть" на ведомые секции
    backward_outputs[SME_BWD_POWER_ON] = static_cast<float>(KM_power->getContactState(2));

    // Сигнал позиции реверсора на ведомые секции
    backward_outputs[SME_REVERS_HANDLE] = km->getReversHandlePos();

    // Сигналы блок-контактов КМ на ведомые секции
    backward_outputs[SME_IS_KM_ZERO] = static_cast<float>(km->isZero());
    backward_outputs[SME_IS_KM_TRACTION] = static_cast<float>(km->isTraction());
    backward_outputs[SME_IS_KM_BRAKE] = static_cast<float>(km->isBrake());

    // Уровень тяги от КМ на ведомые секции
    backward_outputs[SME_KM_TRACTION_LEVEL] = km->getTractionLevel();

    // Частота оборотов дизеля на ведомые секции
    backward_outputs[SME_DISEL_FREQ] = static_cast<float>(mpsu->getOutputData().n_ref);

    // Уровень торможения от КМ на ведомые секции
    backward_outputs[SME_KM_BRAKE_LEVEL] = km->getBrakeLevel();

    // Заданный уровень торможения ЭПТ на ведомые секции
    backward_outputs[SME_REF_BRAKE_LEVEL] = km->getBrakeLevel();
    backward_outputs[SME_REF_BRAKE_LEVEL_EPB] = static_cast<float>(mpsu->getOutputData().brake_ref_level_EPB);

    // Сигнал отпуска тормозов (КЭБ) на ведомые секции и промежуточные вагоны
    backward_outputs[SME_BRAKE_RELEASE] = static_cast<float>(mpsu->getOutputData().release_PB1);

    // Сигнал управления стояночным тормозом на ведомые секции
    backward_outputs[SME_PARKING_BRAKE_ON] = static_cast<float>(tumbler[SWITCH_PARKING_BRAKE].getState());

    // Сигнал экстренного торможения на ведомые секции
    backward_outputs[SME_IS_EMERGENCY_BRAKE] = static_cast<float>(
                emerg_brake_valve->isEmergencyBrake() ||
                km->isEmergencyBrake());

    // Сигнал наличия питания на удерживающей катушке ЭПК
    backward_outputs[SME_EPK_STATE] = static_cast<float>(blok->getEPKstate());

    // Сигнал разрешения сделать кабину активной
    backward_outputs[SME_NO_ACTIVE] = 1.0f;


    // Сигнал включения топливного насоса на ведомом дизеле
    backward_outputs[SME_BWD_FUEL_PUMP] = static_cast<float>(mpsu->getOutputData().is_fuel_pump2_ON);

    // Сигнал открытия топливного клапана на ведомом дизеле
    backward_outputs[SME_BWD_FUEL_VALVE_OPEN] = static_cast<float>(mpsu->getOutputData().is_fuel_valve2_open);

    // Сигнал включения стартера на ведомом дизеле
    backward_outputs[SME_BWD_STARTER_ON] = static_cast<float>(mpsu->getOutputData().is_starter2_ON);

    // Сигнал запуска дизеля для включения ПСН в ведомой секции
    backward_outputs[SME_BWD_DISEL_STARTED] = static_cast<float>(mpsu->getOutputData().is_disel2_started);


    // Передаем давление масла в ведущую секцию
    forward_outputs[SME_BWD_OIL_PRESS] = static_cast<float>(disel->getOilPressure());

    // Передаем давление топлива в ведущую секцию
    forward_outputs[SME_BWD_FUEL_PRESS] = static_cast<float>(fuel_pump->getFuelPressure());

    // Передаем состояние топливного насоса в ведущую секцию
    forward_outputs[SME_BWD_FUEL_PUMP_ON] = static_cast<float>(fuel_pump->isStarted());

    // Передаем обороты дизеля в ведущую секцию
    forward_outputs[SME_BWD_OMEGA] = static_cast<float>(disel->getShaftFreq());

    // Передаем состояние генератора в ведущую секцию
    forward_outputs[SME_BWD_GENERATOR] = static_cast<float>(generator->isActive());

    // Передаем состояние компрессора в ведущую секцию
    forward_outputs[SME_BWD_COMPRESSOR] = static_cast<float>(motor_compr->isPowered());

    // Передаем состояние гидропередачи в ведущую секцию
    forward_outputs[SME_REVERS_STATE] = hydro_trans->getReversState();
    forward_outputs[SME_BWD_BRAKE_LEVEL] = hydro_trans->getBrakeLevel();

    // Передаем давление в тормозных цилиндрах в ведущую секцию
    forward_outputs[SME_BWD_BC1] = brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure();
    forward_outputs[SME_BWD_BC2] = brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure();

    // Передаем состояние стояночного тормоза в ведущую секцию
    forward_outputs[SME_PARKING_BRAKE_STATE] = static_cast<float>(brake_module->isParkingBraked());

    // Сигнал наличия связи с ведущей секцией
    forward_outputs[SME_BWD_CAN] = 1.0f;

}
