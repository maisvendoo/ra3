#ifndef     RA3_HEAD_H
#define     RA3_HEAD_H

#include    "vehicle-api.h"

#include    "ra3-tumblers-define.h"
#include    "fuel-tank.h"
#include    "battery.h"
#include    "relay.h"
#include    "mpsu.h"
#include    "ra3-sme-connector.h"
#include    "electric-fuel-pump.h"
#include    "disel.h"
#include    "starter.h"
#include    "hydro-pump.h"
#include    "generator.h"
#include    "aux-converter.h"
#include    "motor-compressor.h"
#include    "ra3-brake-mech.h"
#include    "bto-092.h"
#include    "kru-091.h"
#include    "trac-controller.h"
#include    "blok.h"
#include    "hydro-transmission.h"
#include    "registrator.h"
#include    "emergency-brake-valve.h"
#include    "key-trigger.h"
#include    "epk151d.h"

#include    "ra3-head-signals.h"

#include    "ra3-head-autostart-step.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3HeadMotor : public Vehicle
{
public:

    RA3HeadMotor(QObject *parent = Q_NULLPTR);

    ~RA3HeadMotor() override;

    void initBrakeDevices(double p0, double pBP, double pFL) override;

private:

    /// Серийный номер вагона
    int num;

    /// Передаточные числа редуктора 1 ступени
    double ip1;

    /// Передаточные числа редуктора 2 ступени
    double ip2;

    /// Регистратор параметров движения
    Registrator *reg;

    /// Зарядное давление ТМ
    double charge_press;

    /// Темп утечки из ГР
    double main_res_leak;

    /// Фактический признак активной кабины
    bool is_active;

    /// Признак активной кабины в конфигурации
    bool is_active_ref;

    /// Состояние дверей справа
    int door_R_state;

    /// Состояние дверей слева
    int door_L_state;

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

    /// Напряжение от батареи 24 В
    double U_bat_24;

    /// Напряжение питания цепей управления 110 В
    double Ucc_110;

    /// Ток, потребляемый цепями управления 110 В
    double Icc_110;

    /// Напряжение на линии 24 В
    double Ucc_24;

    /// Ток, потребляемый на линии 24 В
    double Icc_24;

    /// Контактор включения батареи 110 В
    Relay   *KM_power;

    /// Микропроцессорная система управления МПСУ
    MPSU    *mpsu;

    /// Соединения для работы по системе многих единиц (СМЕ) спереди
    RA3SME  *sme_fwd;

    /// Соединения для работы по системе многих единиц (СМЕ) сзади
    RA3SME  *sme_bwd;

    /// Свисток и тифон
    TrainHorn *horn;

    /// Топливоподкачивающий насос
    ElectricFuelPump    *fuel_pump;

    /// Дизель
    Disel   *disel;

    /// Стартер
    Starter *starter;

    /// Таймер автозапуска
    Timer   *autostart_timer;

    /// Счетчик шагов автозапуска
    size_t count_step;

    /// Признак автозапуска
    bool is_autostart;

    /// Реле стартера
    Relay *starter_relay;

    /// Главный генератор
    Generator   *generator;

    /// Преобразователь собственных нужд (ПСН)
    AuxiliaryConverter  *aux_conv;

    /// Насос гидростатического привода
    HydroPump   *hydro_pump;

    /// Компрессорный агрегат
    MotorCompressor     *motor_compressor;

    /// Регулятор давления ГР
    PressureRegulator   *press_reg;

    /// Главный резервуар
    Reservoir   *main_reservoir;

    /// Концевой кран питательной магистрали спереди
    PneumoAngleCock *anglecock_fl_fwd;

    /// Концевой кран питательной магистрали сзади
    PneumoAngleCock *anglecock_fl_bwd;

    /// Рукав питательной  магистрали спереди
    PneumoHose      *hose_fl_fwd;

    /// Рукав питательной  магистрали сзади
    PneumoHose      *hose_fl_bwd;

    /// Кран резервного управления
    KRU091  *kru;

    /// ЭПК
    AutoTrainStopEPK151D *epk;

    /// Тормозная магистраль
    Reservoir   *brakepipe;

    /// Блок тормозного оборудования БТО-092
    BTO092  *brake_module;

    /// Запасный резервуар
    Reservoir   *supply_reservoir;

    /// Концевой кран тормозной магистрали спереди
    PneumoAngleCock *anglecock_bp_fwd;

    /// Концевой кран тормозной магистрали сзади
    PneumoAngleCock *anglecock_bp_bwd;

    /// Рукав тормозной магистрали спереди
    PneumoHose   *hose_bp_fwd;

    /// Рукав тормозной магистрали сзади
    PneumoHose   *hose_bp_bwd;

    /// Тройник на питание СТ
    PneumoSplitter *pb_split;

    enum
    {
        NUM_TROLLEYS = 2,
        NUM_AXIS_PER_TROLLEY = 2,
        TROLLEY_FWD = 0,
        TROLLEY_BWD = 1
    };

    /// Тормозные механизмы тележек
    std::array<RA3BrakeMech *, NUM_TROLLEYS> brake_mech;

    /// Контроллер тяги/торможения
    TracController *km;

    /// Безопасный локомотивный объединённый комплекс (БЛОК)
    BLOK    *blok;

    /// Гидропередача
    HydroTransmission *hydro_trans;

    /// Клапан аварийного экстренного торможения
    EmergencyBrakeValve *emerg_brake_valve;

    /// Путь поиска загружаемых модулей оборудования
    QString modules_dir;

    /// Топливные баки
    std::array<FuelTank *, NUM_TANKS> fuel_tank;

    /// Индексы осей
    enum
    {
        AXIS_1 = 1,
        AXIS_2 = 2,
        AXIS_3 = 3,
        ASIS_4 = 4
    };

    /// Выключатели в кабине
    std::array<Trigger, TUMBLERS_NUM> tumbler;

    /// Кнопка "Поддержание скорости"
    KeyTrigger  button_speed_hold;

    /// Программа автозапуска
    std::vector<autostart_step_t>   autostart_prog;

    void initialization() override;

    /// Инициализация органов управления в кабине
    void initCabineControls();

    /// Инициализация связей системы многих единиц (СМЕ)
    void initSME();

    /// Инициализация переключателей
    void initTumblers(QString config_name);

    /// Инициализация системы питания топливом
    void initFuelSystem();

    /// Инициализация цепей управления
    void initControlCircuit();

    /// Инициализация дизеля
    void initDisel();

    /// Инициализация системы обеспечения сжатым воздухом
    void initPneumoSupply();

    /// Инициализация приборов управления тормозами
    void initBrakesControl();

    /// Инициализация тормозного оборудования
    void initBrakesEquipment();

    /// Инициализация приборов безопасности
    void initSafetyDevices();

    /// Инициализация подсистемы тяги (гидропередача и т.п.)
    void initTraction();

    /// Инициализация прочего оборудования
    void initOtherEquipment();

    /// Инициализация звуков
    void initSounds();

    /// Инициализация последовательности автозапуска
    void initAutostart();

    void step(double t, double dt) override;

    /// Моделирование работы органов управления в кабине
    void stepCabineControls(double t, double dt);

    /// Моделирование работы системы питания топливом
    void stepFuelSystem(double t, double dt);

    /// Моделирование работы цепей управления
    void stepControlCircuit(double t, double dt);

    /// Моделирование работы МПСУ
    void stepMPSU(double t, double dt);

    /// Моделирование сигналов СМЕ
    void stepSME(double t, double dt);

    /// Работа дизеля
    void stepDisel(double t, double dt);

    /// Работа системы обеспечения сжатым воздухом
    void stepPneumoSupply(double t, double dt);

    /// Работа приборов управления тормозами
    void stepBrakesControl(double t, double dt);

    /// Работа тормозного оборудования
    void stepBrakesEquipment(double t, double dt);

    /// Работа приборов безопасности
    void stepSafetyDevices(double t, double dt);

    /// Работа подсистемы тяги
    void stepTraction(double t, double dt);

    /// Вывод сигналов
    void stepSignalsOutput(double t, double dt);

    /// Работа прочего оборудования
    void stepOtherEquipment(double t, double dt);

    /// Работа автозапуска
    void stepAutostart(double t, double dt);

    /// Отладочный вывод
    void debugOutput(double t, double dt);

    /// Обработка клавиш
    void keyProcess() override;

    void loadConfig(QString cfg_path) override;

    /// Вывод сигналов на дисплей МФДУ
    void mdfuSignalsOutput(double t, double dt);

    /// Вывод сигналов на панель контрольных ламп
    void controlLampsSignalsOutput(double t, double dt);

    /// Регистрация параметров движения
    void stepRegistrator(double t, double dt);

    /// Вывод сигналов на дисплей БЛОК-М
    void blokSignalsOutput(double t, double dt);

    /// Вывод сигналов на анимации модели поезда
    void animationSignalsOutput(double t, double dt);

private slots:

    void slotAutostart();
};

#endif // RA3_HEAD_H
