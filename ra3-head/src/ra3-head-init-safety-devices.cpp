#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initSafetyDevices()
{
    blok = new BLOK();
    blok->read_custom_config(config_dir +
                             QDir::separator() +
                             "blok");

    epk = loadAutoTrainStop(modules_dir +
                            QDir::separator() +
                            "epk150");
    epk->read_custom_config(config_dir +
                            QDir::separator() +
                            "epk");
}
