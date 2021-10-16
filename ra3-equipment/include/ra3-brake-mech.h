#ifndef     RA3_BRAKE_MECH_H
#define     RA3_BRAKE_MECH_H

#include    "brake-mech.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3BrakeMech : public BrakeMech
{
public:

    RA3BrakeMech(QObject *parent = Q_NULLPTR);

    ~RA3BrakeMech();

    void setParkingBrakeAirFlow(double Q_st) { this->Q_st = Q_st; }

private:

    /// Объем камеры стояночного тормоза
    double V_st;

    /// Общий расход в камеры стояночного токмоза
    double Q_st;

    /// Максимальное давление в питательной магистрали
    double pPM_max;

    /// Общее число пружинных энергоаккумуляторов
    int num_ea;

    void preStep(state_vector_t &Y, double t) override;

    virtual void ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // RA3_BRAKE_MECH_H
