#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::debugOutput(double t, double dt)
{
    Q_UNUSED(dt)

    DebugMsg = QString("t: %1 Ucc: %2 D: %3 FUEL PRESS.: %4 OIL PRESS.: %5 n1: %6 n2: %7 Is: %8 U_gen: %9")
            .arg(t, 10, 'f', 1)
            .arg(Ucc, 5, 'f', 1)
            .arg(mpsu->getOutputData().current_started_disel + 1, 1)
            .arg(fuel_pump->getFuelPressure(), 4, 'f', 2)
            .arg(disel->getOilPressure(), 4, 'f', 2)
            .arg(disel->getShaftFreq(), 6, 'f', 1)
            .arg(backward_inputs[SME_BWD_OMEGA], 6, 'f', 1)
            .arg(starter->getCurrent(), 6, 'f', 1)
            .arg(generator->getVoltage() * sqrt(3.0), 5, 'f', 1);
}
