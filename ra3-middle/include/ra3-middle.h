#ifndef     RA3_MIDDLE_H
#define     RA3_MIDDLE_H

#include    "vehicle-api.h"

#include    "ra3-middle-signals.h"

#include    "ra3-sme-connector.h"
#include    "battery.h"
#include    "ra3-brake-mech.h"
#include    "bto-092.h"
#include    "door-control-module.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3Middle : public Vehicle
{
public:

    RA3Middle(QObject *parent = Q_NULLPTR);

    ~RA3Middle();

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

/*    /// Расцепной рычаг спереди
    OperatingRod *oper_rod_fwd;
    /// Расцепной рычаг сзади
    OperatingRod *oper_rod_bwd;*/

    /// Серийный номер вагона
    int num = 103;

    /// Коэффициент утечки из ГР
    double main_res_leak = 0.0;

    /// Двери справа
    DoorControlModule *door_R = nullptr;
    DoorControlModule *door_R2 = nullptr;

    /// Двери слева
    DoorControlModule *door_L = nullptr;
    DoorControlModule *door_L2 = nullptr;

    /// Напряжение от батареи 110 В
    double U_bat_110 = 0.0;

    /// Напряжение питания цепей управления 110 В
    double Ucc_110 = 0.0;

    /// Батарея 110 В
    Battery *bat110 = nullptr;

    /// Контактор включения батареи 110 В
    Relay   *KM_power = nullptr;

    /// Соединения для работы по системе многих единиц (СМЕ) спереди
    RA3SME  *sme_fwd = nullptr;

    /// Соединения для работы по системе многих единиц (СМЕ) сзади
    RA3SME  *sme_bwd = nullptr;

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

    void initialization() override;

    /// Инициализация сцепных устройств
    void initCouplings(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация связей системы многих единиц (СМЕ)
    void initSME(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация цепей управления
    void initControlCircuit(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация системы обеспечения сжатым воздухом
    void initPneumoSupply(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация тормозного оборудования
    void initBrakesEquipment(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация прочего оборудования
    void initOtherEquipment(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Предварительные расчёты перед симуляцией
    void preStep(double t) override;

    /// Предварительный расчёт координат сцепных устройств
    void preStepCouplings(double t);

    /// Шаг моделирования
    void step(double t, double dt) override;

    /// Моделирование сцепных устройств
    void stepCouplings(double t, double dt);

    /// Моделирование сигналов СМЕ
    void stepSME(double t, double dt);

    /// Моделирование работы цепей управления
    void stepControlCircuit(double t, double dt);

    /// Работа системы обеспечения сжатым воздухом
    void stepPneumoSupply(double t, double dt);

    /// Работа тормозного оборудования
    void stepBrakesEquipment(double t, double dt);

    /// Работа прочего оборудования
    void stepOtherEquipment(double t, double dt);

    /// Вывод сигналов на анимации модели поезда
    void stepSignalsOutput(double t, double dt);

    /// Отладочный вывод
    void debugOutput(double t, double dt);

    void loadConfig(QString cfg_path) override;
};

#endif // RA3_MIDDLE_H
