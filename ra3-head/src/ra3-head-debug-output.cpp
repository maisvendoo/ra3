#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::debugOutput(double t, double dt)
{
    Q_UNUSED(dt)

    DebugMsg = QString("t: %1 Ucc: %2 БОРТСЕТЬ ВКЛ.: %3 БОРТСЕТЬ ОТКЛ.: %4 ДИЗЕЛЬ: %5")
            .arg(t, 10, 'f', 1)
            .arg(Ucc, 5, 'f', 1)
            .arg(tumbler[BUTTON_PWR_ON].getState(), 1)
            .arg(tumbler[BUTTON_PWR_OFF].getState(), 1)
            .arg(mpsu->getOutputData().current_started_disel + 1, 1);
}
