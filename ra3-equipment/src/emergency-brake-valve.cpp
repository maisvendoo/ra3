#include    "emergency-brake-valve.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
EmergencyBrakeValve::EmergencyBrakeValve(QObject *parent) : Device(parent)
  , QBP(0.0)
  , pBP(0.0)
  , K_flow(5.0e-2)
  , Kv(4.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
EmergencyBrakeValve::~EmergencyBrakeValve()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::setBPpressure(double value)
{
    pBP = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double EmergencyBrakeValve::getBPflow() const
{
    return QBP;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::setEmergencyBrake(bool is_emergency)
{
    if (is_emergency)
        brake.set();
    else
        brake.reset();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool EmergencyBrakeValve::isEmergencyBrake() const
{
    return brake.getState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    double u = static_cast<double>(brake.getState());

    QBP = - K_flow * pBP * u;

    emit soundSetVolume("EB_vipusk", qRound(nf(QBP) * Kv));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::ode_system(const state_vector_t &Y,
                                     state_vector_t &dYdt,
                                     double t)
{
    Q_UNUSED(t)
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "K_flow", K_flow);
    cfg.getDouble(secName, "Kv", Kv);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::stepKeysControl(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    if (getKeyState(KEY_X))
    {
        if (isShift())
        {
            brake.reset();
        }
        else
        {
            brake.set();
        }
    }
}
