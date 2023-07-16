#include    "ra3-head.h"

#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3HeadMotor::RA3HeadMotor(QObject *parent) : Vehicle(parent)
  , num(4001)
  , ip1(1.2)
  , ip2(2.78)
  , reg(Q_NULLPTR)
  , charge_press(0.5)
  , main_res_leak(0.0)
  , is_active(false)
  , is_active_ref(false)
  , door_R_state(1)
  , door_L_state(1)
  , bat110(Q_NULLPTR)
  , bat24(Q_NULLPTR)
  , U_bat_110(0.0)
  , U_bat_24(0.0)
  , Ucc_110(0.0)
  , Icc_110(0.0)
  , Ucc_24(0.0)
  , Icc_24(0.0)
  , KM_power(Q_NULLPTR)
  , mpsu(Q_NULLPTR)
  , horn(Q_NULLPTR)
  , fuel_pump(Q_NULLPTR)
  , disel(Q_NULLPTR)
  , starter(Q_NULLPTR)
  , autostart_timer(Q_NULLPTR)
  , count_step(0)
  , is_autostart(false)
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
    modules_dir = QString(fs.getModulesDir().c_str());

    // Инициализация органов управления в кабине
    initCabineControls();

    // Инициализация связей системы многих единиц (СМЕ)
    initSME();

    // Инициализация системы питания топливом
    initFuelSystem();

    // Инициализация цепей управления
    initControlCircuit();

    // Инициализация дизеля
    initDisel();

    // Инициализация системы обеспечения сжатым воздухом
    initPneumoSupply();

    // Инициализация приборов управления тормозами
    initBrakesControl();

    // Инициализация тормозного оборудования
    initBrakesEquipment();

    // Инициализация приборов безопасности
    initSafetyDevices();

    // Инициализация подсистемы тяги
    initTraction();

    // Инициализация разного оборудования
    initOtherEquipment();

    // Инициализация озвучки
    initSounds();

    // Инициализация автозапуска
    initAutostart();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::step(double t, double dt)
{
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

        cfg.getBool(secName, "IsActive", is_active_ref);

        cfg.getDouble(secName, "MainResLeak", main_res_leak);
        cfg.getInt(secName, "Number", num);

        QString log_name;
        if (cfg.getString(secName, "LogName", log_name))
        {
            double timeout = 0.1;
            cfg.getDouble(secName, "LogTimeout", timeout);

            reg = new Registrator(log_name, timeout);
        }

        cfg.getDouble(secName, "ip1", ip1);
        cfg.getDouble(secName, "ip2", ip2);

        cfg.getBool(secName, "Autostart", is_autostart);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_VEHICLE(RA3HeadMotor)
