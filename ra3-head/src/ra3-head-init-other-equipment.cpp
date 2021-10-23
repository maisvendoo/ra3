#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initOtherEquipment()
{
    horn = new TrainHorn();

    hydro_pump = new HydroPump();
    hydro_pump->read_custom_config(config_dir +
                                   QDir::separator() +
                                   "hydro-pump");

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
