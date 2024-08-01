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
    FL_flow += horn->getFLflow();
    FL_flow += sand_system->getFLflow();
    FL_flow += -Q_pm_sr;
    FL_flow += kru->getFLflow();
    FL_flow += epk->getFLflow();

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
    anglecock_fl_fwd->setControl(keys);
    anglecock_fl_fwd->step(t, dt);
    anglecock_fl_bwd->setPipePressure(main_reservoir->getPressure());
    //anglecock_fl_bwd->setControl(keys);
    anglecock_fl_bwd->step(t, dt);

    // Рукава питательной магистрали
    hose_fl_fwd->setPressure(anglecock_fl_fwd->getPressureToHose());
    hose_fl_fwd->setFlowCoeff(anglecock_fl_fwd->getFlowCoeff());
    hose_fl_fwd->setCoord(railway_coord + dir * orient * (length / 2.0 - anglecock_fl_fwd->getShiftCoord()));
    hose_fl_fwd->setShiftSide(anglecock_fl_fwd->getShiftSide());
    hose_fl_fwd->setControl(keys);
    hose_fl_fwd->step(t, dt);
    hose_fl_bwd->setPressure(anglecock_fl_bwd->getPressureToHose());
    hose_fl_bwd->setFlowCoeff(anglecock_fl_bwd->getFlowCoeff());
    hose_fl_bwd->setCoord(railway_coord - dir * orient * (length / 2.0 - anglecock_fl_bwd->getShiftCoord()));
    hose_fl_bwd->setShiftSide(anglecock_fl_bwd->getShiftSide());
    //hose_fl_bwd->setControl(keys);
    hose_fl_bwd->step(t, dt);
}
