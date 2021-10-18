#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initBrakeControls()
{
    kru = new KRU091();
    kru->setCustomConfigDir(config_dir);
    kru->read_custom_config(config_dir + QDir::separator() + "kru091");
}
