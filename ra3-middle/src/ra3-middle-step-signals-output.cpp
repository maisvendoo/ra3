#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    // Колесные пары
    analogSignal[WHEELSET_1] = static_cast<float>(wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[WHEELSET_2] = static_cast<float>(wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[WHEELSET_3] = static_cast<float>(wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[WHEELSET_4] = static_cast<float>(wheel_rotation_angle[3] / 2.0 / Physics::PI);

    // Двери
    analogSignal[DOOR_L_FWD_WARNING_INDICATOR] = door_L->getWarningSignal();
    analogSignal[DOOR_L_FWD_STEP] = door_L->getStepState();
    analogSignal[DOOR_L_FWD_SKID] = door_L->getDoorSkidState();
    analogSignal[DOOR_L_FWD_LEFT] = door_L->getDoorState();
    analogSignal[DOOR_L_FWD_RIGHT] = door_L->getDoorState();
    analogSignal[DOOR_L_BWD_WARNING_INDICATOR] = door_L2->getWarningSignal();
    analogSignal[DOOR_L_BWD_STEP] = door_L2->getStepState();
    analogSignal[DOOR_L_BWD_SKID] = door_L2->getDoorSkidState();
    analogSignal[DOOR_L_BWD_LEFT] = door_L2->getDoorState();
    analogSignal[DOOR_L_BWD_RIGHT] = door_L2->getDoorState();
    analogSignal[DOOR_R_FWD_WARNING_INDICATOR] = door_R->getWarningSignal();
    analogSignal[DOOR_R_FWD_STEP] = door_R->getStepState();
    analogSignal[DOOR_R_FWD_SKID] = door_R->getDoorSkidState();
    analogSignal[DOOR_R_FWD_LEFT] = door_R->getDoorState();
    analogSignal[DOOR_R_FWD_RIGHT] = door_R->getDoorState();
    analogSignal[DOOR_R_BWD_WARNING_INDICATOR] = door_R2->getWarningSignal();
    analogSignal[DOOR_R_BWD_STEP] = door_R2->getStepState();
    analogSignal[DOOR_R_BWD_SKID] = door_R2->getDoorSkidState();
    analogSignal[DOOR_R_BWD_LEFT] = door_R2->getDoorState();
    analogSignal[DOOR_R_BWD_RIGHT] = door_R2->getDoorState();

    // Предупреждение о закрытии дверей
    analogSignal[SOUND_DOOR_WARN_L] = door_L->getSoundSignal();
    analogSignal[SOUND_DOOR_WARN_L2] = door_L2->getSoundSignal();
    analogSignal[SOUND_DOOR_WARN_R] = door_R->getSoundSignal();
    analogSignal[SOUND_DOOR_WARN_R2] = door_R2->getSoundSignal();
}
