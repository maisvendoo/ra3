#include    "ra3-head.h"

#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3HeadMotor::RA3HeadMotor(QObject *parent) : Vehicle(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3HeadMotor::~RA3HeadMotor()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initialization()
{
    // Определяем путь к загружаемым модулям оборудования
    FileSystem &fs = FileSystem::getInstance();
    QString modules_dir = QString(fs.getModulesDir().c_str());
    QString custom_cfg_dir(fs.getVehiclesDir().c_str());
    custom_cfg_dir += fs.separator() + config_dir;

    // Инициализация сцепных устройств
    initCouplings(modules_dir, custom_cfg_dir);

    // Инициализация органов управления в кабине
    initCabineControls(modules_dir, custom_cfg_dir);

    // Инициализация связей системы многих единиц (СМЕ)
    initSME(modules_dir, custom_cfg_dir);

    // Инициализация системы питания топливом
    initFuelSystem(modules_dir, custom_cfg_dir);

    // Инициализация цепей управления
    initControlCircuit(modules_dir, custom_cfg_dir);

    // Инициализация дизеля
    initDisel(modules_dir, custom_cfg_dir);

    // Инициализация системы обеспечения сжатым воздухом
    initPneumoSupply(modules_dir, custom_cfg_dir);

    // Инициализация приборов управления тормозами
    initBrakesControl(modules_dir, custom_cfg_dir);

    // Инициализация тормозного оборудования
    initBrakesEquipment(modules_dir, custom_cfg_dir);

    // Инициализация приборов безопасности
    initSafetyDevices(modules_dir, custom_cfg_dir);

    // Инициализация подсистемы тяги
    initTraction(modules_dir, custom_cfg_dir);

    // Инициализация разного оборудования
    initOtherEquipment(modules_dir, custom_cfg_dir);

    // Инициализация автозапуска
    initAutostart(modules_dir, custom_cfg_dir);

    // Инициализация регистратора
    initRegistrator(modules_dir, custom_cfg_dir);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::preStep(double t)
{
    preStepCouplings(t);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::step(double t, double dt)
{
    // Моделирование сцепных устройств
    stepCouplings(t, dt);

    // Моделирование работы органов управления в кабине
    stepCabineControls(t, dt);

    // Работа системы питания топливом
    stepFuelSystem(t, dt);

    // Работа цепей управления
    stepControlCircuit(t, dt);

    // Работа МПСУ
    stepMPSU(t, dt);

    // Моделирование сигналов СМЕ
    stepSME(t, dt);

    // Работа дизеля
    stepDisel(t, dt);

    // Работа системы обеспечения сжатым воздухом
    stepPneumoSupply(t, dt);

    // Работа приборов управления тормозами
    stepBrakesControl(t, dt);

    // Работа тормозного оборудования
    stepBrakesEquipment(t, dt);

    // Работа приборов безопасности
    stepSafetyDevices(t, dt);

    // Работа подсистемы тяги
    stepTraction(t, dt);

    // Работа разного оборудования
    stepOtherEquipment(t, dt);

    // Вывод сигналов
    stepSignalsOutput(t, dt);

    // Регистрация параметров движения
    stepRegistrator(t, dt);

    // Автозапуск
    stepAutostart(t, dt);

    // Отладочный вывод по F1
    debugOutput(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::loadConfig(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString secName = "Vehicle";

        cfg.getString(secName, "CouplingModule", coupling_fwd_module_name);
        cfg.getString(secName, "CouplingConfig", coupling_fwd_config_name);
        coupling_bwd_module_name = coupling_fwd_module_name;
        coupling_bwd_config_name = coupling_fwd_config_name;

        // Создаем и инициализируем топливные баки
        double fuel_capacity = 0;
        cfg.getDouble(secName, "FuelCapacity", fuel_capacity);

        double fuel_level = 0;
        cfg.getDouble(secName, "FuelLevel", fuel_level);

        for (size_t i = 0; i < fuel_tank.size(); ++i)
        {
            fuel_tank[i] = new FuelTank();
            fuel_tank[i]->setCapacity(fuel_capacity);
            fuel_tank[i]->setFuelLevel(fuel_level);
        }

        cfg.getDouble(secName, "MainResLeak", main_res_leak);
        cfg.getInt(secName, "Number", num);        

        cfg.getDouble(secName, "ip1", ip1);
        cfg.getDouble(secName, "ip2", ip2);

        cfg.getBool(secName, "Autostart", is_autostart);

        cfg.getBool(secName, "isRegistratorOn", is_Registrator_on);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_VEHICLE(RA3HeadMotor)
