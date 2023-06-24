#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::debugOutput(double t, double dt)
{
    Q_UNUSED(dt);

    DebugMsg = QString("t%1 s|")
            .arg(t, 7, 'f', 1);
    DebugMsg += QString("x%1 km|V%2 km/h|")
            .arg(railway_coord / 1000.0, 8, 'f', 3)
            .arg(velocity * Physics::kmh, 6, 'f', 1);
    DebugMsg += QString("pBP%1|pBC%2|pBC%3|pSR%4|")
            .arg(10.0 * brakepipe->getPressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_FWD]->getBCpressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_BWD]->getBCpressure(), 6, 'f', 2)
            .arg(10.0 * supply_reservoir->getPressure(), 6, 'f', 2);
    DebugMsg += QString("pFL%1|pPB%2|pPB%3|")
            .arg(10.0 * main_reservoir->getPressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_FWD]->getPBpressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_BWD]->getPBpressure(), 6, 'f', 2);
    DebugMsg += QString("          ");
}
