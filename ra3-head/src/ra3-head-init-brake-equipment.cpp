#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initBrakeEquipment()
{
    brake_module = new BTO092();
    brake_module->read_custom_config(config_dir + QDir::separator() + "bto092");
}
