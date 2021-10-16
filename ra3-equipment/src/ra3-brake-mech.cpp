#include    "ra3-brake-mech.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3BrakeMech::RA3BrakeMech(QObject *parent) : BrakeMech(parent)
  , V_st(2e-3)
  , Q_st(0.0)
  , pPM_max(0.8)
  , num_ea(2)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3BrakeMech::~RA3BrakeMech()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3BrakeMech::preStep(state_vector_t &Y, double t)
{
    // Нажатие от пружинного аккумулятора стояночного тормоза
    double K_st = Kmax * (1 - Y[1] / pPM_max);

    // Нажатие от блок-тормоза без энергоаккумулятора
    double K_b1 = Kmax * Y[0] / p_max;

    // Ограничение тормозного нажатия, учитывающее зазор в механизмах
    // блок тормоза с пружинным энергоаккумулятором
    double K_lim = pf(Kmax - K_st);

    // Нажатие от блок-тормоза с энергоаккумулятором
    double K_b2 = K_st + cut(K_b1, 0.0, K_lim);

    // Тормозное усилие от б/т без энергоаккумулятора
    double shoe_brake_force1 = K_b1 * phi(K_b1, velocity) * Physics::g * 1000.0;

    // Тормозное усилие от б/т с энергоаккумулятором
    double shoe_brake_force2 = K_b2 * phi(K_b2, velocity) * Physics::g * 1000.0;

    // Момент от тормозных сил на колесной паре
    brakeTorque = shoesAxis * (shoe_brake_force1 + shoe_brake_force2) * effRadius;

    is_parking_brake = static_cast<bool>(hs_n(Y[1] - p_max));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3BrakeMech::ode_system(const state_vector_t &Y,
                              state_vector_t &dYdt,
                              double t)
{
    dYdt[1] = Q_st / V_st / num_ea;

    BrakeMech::ode_system(Y, dYdt, t);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3BrakeMech::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "V_st", V_st);
    cfg.getDouble(secName, "pPM_max", pPM_max);
    cfg.getInt(secName, "num_ea", num_ea);

    BrakeMech::load_config(cfg);
}
