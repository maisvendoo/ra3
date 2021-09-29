#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepDisel(double t, double dt)
{
    disel->step(t, dt);

    // Передаем давление масла в ведущую секцию
    forward_outputs[SME_BWD_OIL_PRESS] = static_cast<float>(disel->getOilPressure());

    starter->step(t, dt);
}
