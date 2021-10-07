#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepPneumoSystem(double t, double dt)
{
    main_res->setAirFlow(motor_compr->getAirFlow());
    main_res->step(t, dt);

    motor_compr->setU_power(aux_conv->getU_380() * press_reg->getState());
    motor_compr->setExternalPressure(main_res->getPressure());
    motor_compr->step(t, dt);

    press_reg->setPressure(main_res->getPressure());
    press_reg->step(t, dt);
}
