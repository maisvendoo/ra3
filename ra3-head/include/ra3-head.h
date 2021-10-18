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
#include    "ra3-brake-mech.h"
#include    "bto-092.h"
#include    "kru-091.h"

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

    /// Зарядное давление ТМ
    double charge_press;

    /// Темп утечки из ГР
    double main_res_leak;

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

    /// Ток, потребляемый цепями управления
    double Icc;

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

    /// Запасный резервуар
    Reservoir   *aux_res;

    /// Компрессорный агрегат
    MotorCompressor *motor_compr;

    /// Регулятор давления в ГР
    PressureRegulator *press_reg;

    /// Блок тормозного оборудования БТО-092
    BTO092  *brake_module;

    /// Тройник на питание СТ
    PneumoSplitter *pb_split;

    /// Кран резервного управления
    KRU091  *kru;

    /// Топливные баки
    std::array<FuelTank *, NUM_TANKS> fuel_tank;

    enum
    {
        NUM_TROLLEYS = 2,
        FWD_TROLLEY = 0,
        BWD_TROLLEY = 1
    };

    /// Индексы осей
    enum
    {
        AXIS_1 = 1,
        AXIS_2 = 2,
        AXIS_3 = 3,
        ASIS_4 = 4
    };

    /// Тормозная механика тележек
    std::array<RA3BrakeMech *, NUM_TROLLEYS> brake_mech;

    /// Выключатели в кабине
    std::array<Trigger, TUMBLERS_NUM> tumbler;

    void initialization() override;

    void initBrakeDevices(double p0, double pTM, double pFL) override;

    /// Инициализация органов управления в кабине
    void initCabineControls();

    /// Инициализация переключателей
    void initTumblers(QString config_name);

    /// Инициализация системы питания топливом
    void initFuelSystem();

    /// Инициализация цепей управления
    void initControlCircuit();

    /// Инициализация дизеля
    void initDisel();

    /// Инициализация системы обеспечения сжатым воздухом
    void initPneumoSystem();

    /// Инициализация механической части тормозной системы
    void initBrakeMech();

    /// Инициализация тормозного оборудования
    void initBrakeEquipment();

    /// Инициализация приборов управления тормозами
    void initBrakeControls();

    /// Инициализация прочего оборудования
    void initOtherEquipment();

    /// Инициализация звуков
    void initSounds();

    void step(double t, double dt) override;

    /// Моделирование работы органов управления в кабине
    void stepCabineControls(double t, double dt);

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

    /// Работа механической части тормозной системы
    void stepBrakeMech(double t, double dt);

    /// Работа тормозного оборудования
    void stepBrakeEquipment(double t, double dt);

    /// Работа приборов управления тормозами
    void stepBrakeControls(double t, double dt);

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

    /// Вывод сигналов на дисплей МФДУ
    void mdfuSignalsOutput(double t, double dt);

    /// Вывод сигналов на панель контрольных ламп
    void controlLampsSignalsOutput(double t, double dt);

    /// Вывод сигналов СМЕ
    void stepSMESignalsOutput(double t, double dt);
};

#endif // RA3_HEAD_H
