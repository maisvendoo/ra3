#ifndef     BTO_092_H
#define     BTO_092_H

#include    "airdistributor.h"
#include    "hysteresis.h"
#include    "pneumo-switching-valve.h"
#include    "pneumo-reducer.h"
#include    "pneumo-relay.h"
//#include    "electro-lock-valve.h"
#include    "relay.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class BTO092 : public AirDistributor
{
public:

    BTO092(QObject *parent = Q_NULLPTR);

    ~BTO092();

    /// Задать питающее напряжение
    void setPowerVoltage(double value);

    /// Задать давление от тормозных цилиндров передней (моторной) тележки
    void setBCpressure1(double value);

    /// Поток в тормозные цилиндры передней (моторной) тележки
    double getBCflow1() const;

    /// Задать давление от тормозных цилиндров задней (безмоторной) тележки
    void setBCpressure2(double value);

    /// Поток в тормозные цилиндры задней (безмоторной) тележки
    double getBCflow2() const;

    /// Задать давление от камер отпуска стояночного тормоза
    void setPBpressure(double value);

    /// Поток в камеры отпуска стояночного тормоза
    double getPBflow() const;

    /// Задать состояние стояночного тормоза
    void setParkingBrakeState(bool is_parking_braked);

    /// Состояние стояночного тормоза
    bool isParkingBraked();

    /// Задать отпуск пневматических тормозов на моторной тележке
    void releaseBrakes(bool release);

    /// Задать требуемый уровень электропневматического торможения
    void setRefEPBlevel(double ref_level);

    /// Максимальное давление в тормозных цилиндрах
    double getMaxBCpressure() const;

    /// Шаг моделирования блока тормозного оборудования
    void step(double t, double dt) override;

private:

    /// Давление от магистрали отпуска стояночного тормоза
    double pBC_motor;

    /// Поток в тормозные цилиндры передней (моторной) тележки
    double QBC_motor;

    /// Давление от магистрали отпуска стояночного тормоза
    double pPB;

    /// Поток в магистраль отпуска стояночного тормоза
    double QPB;

    /// Уставка давления в цилиндрах стояночного тормоза (ЦСТ)
    double pPB_max;

    /// Состояние стояночного тормоза
    bool ref_parking_brake_state;

    /// Гистерезисный блок, для определения статуса стояночного тормоза
    Hysteresis  *parking_brake_state;

    /// Напряжение питания
    double U_pow;

    /// Номинальное напряжение питания
    double U_nom;

    /// Максимальное давление в тормозных цилиндрах
    double pBC_max;

    /// Редуктор питания магистрали ТЦ
    PneumoReducer *bc_reducer;

    /// Переключательный клапан
    SwitchingValve *sw_valve;

    /// Реле давления для наполнения ТЦ передней (моторной) тележки
    PneumoRelay *bc_relay1;

    /// Реле давления для наполнения ТЦ задней (безмоторной) тележки
    PneumoRelay *bc_relay2;

    /// Условная площадь управляющего поршня
    double A;

    /// Давление пружин
    double ps;

    /// Сигнал включения КЭБ для отпуска тормозов
    bool is_release;
/*
    /// КЭБ (Клапан электроблокировочный)
    ElectroLockValve *keb;
*/
    /// Вентиль отпуска ЭПТ (ВО)
    Relay   *release_valve;

    /// Вентиль торможения ЭПТ (ВТ)
    Relay   *brake_valve;

    /// Заданное давление в ТЦ для ЭПТ
    double p_ref;

    /// Точность поддержания давления в ТЦ при ЭПТ
    double ept_eps;

    /// Минимальная ступень торможения ЭПТ
    //double p_min;

    /// Управление вентилями ЭПТ
    int state_ept;

    /// Озвучка применения стояночного тормоза
    bool pb_brake_play;

    enum
    {
        NUM_COEFFS = 9
    };

    std::array<double, NUM_COEFFS> K;

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
