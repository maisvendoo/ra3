#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initPneumoSupply(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;
    (void) custom_cfg_dir;

    // Регулятор давления в ГР
    press_reg = new PressureRegulator(0.65, 0.8);

    // Мотор-компрессор
    motor_compressor = new MotorCompressor();
    motor_compressor->read_config("motor-compressor", custom_cfg_dir);

    // Главный резервуар
    double volume_main = 0.3;
    main_reservoir = new Reservoir(volume_main);
    main_reservoir->setLeakCoeff(main_res_leak);

    // Запасный резервуар
    supply_reservoir = new Reservoir(0.1);
    supply_reservoir->setLeakCoeff(main_res_leak);

    // Концевые краны питательной магистрали
    anglecock_fl_fwd = new PneumoAngleCock();
    anglecock_fl_fwd->setKeyCode(KEY_F6);
    anglecock_fl_fwd->read_config("pneumo-anglecock-FL");

    anglecock_fl_bwd = new PneumoAngleCock();
    //anglecock_fl_bwd->setKeyCode(KEY_F7);
    anglecock_fl_bwd->read_config("pneumo-anglecock-FL");

    // Рукава питательной магистрали
    hose_fl_fwd = new PneumoHose();
    hose_fl_fwd->setKeyCode(KEY_F5);
    hose_fl_fwd->read_config("pneumo-hose-FL");
    forward_connectors.push_back(hose_fl_fwd);

    hose_fl_bwd = new PneumoHose();
    //hose_fl_bwd->setKeyCode(KEY_F8);
    hose_fl_bwd->read_config("pneumo-hose-FL");
    backward_connectors.push_back(hose_fl_bwd);
}
