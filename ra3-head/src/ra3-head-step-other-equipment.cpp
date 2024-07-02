#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepOtherEquipment(double t, double dt)
{
    horn->setFLpressure(main_reservoir->getPressure());
    horn->setControl(keys);
    horn->step(t, dt);

    hydro_pump->setDiselOmega(disel->getOmega());
    hydro_pump->step(t, dt);   
}
