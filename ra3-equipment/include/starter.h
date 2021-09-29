#ifndef     STARTER_H
#define     STARTER_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Starter : public Device
{
public:

    Starter(QObject *parent = Q_NULLPTR);

    ~Starter();

private:

    /// Номинальная механическая мощность
    double P_nom;

    /// Номинальная частота вращения
    double omega_nom;

    /// Номинальное напряжение питания
    double U_nom;

    /// Номинальный ток
    double I_nom;

    /// Ток якоря
    double I;

    /// Постоянная намагничивания
    double cPhi;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // STARTER_H
