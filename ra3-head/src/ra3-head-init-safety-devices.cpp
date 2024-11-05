#include    "ra3-head.h"

#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initSafetyDevices(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;
    (void) custom_cfg_dir;

    // Карта ограничений скорости
    speedmap_fwd = new SpeedMap();
    speedmap_fwd->setDirection(dir * orient);
    addRailwayConnector(speedmap_fwd, length / 2.0);

    // Приёмная катушка АЛСН
    coil_ALSN_fwd = new CoilALSN();
    coil_ALSN_fwd->setDirection(dir * orient);
    addRailwayConnector(coil_ALSN_fwd, length / 2.0);

    // Дешифратор АЛСН
    alsn_decoder = new DecoderALSN();
    alsn_decoder->read_config("ALSN-decoder");

    // БЛОК
    blok = new BLOK();
    //Конфиг для БЛОК не сделан
    //blok->read_config("blok", custom_cfg_dir);
    blok->setMaxVelocity(120.0);
    blok->setSpeedMapModule(speedmap_fwd);
    blok->setDirection(dir * orient);
    blok->setTrainLength(mpsu->getOutputData().train_length);

    // Загрузка станций в БЛОК
    FileSystem &fs = FileSystem::getInstance();
    QString path = fs.getRouteRootDir().c_str();
    path += QDir::separator() + route_dir;
    path += QDir::separator() + QString("topology");
    path += QDir::separator() + QString("stations.conf");
    blok->loadStationsMap(path);
}
