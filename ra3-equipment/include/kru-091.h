#ifndef     KRU091_H
#define     KRU091_H

#include    "brake-crane.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class KRU091 : public BrakeCrane
{
public:

    KRU091(QObject *parent = Q_NULLPTR);

    ~KRU091();

private:

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // KRU091_H
