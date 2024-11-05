#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepPneumoSupply(double t, double dt)
{
    // Расчитываем переток из главного резервуара в запасный через обратный клапан
    double K_ps = 0.05;
    double Q_pm_sr = K_ps * pf(  main_reservoir->getPressure()
                               - supply_reservoir->getPressure());

    // Задаём главному резервуару отток в запасный, потоки из рукавов
    double FL_flow = 0.0;
    FL_flow += -Q_pm_sr;

    anglecock_fl_fwd->setHoseFlow(hose_fl_fwd->getFlow());
    FL_flow += anglecock_fl_fwd->getFlowToPipe();

    anglecock_fl_bwd->setHoseFlow(hose_fl_bwd->getFlow());
    FL_flow += anglecock_fl_bwd->getFlowToPipe();

    main_reservoir->setFlow(FL_flow);
    main_reservoir->step(t, dt);

    // Задаём запасному резервуару приток из главного,
    // расход на питание блока тормозного оборудования
    supply_reservoir->setFlow(brake_module->getSRflow() + Q_pm_sr);
    supply_reservoir->step(t, dt);

    // Концевые краны питательной магистрали
    anglecock_fl_fwd->setPipePressure(main_reservoir->getPressure());
    //anglecock_fl_fwd->setControl(keys);
    anglecock_fl_fwd->step(t, dt);
    anglecock_fl_bwd->setPipePressure(main_reservoir->getPressure());
    //anglecock_fl_bwd->setControl(keys);
    anglecock_fl_bwd->step(t, dt);

    // Рукава питательной магистрали
    hose_fl_fwd->setPressure(anglecock_fl_fwd->getPressureToHose());
    hose_fl_fwd->setFlowCoeff(anglecock_fl_fwd->getFlowCoeff());
    hose_fl_fwd->setCoord(train_coord + dir * orient * (length / 2.0 - anglecock_fl_fwd->getShiftCoord()));
    hose_fl_fwd->setShiftSide(anglecock_fl_fwd->getShiftSide());
    //hose_fl_fwd->setControl(keys);
    hose_fl_fwd->step(t, dt);
    hose_fl_bwd->setPressure(anglecock_fl_bwd->getPressureToHose());
    hose_fl_bwd->setFlowCoeff(anglecock_fl_bwd->getFlowCoeff());
    hose_fl_bwd->setCoord(train_coord - dir * orient * (length / 2.0 - anglecock_fl_bwd->getShiftCoord()));
    hose_fl_bwd->setShiftSide(anglecock_fl_bwd->getShiftSide());
    //hose_fl_bwd->setControl(keys);
    hose_fl_bwd->step(t, dt);
}
