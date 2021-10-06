#ifndef     HYDRO_PUMP_H
#define     HYDRO_PUMP_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class HydroPump : public Device
{
public:

    HydroPump(QObject *parent = Q_NULLPTR);

    ~HydroPump();

    void setDiselOmega(double omega) { this->omega = omega; }

    double getPressure() const { return getY(0); }

private:

    double K_press;

    double T;

    double omega;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

};

#endif // HYDRO_PUMP_H
