#include    "starter.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Starter::Starter(QObject *parent) : Device(parent)
  , P_nom(1440.0)
  , omega_nom(48.0)
  , U_nom(110.0)
  , I_nom(62.5)
  , I(0.0)
  , cPhi(0.0)
  , Ra(0.1)
  , omega(0.0)
  , U(0.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Starter::~Starter()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double Starter::getTorque() const
{
    return cPhi * I;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
sound_state_t Starter::getSoundState(size_t idx) const
{
    (void) idx;
    return sound_state_t(U > 0.9 * U_nom);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float Starter::getSoundSignal(size_t idx) const
{
    (void) idx;
    return sound_state_t::createSoundSignal(U > 0.9 * U_nom);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Starter::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    double Rp = 0.014 * hs_n(omega - 50.0) + 0.016;

    I = (U - cPhi * omega) / (Ra + Rp);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Starter::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Starter::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "P_nom", P_nom);
    cfg.getDouble(secName, "omega_nom", omega_nom);
    cfg.getDouble(secName, "U_nom", U_nom);
    cfg.getDouble(secName, "I_nom", I_nom);

    double eta = P_nom / U_nom / I_nom;
    Ra = 0.5 * P_nom * (1 - eta) / I_nom / I_nom;
    cPhi = (U_nom - Ra * I_nom) / omega_nom;
}
