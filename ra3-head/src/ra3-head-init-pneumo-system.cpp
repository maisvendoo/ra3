#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initPneumoSystem()
{
    main_res = new Reservoir(0.3);

    motor_compr = new MotorCompressor();
    motor_compr->read_custom_config(config_dir + QDir::separator() + "motor-compressor");    

    press_reg = new PressureRegulator(0.65, 0.8);

    aux_res = new Reservoir(0.1);
}
