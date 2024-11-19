#include    "ra3-middle.h"

#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3Middle::RA3Middle(QObject *parent) : Vehicle(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3Middle::~RA3Middle()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::initialization()
{
    // Определяем путь к загружаемым модулям оборудования
    FileSystem &fs = FileSystem::getInstance();
    QString modules_dir = QString(fs.getModulesDir().c_str());
    QString custom_cfg_dir(fs.getVehiclesDir().c_str());
    custom_cfg_dir += fs.separator() + config_dir;

    // Инициализация сцепных устройств
    initCouplings(modules_dir, custom_cfg_dir);

    // Инициализация связей системы многих единиц (СМЕ)
    initSME(modules_dir, custom_cfg_dir);

    // Инициализация цепей управления
    initControlCircuit(modules_dir, custom_cfg_dir);

    // Инициализация системы обеспечения сжатым воздухом
    initPneumoSupply(modules_dir, custom_cfg_dir);

    // Инициализация тормозного оборудования
    initBrakesEquipment(modules_dir, custom_cfg_dir);

    // Инициализация разного оборудования
    initOtherEquipment(modules_dir, custom_cfg_dir);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::preStep(double t)
{
    preStepCouplings(t);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::step(double t, double dt)
{
    // Моделирование сцепных устройств
    stepCouplings(t, dt);

    // Моделирование сигналов СМЕ
    stepSME(t, dt);

    // Работа цепей управления
    stepControlCircuit(t, dt);

    // Работа системы обеспечения сжатым воздухом
    stepPneumoSupply(t, dt);

    // Работа тормозного оборудования
    stepBrakesEquipment(t, dt);

    // Работа разного оборудования
    stepOtherEquipment(t, dt);

    // Вывод сигналов
    stepSignalsOutput(t, dt);

    // Отладочный вывод по F1
    debugOutput(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::loadConfig(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString secName = "Vehicle";

        cfg.getDouble(secName, "MainResLeak", main_res_leak);
        cfg.getInt(secName, "Number", num);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_VEHICLE(RA3Middle)
