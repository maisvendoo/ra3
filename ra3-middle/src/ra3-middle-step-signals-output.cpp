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

    // TODO // Двери
    analogSignal[DOOR_L_FWD_WARNING_INDICATOR] = 0.0f;
    analogSignal[DOOR_L_FWD_STEP] = 0.0f;
    analogSignal[DOOR_L_FWD_SKID] = 0.0f;
    analogSignal[DOOR_L_FWD_LEFT] = 0.0f;
    analogSignal[DOOR_L_FWD_RIGHT] = 0.0f;
    analogSignal[DOOR_L_BWD_WARNING_INDICATOR] = 0.0f;
    analogSignal[DOOR_L_BWD_STEP] = 0.0f;
    analogSignal[DOOR_L_BWD_SKID] = 0.0f;
    analogSignal[DOOR_L_BWD_LEFT] = 0.0f;
    analogSignal[DOOR_L_BWD_RIGHT] = 0.0f;
    analogSignal[DOOR_R_FWD_WARNING_INDICATOR] = 0.0f;
    analogSignal[DOOR_R_FWD_STEP] = 0.0f;
    analogSignal[DOOR_R_FWD_SKID] = 0.0f;
    analogSignal[DOOR_R_FWD_LEFT] = 0.0f;
    analogSignal[DOOR_R_FWD_RIGHT] = 0.0f;
    analogSignal[DOOR_R_BWD_WARNING_INDICATOR] = 0.0f;
    analogSignal[DOOR_R_BWD_STEP] = 0.0f;
    analogSignal[DOOR_R_BWD_SKID] = 0.0f;
    analogSignal[DOOR_R_BWD_LEFT] = 0.0f;
    analogSignal[DOOR_R_BWD_RIGHT] = 0.0f;
}
