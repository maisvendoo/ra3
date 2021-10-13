#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::controlLampsSignalsOutput(double t, double dt)
{
    analogSignal[ACTIVE_COCKPIT] = 1.0f;
    analogSignal[ALARM] = 1.0f;
    analogSignal[PARKING_BRAKE] = 1.0f;
}
