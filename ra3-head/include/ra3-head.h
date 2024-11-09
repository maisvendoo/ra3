#ifndef     RA3_HEAD_H
#define     RA3_HEAD_H

#include    "vehicle-api.h"

#include    "ra3-tumblers-define.h"
#include    "fuel-tank.h"
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
#include    "emergency-brake-valve.h"
#include    "epk151d.h"
#include    "door-control-module.h"

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

    /// Имя модуля сцепного устройства спереди
    QString coupling_fwd_module_name = "sa3";
    /// Имя конфига сцепного устройства спереди
    QString coupling_fwd_config_name = "sa3";

    /// Имя модуля сцепного устройства сзади
    QString coupling_bwd_module_name = "sa3";
    /// Имя конфига сцепного устройства сзади
    QString coupling_bwd_config_name = "sa3";

    /// Сцепка спереди
    Coupling *coupling_fwd = nullptr;
    /// Сцепка сзади
    Coupling *coupling_bwd = nullptr;

    /// Расцепной рычаг спереди
    OperatingRod *oper_rod_fwd = nullptr;
/*    /// Расцепной рычаг сзади
    OperatingRod *oper_rod_bwd = nullptr;*/

    /// Серийный номер вагона
    int num = 101;

    /// Передаточные числа редуктора 1 ступени
    double ip1 = 1.2;

    /// Передаточные числа редуктора 2 ступени
    double ip2 = 2.78;

    /// Регистратор параметров движения
    Registrator *reg = nullptr;

    /// Темп утечки из ГР
    double main_res_leak = 0.0;

    /// Реле активной кабины
    Relay   *active_cab_relay = nullptr;

    /// Дверь справа
    DoorControlModule *door_R = nullptr;

    /// Дверь слева
    DoorControlModule *door_L = nullptr;

    /// Аккумуляторная батарея 110 В
    Battery     *bat110 = nullptr;

    /// Аккумуляторная батарея 24 В
    Battery     *bat24 = nullptr;

    /// Напряжение от батареи 110 В
    double U_bat_110 = 0.0;

    /// Напряжение от батареи 24 В
    double U_bat_24 = 0.0;

    /// Напряжение питания цепей управления 110 В
    double Ucc_110 = 0.0;

    /// Ток, потребляемый цепями управления 110 В
    double Icc_110 = 0.0;

    /// Напряжение на линии 24 В
    double Ucc_24 = 0.0;

    /// Ток, потребляемый на линии 24 В
    double Icc_24 = 0.0;

    /// Контактор включения батареи 110 В
    Relay   *KM_power = nullptr;

    /// Микропроцессорная система управления МПСУ
    MPSU    *mpsu = nullptr;

    /// Соединения для работы по системе многих единиц (СМЕ) спереди
    RA3SME  *sme_fwd = nullptr;

    /// Соединения для работы по системе многих единиц (СМЕ) сзади
    RA3SME  *sme_bwd = nullptr;

    /// Свисток и тифон
    TrainHorn *horn = nullptr;

    /// Система подачи песка под оси передней (моторной) тележки
    SandingSystem   *sand_system = nullptr;

    /// Топливоподкачивающий насос
    ElectricFuelPump    *fuel_pump = nullptr;

    /// Дизель
    Disel   *disel = nullptr;

    /// Стартер
    Starter *starter = nullptr;

    /// Таймер автозапуска
    Timer   *autostart_timer = nullptr;

    /// Счетчик шагов автозапуска
    size_t count_step = 0;

    /// Признак автозапуска
    bool is_autostart = false;

    /// Признак включения регистрации
    bool is_Registrator_on = false;

    /// Реле стартера
    Relay *starter_relay = nullptr;

    /// Главный генератор
    Generator   *generator = nullptr;

    /// Преобразователь собственных нужд (ПСН)
    AuxiliaryConverter  *aux_conv = nullptr;

    /// Насос гидростатического привода
    HydroPump   *hydro_pump = nullptr;

    /// Компрессорный агрегат
    MotorCompressor     *motor_compressor = nullptr;

    /// Регулятор давления ГР
    PressureRegulator   *press_reg = nullptr;

    /// Главный резервуар
    Reservoir   *main_reservoir = nullptr;

    /// Концевой кран питательной магистрали спереди
    PneumoAngleCock *anglecock_fl_fwd = nullptr;

    /// Концевой кран питательной магистрали сзади
    PneumoAngleCock *anglecock_fl_bwd = nullptr;

    /// Рукав питательной  магистрали спереди
    PneumoHose      *hose_fl_fwd = nullptr;

    /// Рукав питательной  магистрали сзади
    PneumoHose      *hose_fl_bwd = nullptr;

    /// Кран резервного управления
    KRU091  *kru = nullptr;

    /// ЭПК
    AutoTrainStopEPK151D *epk = nullptr;

    /// Тормозная магистраль
    Reservoir   *brakepipe = nullptr;

    /// Блок тормозного оборудования БТО-092
    BTO092  *brake_module = nullptr;

    /// Запасный резервуар
    Reservoir   *supply_reservoir = nullptr;

    /// Концевой кран тормозной магистрали спереди
    PneumoAngleCock *anglecock_bp_fwd = nullptr;

    /// Концевой кран тормозной магистрали сзади
    PneumoAngleCock *anglecock_bp_bwd = nullptr;

    /// Рукав тормозной магистрали спереди
    PneumoHose   *hose_bp_fwd = nullptr;

    /// Рукав тормозной магистрали сзади
    PneumoHose   *hose_bp_bwd = nullptr;

    /// Тройник на питание СТ
    PneumoSplitter *pb_split = nullptr;

    enum
    {
        NUM_TROLLEYS = 2,
        NUM_AXIS_PER_TROLLEY = 2,
        TROLLEY_FWD = 0,
        TROLLEY_BWD = 1
    };

    /// Тормозные механизмы тележек
    std::array<RA3BrakeMech *, NUM_TROLLEYS> brake_mech = {nullptr, nullptr};

    /// Контроллер тяги/торможения
    TracController *km = nullptr;

    /// Безопасный локомотивный объединённый комплекс (БЛОК)
    BLOK    *blok = nullptr;

    /// Гидропередача
    HydroTransmission *hydro_trans = nullptr;

    /// Клапан аварийного экстренного торможения
    EmergencyBrakeValve *emerg_brake_valve = nullptr;

    double tractionForce = 0.0;

    enum
    {
        NUM_TANKS = 2,
        LEFT_TANK = 0,
        RIGHT_TANK = 1
    };

    /// Топливные баки
    std::array<FuelTank *, NUM_TANKS> fuel_tank = {nullptr, nullptr};

    /// Выключатели в кабине
    std::array<Trigger, TUMBLERS_NUM> tumbler;

    /// Ограничения скорости на путевой инфраструктуре
    SpeedMap    *speedmap_fwd = nullptr;

    /// Приёмная катушка АЛСН
    CoilALSN    *coil_ALSN_fwd = nullptr;

    /// Дешифратор сигнала АЛСН
    DecoderALSN *alsn_decoder = nullptr;

    /// Программа автозапуска
    std::vector<autostart_step_t>   autostart_prog;

    void initialization() override;

    /// Инициализация сцепных устройств
    void initCouplings(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация органов управления в кабине
    void initCabineControls(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация связей системы многих единиц (СМЕ)
    void initSME(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация переключателей
    void initTumblers(const QString &config_name, const QString &custom_cfg_dir);

    /// Инициализация системы питания топливом
    void initFuelSystem(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация цепей управления
    void initControlCircuit(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация дизеля
    void initDisel(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация системы обеспечения сжатым воздухом
    void initPneumoSupply(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация приборов управления тормозами
    void initBrakesControl(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация тормозного оборудования
    void initBrakesEquipment(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация приборов безопасности
    void initSafetyDevices(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация подсистемы тяги (гидропередача и т.п.)
    void initTraction(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация прочего оборудования
    void initOtherEquipment(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация последовательности автозапуска
    void initAutostart(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация регистратора
    void initRegistrator(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Предварительные расчёты перед симуляцией
    void preStep(double t) override;

    /// Предварительный расчёт координат сцепных устройств
    void preStepCouplings(double t);

    /// Шаг моделирования
    void step(double t, double dt) override;

    /// Моделирование сцепных устройств
    void stepCouplings(double t, double dt);

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

    /// Вывод сигналов звучки
    void stepSoundSignalsOutput(double t, double dt);

private slots:

    void slotAutostart();
};

#endif // RA3_HEAD_H
