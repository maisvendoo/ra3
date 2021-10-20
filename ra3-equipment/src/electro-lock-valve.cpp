#include    "electro-lock-valve.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ElectroLockValve::ElectroLockValve(QObject *parent) : BrakeDevice(parent)
  , U(0.0)
  , state(false)
  , Q_in(0.0)
  , Q_out(0.0)
  , p_in(0.0)
  , p_out(0.0)
  , Q_atm(0.0)
  , K_atm(0.01)
  , volume(new Reservoir(0.001))
  , valve(new Relay(1))
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ElectroLockValve::~ElectroLockValve()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectroLockValve::step(double t, double dt)
{
    volume->step(t, dt);

    valve->step(t, dt);

    BrakeDevice::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectroLockValve::preStep(state_vector_t &Y, double t)
{
    valve->setVoltage(U * static_cast<double>(state));

    double v1 = static_cast<double>(valve->getContactState(0));

    double v2 = 1.0 - v1;

    Q_atm = - K_atm * p_out * v1;

    double Q1 = Q_in * v1;
    volume->setAirFlow(Q1);

    Q_out = Q_in * v2;

    p_in = volume->getPressure() * v1 + p_out * v2;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectroLockValve::ode_system(const state_vector_t &Y,
                                  state_vector_t &dYdt,
                                  double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectroLockValve::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "K_atm", K_atm);

    valve->read_custom_config(custom_config_dir + QDir::separator() + "mk");
    valve->setInitContactState(0, false);
}
