#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initOtherEquipment(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;

    horn = new TrainHorn();
    horn->read_config("train-horn");

    // Система подачи песка под оси передней (моторной) тележки
    sand_system = new SandingSystem();
    sand_system->read_config("sanding-system");
    sand_system->setSandLevel(payload_coeff);

    hydro_pump = new HydroPump();
    hydro_pump->read_config("hydro-pump", custom_cfg_dir);
}
