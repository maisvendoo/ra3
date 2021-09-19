#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3HeadMotor::RA3HeadMotor(QObject *parent) : Vehicle(parent)
  , bat110(Q_NULLPTR)
  , bat24(Q_NULLPTR)
  , Ucc(0.0)
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
    // Инициализация системы питания топливом
    initFuelSystem();

    // Инициализация цепей управления
    initControlCircuit();

    // Инициализация озвучки
    initSounds();
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
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_VEHICLE(RA3HeadMotor)
