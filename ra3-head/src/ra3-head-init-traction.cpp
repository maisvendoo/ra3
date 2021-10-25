#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initTraction()
{
    hydro_trans = new HydroTransmission();
    hydro_trans->setCustomConfigDir(config_dir);
    hydro_trans->read_custom_config(config_dir +
                                    QDir::separator() +
                                    "hydro-transmission");
}
