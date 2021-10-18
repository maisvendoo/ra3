#include    "pneumo-reducer.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PneumoReducer::PneumoReducer(QObject *parent) : BrakeDevice(parent)
  , p_ref(0.5)
  , V_work(0.001)
  , p_in(0.0)
  , Q_out(0.0)
  , Q_in(0.0)
{
    std::fill(K.begin(), K.end(), 0.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PneumoReducer::~PneumoReducer()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoReducer::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(t)

    double v = cut(nf(K[2]*(Y[0] - p_ref)), 0.0, 1.0);

    Q_in = K[1] * (p_in - Y[0]) * v;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoReducer::ode_system(const state_vector_t &Y,
                               state_vector_t &dYdt,
                               double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    dYdt[0] = (Q_in + Q_out) / V_work;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoReducer::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    for (size_t i = 1; i < K.size(); ++i)
    {
        QString coeff = QString("K%1").arg(i);
        cfg.getDouble(secName, coeff, K[i]);
    }
}
