#include    "ra3-head.h"

#include    "filesystem.h"

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
    sand_system->read_config("sanding-system", custom_cfg_dir);
    sand_system->setSandLevel(payload_coeff);

    hydro_pump = new HydroPump();
    hydro_pump->read_config("hydro-pump", custom_cfg_dir);

    // Двери
    door_L = new DoorControlModule();
    door_L->read_config("door-control-module", custom_cfg_dir);
    door_R = new DoorControlModule();
    door_R->read_config("door-control-module", custom_cfg_dir);

    // БУЦИК
    bucik = new BUCIK();
    FileSystem &fs = FileSystem::getInstance();
    QString path = fs.getRouteRootDir().c_str();
    path += QDir::separator() + route_dir;
    path += QDir::separator() + QString("topology");
    path += QDir::separator() + QString("stations.conf");
    bucik->loadStations(path);
}
