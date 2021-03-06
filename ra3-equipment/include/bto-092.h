#ifndef     BTO_092_H
#define     BTO_092_H

#include    "airdistributor.h"
#include    "hysteresis.h"
#include    "switching-valve.h"
#include    "pneumo-reducer.h"
#include    "pneumo-relay.h"
#include    "reservoir.h"
#include    "electro-lock-valve.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class BTO092 : public AirDistributor
{
public:

    BTO092(QObject *parent = Q_NULLPTR);

    ~BTO092();

    void setParkingBrakePressure(double p_pb) { this->p_pb = p_pb; }

    double getParkingBrakeAirFlow() const { return Q_pb; }

    void setParkingBrakeState(bool is_parking_braked)
    {
        this->is_parking_brake_ON = is_parking_braked;
    }

    void setVoltage(double U_pow) { this->U_pow = U_pow; }

    bool isParkingBraked();

    void step(double t, double dt) override;

    void releaseBrakes(bool is_release) { this->is_release = is_release; }

    void setRefPressureLevel(double p_ref) { this->p_ref = p_ref * pBC_max; }

    double getMaxBrakeCylinderPressure() const { return pBC_max; }

private:

    /// Давление в магистрали стояночного тормоза
    double p_pb;

    /// Поток в магистраль стояночного тормоза
    double Q_pb;

    /// Состояние стояночного тормоза
    bool is_parking_brake_ON;

    /// Признак срабатывания стояночного тормоза
    bool is_parking_braked;

    /// Уставка давления в цилиндрах стояночного тормоза (ЦСТ)
    double pPB_max;

    /// Напряжение питания
    double U_pow;

    /// Номинальное напряжение питания
    double U_nom;

    /// Переключательный клапан
    SwitchingValve *sw_valve;

    /// Редуктор питания магистрали ТЦ
    PneumoReducer *bc_reducer;

    /// Реле давления для наполнения ТЦ
    PneumoReley *bc_relay;

    /// Максимальное давление в тормозных цилиндрах
    double pBC_max;

    /// Условная площадь управляющего поршня
    double A;

    /// Давление пружин
    double ps;

    /// Условный резервуар, имитирующий рабочую полость КПУ
    Reservoir   *work_res;

    /// Сигнал включения КЭБ для отпуска тормозов
    bool is_release;

    /// КЭБ (Клапан электроблокировочный)
    ElectroLockValve *keb;

    /// Вентиль отпуска ЭПТ (ВО)
    Relay   *release_valve;

    /// Вентиль торможения ЭПТ (ВТ)
    Relay   *brake_valve;    

    /// Заданное давление в ТЦ для ЭПТ
    double p_ref;

    /// Точность поддержания давления в ТЦ при ЭПТ
    double ept_eps;

    /// Минимальная ступень торможения ЭПТ
    double p_min;

    int state_ept;

    bool pb_brake_play;

    enum
    {
        NUM_COEFFS = 10
    };

    std::array<double, NUM_COEFFS> K;

    /// Гистерезисный блок, для определения статуса СТ
    Hysteresis  parking_brake;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    /// Моделирование управления стояночным тормозом
    void stepParkingBrake();

    /// Моделирование работы пневматического торможения
    void stepPneumoBrake();

    /// Регулятор ЭПТ
    void pressureRegulatorEPT(double p_ref, double p);
};

#endif // BTO092_H
