#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::blokSignalsOutput(double t, double dt)
{
    analogSignal[BLOK_REVERS] = static_cast<float>(mpsu->getOutputData().getReversorDir());
    analogSignal[BLOK_TM_PRESS] = static_cast<float>(pTM);
    analogSignal[BLOK_TC_PRESS] = static_cast<float>(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure());
    analogSignal[BLOK_VELOCITY] = static_cast<float>(velocity * Physics::kmh);
}
