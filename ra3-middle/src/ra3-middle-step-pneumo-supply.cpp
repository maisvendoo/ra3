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
    FL_flow += anglecock_fl_fwd->getFlowToPipe();
    FL_flow += anglecock_fl_bwd->getFlowToPipe();
    main_reservoir->setFlow(FL_flow);
    main_reservoir->step(t, dt);

    // Задаём запасному резервуару приток из главного,
    // расход на питание блока тормозного оборудования
    supply_reservoir->setFlow(brake_module->getSRflow() + Q_pm_sr);
    supply_reservoir->step(t, dt);
}
