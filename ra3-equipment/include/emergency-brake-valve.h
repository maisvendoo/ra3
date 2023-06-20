#ifndef     EMERGENCY_BRAKE_VALVE_H
#define     EMERGENCY_BRAKE_VALVE_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class EmergencyBrakeValve : public Device
{
public:

    EmergencyBrakeValve(QObject *parent = Q_NULLPTR);

    ~EmergencyBrakeValve();

    /// Задать давление от тормозной магистрали
    void setBPpressure(double value);

    /// Поток в тормозную магистраль
    double getBPflow() const;

    /// Задать состояние экстренного торможения
    void setEmergencyBrake(bool is_emergency);

    /// Экстренное торможение
    bool isEmergencyBrake() const;

private:

    double QBP;

    double pBP;

    double K_flow;

    double Kv;

    Trigger brake;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // EMERGENCY_BRAKE_VALVE_H
