#ifndef     RA3_MIDDLE_H
#define     RA3_MIDDLE_H

#include    "vehicle-api.h"

#include    "ra3-middle-signals.h"

#include    "battery.h"
#include    "ra3-brake-mech.h"
#include    "bto-092.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3Middle : public Vehicle
{
public:

    RA3Middle(QObject *parent = Q_NULLPTR);

    ~RA3Middle();

private:

    enum
    {
        NUM_TROLLEY = 2,
        FWD_TROLLEY = 0,
        BWD_TROLLEY = 1
    };

    /// Серийный номер вагона
    int num;

    /// Состояние дверей справа
    int door_R_state;

    /// Состояние дверей слева
    int door_L_state;

    /// Напряжение от батареи 110 В
    double U_bat_110;

    /// Напряжение питания цепей управления 110 В
    double Ucc_110;

    /// Батарея 110 В
    Battery *bat110;

    /// Контактор включения батареи 110 В
    Relay   *KM_power;

    /// Главный резервуар
    Reservoir *main_res;

    /// Запасный резервуар
    Reservoir *aux_res;

    /// Коэффициент утечки из ГР
    double main_res_leak;

    /// Переток воздуха из ПМ заднего вагона
    double Q_pm_bwd;
    /// Переток воздуха из ПМ переднего вагона
    double Q_pm_fwd;

    /// Блок тормозного оборудования (БТО-092)
    BTO092 *brake_module;

    /// Разветвитель на стояночный тормоз
    PneumoSplitter *pb_split;

    /// Разветвитель на магистраль ТЦ
    PneumoSplitter *bc_split;

    /// Тормозные механизмы тележек
    std::array<RA3BrakeMech *, NUM_TROLLEY> brake_mech;

    void initialization() override;

    void initBrakeDevices(double p0, double pTM, double pFL) override;

    void initControlCircuit();

    void initPneumoSystem();

    void initBrakeMech();

    void initBrakeEquipment();

    void step(double t, double dt) override;

    void stepControlCircuit(double t, double dt);

    void stepPneumoSystem(double t, double dt);

    void stepBrakeMech(double t, double dt);

    void stepBrakeEquipment(double t, double dt);

    void stepSignalsOutput(double t, double dt);

    /// Работа сигналов СМЕ
    void stepSMESignalsOutput(double t, double dt);

    void stepVehiclesConnect();

    void debugOutput(double t, double dt);

    void loadConfig(QString cfg_path) override;
};

#endif // RA3_MIDDLE_H
