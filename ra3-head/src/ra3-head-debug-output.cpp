#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::debugOutput(double t, double dt)
{
    Q_UNUSED(dt)

    DebugMsg = QString("t: %1 PM: %2 3P: %3 P1: %4 P2: %5 ER: %6 TM: %7 TC1: %8 TC2 %9 B: %10 BL: %11")
            .arg(t, 10, 'f', 1)
            .arg(main_res->getPressure(), 4, 'f', 2)
            .arg(aux_res->getPressure(), 4, 'f', 2)
            .arg(brake_mech[FWD_TROLLEY]->getParkingBrakePressure(), 4, 'f', 2)
            .arg(brake_mech[BWD_TROLLEY]->getParkingBrakePressure(), 4, 'f', 2)
            .arg(kru->getEqReservoirPressure(), 4, 'f', 2)
            .arg(pTM, 4, 'f', 2)
            .arg(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure(), 4, 'f', 2)
            .arg(brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure(), 4, 'f', 2)
            .arg(km->getBrakeLevel(), 4, 'f', 2)
            .arg(hydro_trans->getBrakeLevel(), 4, 'f', 2);

//    DebugMsg = QString("t: %1 s | x: %2 m")
//            .arg(t, 6, 'f', 1)
//            .arg(railway_coord, 10, 'f', 1);
//    DebugMsg += blok->getDebugMsg();
}
