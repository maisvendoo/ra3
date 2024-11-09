#include    "ra3-middle.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::initOtherEquipment(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;

    door_L = new DoorControlModule();
    door_L->read_config("door-control-module", custom_cfg_dir);
    door_R = new DoorControlModule();
    door_R->read_config("door-control-module", custom_cfg_dir);
}
