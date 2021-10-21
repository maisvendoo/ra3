#ifndef     TRAC_CONTROLLER_H
#define     TRAC_CONTROLLER_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class TractionController : public Device
{
public:

    TractionController(QObject *parent = Q_NULLPTR);

    ~TractionController();

private:

    int handle_pos;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // TRAC_CONTROLLER_H
