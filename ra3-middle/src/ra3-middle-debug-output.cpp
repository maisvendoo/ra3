#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::debugOutput(double t, double dt)
{
    DebugMsg = QString("t: %1 PM: %2 3P: %3 P1: %4 P2: %5 TM: %6 TC1: %7 TC2 %8")
            .arg(t, 10, 'f', 1)
            .arg(main_res->getPressure(), 4, 'f', 2)
            .arg(aux_res->getPressure(), 4, 'f', 2)
            .arg(brake_mech[FWD_TROLLEY]->getParkingBrakePressure(), 4, 'f', 2)
            .arg(brake_mech[BWD_TROLLEY]->getParkingBrakePressure(), 4, 'f', 2)
            .arg(pTM, 4, 'f', 2)
            .arg(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure(), 4, 'f', 2)
            .arg(brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure(), 4, 'f', 2);
}
