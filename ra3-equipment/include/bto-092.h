#ifndef     BTO_092_H
#define     BTO_092_H

#include    "airdistributor.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class BTO092 : public AirDistributor
{
public:

    BTO092(QObject *parent = Q_NULLPTR);

    ~BTO092();



private:

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // BTO092_H
