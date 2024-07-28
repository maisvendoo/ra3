#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSoundSignalsOutput(double t, double dt)
{
    (void) t;
    (void) dt;
    // Свисток и тифон
    analogSignal[SOUND_SVISTOK] = horn->getSoundSignal(TrainHorn::SVISTOK_SOUND);
    analogSignal[SOUND_TIFON] = horn->getSoundSignal(TrainHorn::TIFON_SOUND);

    // Реверсор и контроллер
    analogSignal[SOUND_REVERSOR] = km->getSoundSignal(TracController::REVERS_CHANGE_POS_SOUND);
    analogSignal[SOUND_CONTROLLER] = km->getSoundSignal(TracController::MAIN_CHANGE_MODE_SOUND);
    analogSignal[SOUND_KM_EMERGENCY] = km->getSoundSignal(TracController::MAIN_EMERGENCY_FLOW_SOUND);
    // Клапан аварийного экстренного торможения
    analogSignal[SOUND_EMERGENCY_VALVE] = emerg_brake_valve->getSoundSignal();

    // БЛОК
    analogSignal[SOUND_BLOK_BUTTON] = blok->getSoundSignal(BLOK::BUTTON_PRESS_SOUND);
    analogSignal[SOUND_BLOK_SPEED_LIMIT] = blok->getSoundSignal(BLOK::VELOCITY_NEAR_LIMIT_SOUND);

    // Стояночный пружинный тормоз
    analogSignal[SOUND_PARKING_BRAKE_SWITCHER] = tumbler[SWITCH_PARKING_BRAKE].getSoundSignal(Trigger::CHANGE_SOUND);
    analogSignal[SOUND_PARKING_BRAKE_FLOW] = brake_module->getSoundSignal();

    // Кран резервного управления
    analogSignal[SOUND_BRAKE_CRANE_BP_FILL_FLOW] = kru->getSoundSignal(BrakeCrane::BP_FILL_FLOW_SOUND);
    analogSignal[SOUND_BRAKE_CRANE_BP_DRAIN_FLOW] = kru->getSoundSignal(BrakeCrane::BP_DRAIN_FLOW_SOUND);

    // ЭПК
    analogSignal[SOUND_EPK_WHISTLE] = epk->getSoundSignal();

    // Реле
    analogSignal[SOUND_RELAY_POWER] = KM_power->getSoundSignal(Relay::CHANGE_SOUND);
    analogSignal[SOUND_RELAY_ACTIVE_CAB] = active_cab_relay->getSoundSignal(Relay::CHANGE_SOUND);

    // Двигательная установка
    analogSignal[SOUND_FUEL_PUMP] = fuel_pump->getSoundSignal();
    analogSignal[SOUND_DISEL_STARTER] = starter->getSoundSignal();
    analogSignal[SOUND_DISEL_NOM_FREQ] = disel->getSoundSignal(Disel::NOMINAL_FREQUENCY_SOUND);
    analogSignal[SOUND_DISEL_HIGH_FREQ] = disel->getSoundSignal(Disel::HIGH_FREQUENCY_SOUND);
    analogSignal[SOUND_DISEL_STOP] = disel->getSoundSignal(Disel::STOP_SOUND);

    // Песочница
    analogSignal[SOUND_SAND_DELIVERY] = sand_system->getSoundSignal();
}
