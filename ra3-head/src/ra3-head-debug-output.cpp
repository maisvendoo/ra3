#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::debugOutput(double t, double dt)
{
    Q_UNUSED(dt)

    DebugMsg = QString("t%1 s|")
            .arg(t, 7, 'f', 1);/*
    DebugMsg += QString("x%1 km|V%2 km/h|")
            .arg(railway_coord / 1000.0, 8, 'f', 3)
            .arg(velocity * Physics::kmh, 6, 'f', 1);
    DebugMsg += QString("pBP%1|pBC%2|pBC%3|pSR%4|")
            .arg(10.0 * brakepipe->getPressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_FWD]->getBCpressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_BWD]->getBCpressure(), 6, 'f', 2)
            .arg(10.0 * supply_reservoir->getPressure(), 6, 'f', 2);
    DebugMsg += QString("pFL%1|pPB%2|pPB%3|pER%2|KRU:%3|")
            .arg(10.0 * main_reservoir->getPressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_FWD]->getPBpressure(), 6, 'f', 2)
            .arg(10.0 * brake_mech[TROLLEY_BWD]->getPBpressure(), 6, 'f', 2);
    DebugMsg += QString("pER%1|KRU:%2|")
            .arg(10.0 * kru->getERpressure(), 6, 'f', 2)
            .arg(kru->getPositionName(), 3);
    DebugMsg += QString("Rev%1|Pos%2%|T%3 N*m(%4%)|")
            .arg(km->getReversHandlePos(), 2, 'f', 0)
            .arg(100.0 * (km->getTractionLevel() - km->getBrakeLevel()), 4, 'f', 0)
            .arg(hydro_trans->getOutputTorque(), 6, 'f', 0)
            .arg(100.0 * (  hydro_trans->getTractionLevel()
                          - hydro_trans->getBrakeLevel()  ) , 4, 'f', 0);
    DebugMsg += QString("ALSN:%1|D:%2|")
            .arg(alsn_info.code_alsn, 2)
            .arg(alsn_info.signal_dist, 8, 'f', 1);*/
    DebugMsg += kru->getDebugMsg();
}
