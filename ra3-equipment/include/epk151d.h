//------------------------------------------------------------------------------
//
//      Электро-пневматический клапан автостопа (ЭПК) усл. №150
//      (c) maisvendoo, 06/05/2019
//
//------------------------------------------------------------------------------

#ifndef     EPK151D_H
#define     EPK151D_H

#include    "automatic-train-stop.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    MAX_FLOW_COEFFS = 10,
    MAX_GIAN_COEFFS = 10
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class AutoTrainStopEPK151D : public AutoTrainStop
{
public:

    AutoTrainStopEPK151D(QObject *parent = Q_NULLPTR);

    ~AutoTrainStopEPK151D();

    double getEmergencyBrakeRate() const;

    void init(double pTM, double pFL);

    bool isTractionAllowed() const { return is_powered; }

    void setKeyState(bool key_state) { keyOn(key_state); }

private:

    /// Постоянная времени срабатывание электромеханической части (катушки)
    double T1;

    /// Усилие от диафрагмы плунжера
    double pd;

    /// Усилие, развиваемое электромагнитом катушки
    double pk;

    /// Усилие от ключа
    double p_key;

    /// Усилие пружины срывного клапана
    double ps1;

    /// Усилие от пружины мембраны камеры выдежки времени
    double ps2;

    /// Объем камеры над срывным клапаном
    double V1;

    /// Объем камеры выдержки времени
    double V2;

    /// Темп разрядки ТМ через срывной клапан
    double emergencyRate;

    /// Флаг работы свистка
    double is_whistle_on;

    bool is_whistle;

    std::array<double, MAX_FLOW_COEFFS> K;

    std::array<double, MAX_GIAN_COEFFS> k;

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void preStep(state_vector_t &Y, double t);

    void load_config(CfgReader &cfg);

    void stepKeysControl(double t, double dt);
};

#endif // EPK151D_H
