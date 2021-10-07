#include    "motor-compressor.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MotorCompressor::MotorCompressor(QObject *parent) : Device(parent)
  , P_nom(6000.0)
  , omega_nom(151.3)
  , zp(4)
  , freq(50.0)
  , lambda(2.5)
  , p(0.0)
  , Q(0.0)
  , p0(1.0)
  , Mmax(455.8)
  , s_kr(0.154)
  , Un(380.0)
  , U_power(0.0)
  , omega0(157.08)
  , J(0.5)
  , Mc(50.0)
  , Vnk(0.05)

{
    std::fill(K.begin(), K.end(), 0);    
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MotorCompressor::~MotorCompressor()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MotorCompressor::setExternalPressure(double press)
{
    p = press;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double MotorCompressor::getAirFlow() const
{
    return Q;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MotorCompressor::setU_power(double value)
{
    U_power = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MotorCompressor::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(t)

    Q = K[4] * pf(Y[1] - p);

    emit soundSetPitch("Motor_Compressor", static_cast<float>(Y[0] / omega0));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MotorCompressor::ode_system(const state_vector_t &Y,
                                 state_vector_t &dYdt,
                                 double t)
{
    Q_UNUSED(t)

    // Расчитывает текущее скольжение ротора
    double s = 1 - Y[0] / omega0;

    // Рачитываем максимальный момент при данном напряжении питания
    double M_maximal = Mmax * pow(U_power / Un, 2.0);

    // Расчитываем электромагнитный момент (формула Клосса)
    double Ma = 2 * M_maximal / ( s / s_kr + s_kr / s );

    double Mr = Physics::fricForce(Mc, Y[0]);

    double Qnk =  K[1] * Y[0] - K[2] * Y[1] - K[3] * pf(Y[1] - p);

    dYdt[0] = (Ma - Mr) / J;

    dYdt[1] = Qnk / Vnk;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MotorCompressor::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    for (size_t i = 1; i < K.size(); ++i)
    {
        QString coeff = QString("K%1").arg(i);
        cfg.getDouble(secName, coeff, K[i]);
    }

    cfg.getDouble(secName, "P_nom", P_nom);
    cfg.getDouble(secName, "omega_nom", omega_nom);
    cfg.getInt(secName, "zp", zp);
    cfg.getDouble(secName, "U_nom", Un);
    cfg.getDouble(secName, "freq", freq);
    cfg.getDouble(secName, "lambda", lambda);
    cfg.getDouble(secName, "Mc", Mc);
    cfg.getDouble(secName, "J", J);

    omega0 = 2.0 * Physics::PI * freq / zp;
    double sn = 1 - omega_nom / omega0;
    s_kr = sn * (lambda + sqrt( lambda * lambda - 1 ) );

    Mmax = P_nom * lambda / omega_nom;
}


