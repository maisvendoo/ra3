#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initBrakesControl()
{
    // Кран резервного управления
    kru = new KRU091();
    kru->setCustomConfigDir(config_dir);
    kru->read_custom_config(config_dir + QDir::separator() + "kru091");

    epk = new AutoTrainStopEPK151D();
    epk->read_custom_config(config_dir + QDir::separator() + "epk");

    emerg_brake_valve = new EmergencyBrakeValve();
    emerg_brake_valve->read_custom_config(config_dir +
                                          QDir::separator() +
                                          "emergency-brake-valve");

}
