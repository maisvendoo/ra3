#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::blokSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    analogSignal[BLOK_REVERS] = static_cast<float>(hydro_trans->getReversState());
    analogSignal[BLOK_TM_PRESS] = static_cast<float>(brakepipe->getPressure());
    analogSignal[BLOK_TC_PRESS] = static_cast<float>(brake_mech[TROLLEY_BWD]->getBCpressure());
    analogSignal[BLOK_VELOCITY] = static_cast<float>(blok->getVelocityKmh());
    analogSignal[BLOK_RAILWAY_COORD] = static_cast<float>(blok->getRailCoord());
    analogSignal[BLOK_ACCELERATION] = static_cast<float>(blok->getAcceleration());
    analogSignal[BLOK_VELOCITY_CURRENT_LIMIT] = blok->getCurrentSpeedLimit();
    analogSignal[BLOK_VELOCITY_NEXT_LIMIT] = blok->getNextSpeedLimit();

    analogSignal[BLOK_DISPLAY_ON] = static_cast<float>(blok->isDisplayON());

    analogSignal[BLOK_VIGILANCE] = static_cast<float>(blok->isCheckVigilanse());

    analogSignal[BLOK_STATION_INDEX] = blok->getStationIndex();
}
