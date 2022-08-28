#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::debugOutput(double t, double dt)
{
    Q_UNUSED(dt)

    DebugMsg = QString("t %1|ГР %2 3P %3|P1 %4 P2 %5| TM %6 TC1 %7 TC2 %8|T %9 TL %10|B %11 BL %12|M %13|  ")
            .arg(t, 10, 'f', 1)
            .arg(main_res->getPressure(), 4, 'f', 2)
            .arg(aux_res->getPressure(), 4, 'f', 2)
            .arg(brake_mech[FWD_TROLLEY]->getParkingBrakePressure(), 4, 'f', 2)
            .arg(brake_mech[BWD_TROLLEY]->getParkingBrakePressure(), 4, 'f', 2)
            .arg(pTM, 4, 'f', 2)
            .arg(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure(), 4, 'f', 2)
            .arg(brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure(), 4, 'f', 2)
            .arg(km->getTractionLevel(), 4, 'f', 2)
            .arg(hydro_trans->getTractionLevel(), 4, 'f', 2)
            .arg(km->getBrakeLevel(), 4, 'f', 2)
            .arg(hydro_trans->getBrakeLevel(), 4, 'f', 2)
            .arg(hydro_trans->getOutputTorque(), 8, 'f', 2);
}
