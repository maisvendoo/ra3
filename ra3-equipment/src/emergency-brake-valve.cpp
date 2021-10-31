#include    "emergency-brake-valve.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
EmergencyBrakeValve::EmergencyBrakeValve(QObject *parent) : Device(parent)
  , emergencyRate(0.0)
  , pTM(0.0)
  , K_flow(50.0)
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
void EmergencyBrakeValve::preStep(state_vector_t &Y, double t)
{
    double u = static_cast<double>(brake.getState());

    emergencyRate = K_flow * pTM * u;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::ode_system(const state_vector_t &Y,
                                     state_vector_t &dYdt,
                                     double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "K_flow", K_flow);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EmergencyBrakeValve::stepKeysControl(double t, double dt)
{
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
