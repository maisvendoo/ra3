#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepPneumoSystem(double t, double dt)
{
    // Расчитываем переток из главного резервуара в запасный через обратный клапан
    double K_pa = 0.05;
    double Q_pm_ar = K_pa * pf(main_res->getPressure() - aux_res->getPressure());

    main_res->setAirFlow(motor_compr->getAirFlow() - Q_pm_ar);
    main_res->setFlowCoeff(main_res_leak);
    main_res->step(t, dt);

    motor_compr->setU_power(aux_conv->getU_380() * press_reg->getState());
    motor_compr->setExternalPressure(main_res->getPressure());
    motor_compr->step(t, dt);    

    press_reg->setPressure(main_res->getPressure());
    press_reg->step(t, dt);

    aux_res->setAirFlow(brake_module->getAirSupplyFlow() + Q_pm_ar);
    aux_res->setFlowCoeff(main_res_leak);
    aux_res->step(t, dt);
}
