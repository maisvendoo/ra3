#ifndef     PNEUMO_REGUCER_H
#define     PNEUMO_REGUCER_H

#include    "brake-device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class PneumoReducer : public BrakeDevice
{
public:

    PneumoReducer(QObject *parent = Q_NULLPTR);

    ~PneumoReducer();

    void setRefPressure(double p_ref) { this->p_ref = p_ref; }

    void setQ_out(double Q_out) { this->Q_out = Q_out; }

    void setInputPressure(double p_in) { this->p_in = p_in; }

    double getOutPressure() const { return getY(0); }

private:

    /// Уставка давления на выходе редуктора
    double p_ref;

    /// Объем рабочей полости на выходе
    double V_work;

    /// Давление на входе редуктора
    double p_in;

    /// Расход из рабочей полости редуктора
    double Q_out;

    /// Расход в рабочую полость
    double Q_in;

    enum
    {
        NUM_COEFFS = 10
    };

    std::array<double, NUM_COEFFS> K;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // PNEUMO_REGUCER_H
