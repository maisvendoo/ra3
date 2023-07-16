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

    blok->setMaxVelocity(120);

    // Загрузка электронной карты в БЛОК
    QString speeds_name = "speeds";

    if (dir > 0)
        speeds_name += "1";
    else
        speeds_name += "2";

    QString path = QDir::toNativeSeparators(route_dir) +
            QDir::separator() + speeds_name + ".conf";

    blok->loadSpeedsMap(path);
    blok->setDirection(dir * orient);
    blok->setTrainLength(mpsu->getOutputData().train_length);

    // Загрузка станций в БЛОК
    path = QDir::toNativeSeparators(route_dir) +
            QDir::separator() + "stations.conf";

    blok->loadStationsMap(path);
}
