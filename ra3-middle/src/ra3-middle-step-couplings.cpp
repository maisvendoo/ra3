#include    "ra3-middle.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void RA3Middle::preStepCouplings(double t)
{
    (void) t;

    // Координата и скорость переднего сцепного устройства (по оси сцепления)
    coupling_fwd->setCoord(train_coord + dir * orient * length / 2.0);
    coupling_fwd->setVelocity(dir * orient * velocity);

    // Координата и скорость заднего сцепного устройства (по оси сцепления)
    coupling_bwd->setCoord(train_coord - dir * orient * length / 2.0);
    coupling_bwd->setVelocity(dir * orient * velocity);
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void RA3Middle::stepCouplings(double t, double dt)
{
    // Управление передним сцепным устройством отключено
/*    oper_rod_fwd->setCouplingForce(coupling_fwd->getCurrentForce());
    oper_rod_fwd->setControl(keys);
    oper_rod_fwd->step(t, dt);
    coupling_fwd->setCouplingOperatingState(oper_rod_fwd->getOperatingState());*/
    coupling_fwd->couple();
    coupling_fwd->step(t, dt);
    // Добавляем усилие от переднего сцепного устройства на данном шаге
    F_fwd += coupling_fwd->getCurrentForce();

    // Управление задним сцепным устройством отключено
/*    oper_rod_bwd->setCouplingForce(coupling_bwd->getCurrentForce());
    oper_rod_bwd->setControl(keys);
    oper_rod_bwd->step(t, dt);
    coupling_bwd->setCouplingOperatingState(oper_rod_bwd->getOperatingState());*/
    coupling_bwd->couple();
    coupling_bwd->step(t, dt);
    // Добавляем усилие от заднего сцепного устройства на данном шаге
    F_bwd += coupling_bwd->getCurrentForce();
}
