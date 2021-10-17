#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3HeadMotor::RA3HeadMotor(QObject *parent) : Vehicle(parent)
  , main_res_leak(0.0)
  , is_active(false)
  , bat110(Q_NULLPTR)
  , bat24(Q_NULLPTR)
  , U_bat_110(0.0)
  , Ucc(0.0)
  , Icc(0.0)
  , KM_bat_110(Q_NULLPTR)
  , mpsu(Q_NULLPTR)
  , fuel_pump(Q_NULLPTR)
  , horn(Q_NULLPTR)
  , disel(Q_NULLPTR)
  , starter(Q_NULLPTR)
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
    // Инициализация органов управления в кабине
    initCabineControls();

    // Инициализация системы питания топливом
    initFuelSystem();

    // Инициализация цепей управления
    initControlCircuit();

    // Инициализация дизеля
    initDisel();

    // Инициализация системы обеспечения сжатым воздухом
    initPneumoSystem();

    // Инициализируем тормозные механизмы
    initBrakeMech();

    // Инициализация тормозного оборудования
    initBrakeEquipment();

    // Инициализация разного оборудования
    initOtherEquipment();

    // Инициализация озвучки
    initSounds();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initBrakeDevices(double p0, double pTM, double pFL)
{
    main_res->setY(0, pFL);
    aux_res->setY(0, pFL);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::step(double t, double dt)
{
    // Работа системы питания топливом
    stepFuelSystem(t, dt);

    // Работа цепей управления
    stepControlCircuit(t, dt);

    // Работа МПСУ
    stepMPSU(t, dt);

    // Работа дизеля
    stepDisel(t, dt);

    // Работа системы обеспечения сжатым воздухом
    stepPneumoSystem(t, dt);

    // Работа тормозных механизмов
    stepBrakeMech(t, dt);

    // Работа тормозного оборудования
    stepBrakeEquipment(t, dt);

    // Работа разного оборудования
    stepOtherEquipment(t, dt);

    // Вывод сигналов
    stepSignalsOutput(t, dt);

    // Обрабока линий СМЕ
    stepVehiclesConnect();

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

        cfg.getBool(secName, "IsActive", is_active);

        cfg.getDouble(secName, "MainResLeak", main_res_leak);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_VEHICLE(RA3HeadMotor)
