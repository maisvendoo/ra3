#ifndef     ELECTRO_LOCK_VALVE_H
#define     ELECTRO_LOCK_VALVE_H

#include    "device.h"
#include    "reservoir.h"
#include    "relay.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ElectroLockValve : public BrakeDevice
{
public:

    ElectroLockValve(QObject *parent = Q_NULLPTR);

    ~ElectroLockValve();

    void step(double t, double dt) override;

    void setVoltage(double U) { this->U = U; }

    void setState(bool state) { this->state = state; }

    void setQ_in(double Q_in) { this->Q_in = Q_in; }

    double getQ_out() const { return Q_out; }

    void setP_out(double p_out) { this->p_out = p_out; }

    double getP_in() const { return p_in; }

    double getQ_atm() const { return Q_atm; }

private:

    double U;

    bool state;

    double Q_in;

    double Q_out;

    double p_in;

    double p_out;

    double Q_atm;

    double K_atm;

    /// Резервуар, запирающий управляющее давление
    Reservoir *volume;

    /// Электромагнитный вентиль
    Relay   *valve;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // ELECTRO_LOCK_VALVE_H
