#ifndef     GENERATOR_H
#define     GENERATOR_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Generator : public Device
{
public:

    Generator(QObject *parent = Q_NULLPTR);

    ~Generator();

private:

    double P_nom;

    double U_nom;

    double I_nom;

    double omega_nom;

    double cF;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // GENERATOR_H
