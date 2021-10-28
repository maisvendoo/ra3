#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::blokSignalsOutput(double t, double dt)
{
    analogSignal[BLOK_REVERS] = static_cast<float>(hydro_trans->getReversState());
    analogSignal[BLOK_TM_PRESS] = static_cast<float>(pTM);
    analogSignal[BLOK_TC_PRESS] = static_cast<float>(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure());
    analogSignal[BLOK_VELOCITY] = static_cast<float>(blok->getVelocityKmh());
    analogSignal[BLOK_VELOCITY_CURRENT_LIMIT] = blok->getCurrentSpeedLimit();
    analogSignal[BLOK_VELOCITY_NEXT_LIMIT] = blok->getNextSpeedLimit();

    analogSignal[BLOK_DISPLAY_ON] = static_cast<float>(blok->isDisplayON());
}
