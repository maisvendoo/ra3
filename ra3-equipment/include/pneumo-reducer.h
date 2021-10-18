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

private:

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // PNEUMO_REGUCER_H
