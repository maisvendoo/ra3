#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepPneumoSystem(double t, double dt)
{
    // Расчитываем переток из главного резервуара в запасный через обратный клапан
    double K_pa = 0.05;
    double Q_pm_ar = K_pa * pf(main_res->getPressure() - aux_res->getPressure());

    // Расчитываем переток воздуха из ПМ переднего вагона
    double K_pm_fwd = 0.05;
    double Q_pm_fwd = K_pm_fwd * pf(forward_inputs[SME_PM_PRESSURE] - main_res->getPressure());

    // Расчитываем переток воздуха из ПМ заднего вагона
    double K_pm_bwd = 0.05;
    double Q_pm_bwd = K_pm_bwd * pf(backward_inputs[SME_PM_PRESSURE] - main_res->getPressure());

    main_res->setAirFlow(Q_pm_fwd + Q_pm_bwd - Q_pm_ar);
    main_res->setFlowCoeff(main_res_leak);
    main_res->step(t, dt);

    aux_res->setAirFlow(brake_module->getAirSupplyFlow() + Q_pm_ar);
    aux_res->setFlowCoeff(main_res_leak);
    aux_res->step(t, dt);
}
