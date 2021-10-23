#ifndef     HYDRO_TRANSMISSION_H
#define     HYDRO_TRANSMISSION_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class HydroTransmission : public Device
{
public:

    HydroTransmission(QObject *parent = Q_NULLPTR);

    ~HydroTransmission();

private:

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // HYDRO_TRANSMISSION_H
