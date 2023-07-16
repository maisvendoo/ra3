#include    "generator.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Generator::Generator(QObject *parent) : Device(parent)
  , P_nom(70000.0)
  , U_nom(400.0)
  , I_nom(101)
  , omega_nom(314.2)
  , cF(0.75)
  , r(0.0)
  , J(1.0)
  , pressure(0.0)
  , I(0.0)
  , U(0.0)
  , u(0.0)
  , delta_omega(0.0)
  , Mc(0.0)
  , is_active(false)
{
    std::fill(K.begin(), K.end(), 0.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Generator::~Generator()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Generator::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(t)

    // Расчет линейного напряжения
    U = (cF * Y[0] - r * I) * sqrt(3.0);

    // Ошибка по угловой скорости вращения
    delta_omega = omega_nom - Y[0];

    // Ограничиваем выход с интегратора
    Y[1] = cut(Y[1], -1.0, 1.0);

    u = K[3] * delta_omega + K[4] * Y[1];

    // Ограничиваем управляющее воздействие
    u = cut(u, 0.0, 1.0);

    is_active = static_cast<bool>(hs_p(U - 0.9 * U_nom));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Generator::ode_system(const state_vector_t &Y,
                           state_vector_t &dYdt,
                           double t)
{
    Q_UNUSED(t)

    // Момент на приводном гидромоторе
    double M_hm = K[2] * pressure * u;

    dYdt[0] = (M_hm - cF * I - Physics::fricForce(Mc, Y[0])) / J;

    dYdt[1] = delta_omega;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Generator::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "P_nom", P_nom);
    cfg.getDouble(secName, "omega_nom", omega_nom);
    cfg.getDouble(secName, "U_nom", U_nom);
    cfg.getDouble(secName, "I_nom", I_nom);
    cfg.getDouble(secName, "J", J);
    cfg.getDouble(secName, "Mc", Mc);

    // Условный КПД генератора
    double eta = 0.95;

    r = 0.5 * P_nom * (1 - eta) / 3 / I_nom / I_nom;

    cF = (U_nom / sqrt(3.0) + r * I_nom) / omega_nom;

    for (size_t i = 1; i < K.size(); ++i)
    {
        double tmp = 0;
        cfg.getDouble(secName, QString("K%1").arg(i), tmp);
        K[i] = tmp;
    }
}
