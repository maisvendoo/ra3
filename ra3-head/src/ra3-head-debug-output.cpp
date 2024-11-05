#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::debugOutput(double t, double dt)
{
    (void) t;
    (void) dt;

    DebugMsg = "";
    DebugMsg += QString("x%1 km|V%2 km/h|")
                    .arg(profile_point_data.railway_coord / 1000.0, 10, 'f', 3)
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
    DebugMsg += QString("pER%1|KRU:%2|")
                    .arg(10.0 * kru->getERpressure(), 6, 'f', 2)
                    .arg(kru->getPositionName(), 3);

    QString pos = QString("Pos%1%")
                    .arg(100.0 * (km->getTractionLevel() - km->getBrakeLevel()), 4, 'f', 0);
    if (mpsu->getOutputData().is_speed_hold_ON)
        pos = QString("V%1/%2")
                    .arg(qAbs(wheel_omega[0] * rk[0] * Physics::kmh), 3, 'f', 0)
                    .arg(mpsu->getOutputData().v_ref_kmh, 3);
    DebugMsg += QString("Rev%1|%2|T%3 N*m(%4%)|")
                    .arg(km->getReversHandlePos(), 2, 'f', 0)
                    .arg(pos)
                    .arg(hydro_trans->getOutputTorque(), 6, 'f', 0)
                    .arg(100.0 * (  hydro_trans->getTractionLevel()
                                  - hydro_trans->getBrakeLevel()  ) , 4, 'f', 0);

    DebugMsg += QString("\n");
    DebugMsg += QString("%1%2%3---couplings---%5%6%7")
                    .arg(coupling_fwd->isLinked() ? "=" : " ")
                    .arg(coupling_fwd->isCoupled() ? "=" : " ")
                    .arg((coupling_fwd->getOutputSignal(COUPL_OUTPUT_REF_STATE) > -0.5) ? "=" : ">")
                    .arg((oper_rod_fwd->getOperatingState() > -0.5) ? "|" : "/")
                    .arg((coupling_bwd->getOutputSignal(COUPL_OUTPUT_REF_STATE) > -0.5) ? "=" : "<")
                    .arg(coupling_bwd->isCoupled() ? "=" : " ")
                    .arg(coupling_bwd->isLinked() ? "=" : " ");
    DebugMsg += QString("  |  ");
    DebugMsg += QString("%1%2/=%3==BP==%4=\\%5%6")
                    .arg(hose_bp_fwd->isLinked() ? "\\" : " ")
                    .arg(hose_bp_fwd->isConnected() ? "_" : " ")
                    .arg(anglecock_bp_fwd->isOpened() ? "/" : "|")
                    .arg(anglecock_bp_bwd->isOpened() ? "\\" : "|")
                    .arg(hose_bp_bwd->isConnected() ? "_" : " ")
                    .arg(hose_bp_bwd->isLinked() ? "/" : " ");
    DebugMsg += QString("  |  ");
    DebugMsg += QString("%1%2/=%3==FL==%4=\\%5%6")
                    .arg(hose_fl_fwd->isLinked() ? "\\" : " ")
                    .arg(hose_fl_fwd->isConnected() ? "_" : " ")
                    .arg(anglecock_fl_fwd->isOpened() ? "/" : "|")
                    .arg(anglecock_fl_bwd->isOpened() ? "\\" : "|")
                    .arg(hose_fl_bwd->isConnected() ? "_" : " ")
                    .arg(hose_fl_bwd->isLinked() ? "/" : " ");

    DebugMsg += QString("\n");
    DebugMsg += QString("FWD Speed limit %1 km/h | Next %2 km/h (%3 m)")
                    .arg(speedmap_fwd->getCurrentLimit(), 3, 'f', 0)
                    .arg(speedmap_fwd->getNextLimit(), 3, 'f', 0)
                    .arg(speedmap_fwd->getNextLimitDistance(), 6, 'f', 1);

    DebugMsg += QString("   |   ");
    DebugMsg += QString("FWD Signal code %1 (%2 Hz) | Next %3 (%4 m)")
                    .arg(coil_ALSN_fwd->getCode(), 1)
                    .arg(coil_ALSN_fwd->getFrequency(), 3, 'f', 0)
                    .arg(coil_ALSN_fwd->getNextSignalLiter())
                    .arg(coil_ALSN_fwd->getNextSignalDistance(), 6, 'f', 1);
}
