#ifndef     RA3_HEAD_H
#define     RA3_HEAD_H

#include    "vehicle-api.h"

#include    "ra3-tumblers-define.h"
#include    "fuel-tank.h"
#include    "battery.h"
#include    "relay.h"
#include    "mpsu.h"
#include    "electric-fuel-pump.h"
#include    "disel.h"
#include    "starter.h"
#include    "hydro-pump.h"
#include    "generator.h"
#include    "aux-converter.h"
#include    "motor-compressor.h"
#include    "pressure-regulator.h"

#include    "ra3-head-signals.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3HeadMotor : public Vehicle
{
public:

    RA3HeadMotor(QObject *parent = Q_NULLPTR);

    ~RA3HeadMotor() override;    

private:

    /// Признак активной кабины
    bool is_active;

    /// Аккумуляторная батарея 110 В
    Battery     *bat110;

    /// Аккумуляторная батарея 24 В
    Battery     *bat24;

    enum
    {
        NUM_TANKS = 2,
        LEFT_TANK = 0,
        RIGHT_TANK = 1
    };

    /// Напряжение от батареи 110 В
    double U_bat_110;

    /// Напряжение питания цепей управления
    double Ucc;

    /// Контактор включения батареи 110 В
    Relay   *KM_bat_110;

    /// Микропроцессорная система управления МПСУ
    MPSU    *mpsu;

    /// Топливоподкачивающий насос
    ElectricFuelPump    *fuel_pump;

    /// Свисток и тифон
    TrainHorn *horn;

    /// Дизель
    Disel   *disel;

    /// Стартер
    Starter *starter;

    /// Реле стартера
    Relay *starter_relay;

    /// Главный генератор
    Generator   *generator;

    /// Преобразователь собственных нужд (ПСН)
    AuxiliaryConverter  *aux_conv;

    /// Насос гидростатического привода
    HydroPump   *hydro_pump;    

    /// Главный резервуар
    Reservoir   *main_res;

    /// Компрессорный агрегат
    MotorCompressor *motor_compr;

    /// Регулятор давления в ГР
    PressureRegulator *press_reg;

    /// Топливные баки
    std::array<FuelTank *, NUM_TANKS> fuel_tank;

    /// Выключатели в кабине
    std::array<Trigger, TUMBLERS_NUM> tumbler;

    void initialization() override;

    /// Инициализация системы питания топливом
    void initFuelSystem();

    /// Инициализация цепей управления
    void initControlCircuit();

    /// Инициализация дизеля
    void initDisel();

    /// Инициализация системы обеспечения сжатым воздухом
    void initPneumoSystem();

    /// Инициализация прочего оборудования
    void initOtherEquipment();

    /// Инициализация звуков
    void initSounds();

    void step(double t, double dt) override;

    /// Моедлирования работы системы питания топливом
    void stepFuelSystem(double t, double dt);

    /// Моделирование работы цепей управления
    void stepControlCircuit(double t, double dt);

    /// Моделирование работы МПСУ
    void stepMPSU(double t, double dt);

    /// Работа дизеля
    void stepDisel(double t, double dt);

    /// Работа системы обеспечения сжатым воздухом
    void stepPneumoSystem(double t, double dt);

    /// Выбод сигналов
    void stepSignalsOutput(double t, double dt);

    /// Работа прочего оборудования
    void stepOtherEquipment(double t, double dt);

    /// Связывание сигналов СМЕ
    void stepVehiclesConnect();

    /// Отладочный вывод
    void debugOutput(double t, double dt);

    /// Обработка клавиш
    void keyProcess() override;

    void loadConfig(QString cfg_path) override;

    void mdfuSignalsOutput(double t, double dt);
};

#endif // RA3_HEAD_H
