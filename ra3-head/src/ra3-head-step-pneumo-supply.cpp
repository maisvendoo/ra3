#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepPneumoSupply(double t, double dt)
{
    // Регулятор давления
    press_reg->setFLpressure(main_reservoir->getPressure());
    press_reg->step(t, dt);

    // Мотор-компрессор
    double U_power = aux_conv->getU_380()
                    * static_cast<double>(press_reg->getState());
    motor_compressor->setFLpressure(main_reservoir->getPressure());
    motor_compressor->setPowerVoltage(U_power);
    motor_compressor->step(t, dt);

    // Расчитываем переток из главного резервуара в запасный через обратный клапан
    double K_ps = 0.05;
    double Q_pm_sr = K_ps * pf(  main_reservoir->getPressure()
                               - supply_reservoir->getPressure());

    // Задаём главному резервуару приток от компрессора,
    // отток в запасный, расход на питание КРУ и ЭПК, потоки из рукавов
    double FL_flow = 0.0;
    FL_flow += motor_compressor->getFLflow();
    FL_flow += -Q_pm_sr;
    FL_flow += kru->getFLflow();
    FL_flow += epk->getFLflow();
    FL_flow += anglecock_fl_fwd->getFlowToPipe();
    FL_flow += anglecock_fl_bwd->getFlowToPipe();
    main_reservoir->setFlow(FL_flow);
    main_reservoir->step(t, dt);

    // Задаём запасному резервуару приток из главного,
    // расход на питание блока тормозного оборудования
    supply_reservoir->setFlow(brake_module->getSRflow() + Q_pm_sr);
    supply_reservoir->step(t, dt);
}
