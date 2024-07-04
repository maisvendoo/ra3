#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepOtherEquipment(double t, double dt)
{
    horn->setFLpressure(main_reservoir->getPressure());
    horn->setControl(keys);
    horn->step(t, dt);

    // Система подачи песка под оси передней (моторной) тележки
    sand_system->setFLpressure(main_reservoir->getPressure());
    sand_system->setControl(keys);
    sand_system->step(t, dt);
    // Пересчёт трения колесо-рельс
    psi[0] = sand_system->getWheelRailFrictionCoeff(psi[0]);
    psi[1] = sand_system->getWheelRailFrictionCoeff(psi[1]);

    hydro_pump->setDiselOmega(disel->getOmega());
    hydro_pump->step(t, dt);   
}
