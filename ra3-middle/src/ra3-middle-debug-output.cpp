#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::debugOutput(double t, double dt)
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

    DebugMsg += QString("\n");
    DebugMsg += QString("%1%2%3---couplings---%4%5%6")
                    .arg(coupling_fwd->isLinked() ? "=" : " ")
                    .arg(coupling_fwd->isCoupled() ? "=" : " ")
                    .arg((coupling_fwd->getOutputSignal(COUPL_OUTPUT_REF_STATE) > -0.5) ? "=" : ">")
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
}
