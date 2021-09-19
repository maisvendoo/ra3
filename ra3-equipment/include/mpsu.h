#ifndef     MPSU_H
#define     MPSU_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MPSU : public Device
{
public:

    MPSU(QObject *parent = Q_NULLPTR);

    ~MPSU();

private:

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // MPSU_H
