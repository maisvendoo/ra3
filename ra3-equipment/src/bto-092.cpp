#include    "bto-092.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BTO092::BTO092(QObject *parent) : AirDistributor(parent)
  , p_pb(0.0)
  , Q_pb(0.0)
  , is_parking_brake_ON(false)
  , pPB_max(0.4)
  , U_pow(0.0)
  , U_nom(110.0)
{
    std::fill(K.begin(), K.end(), 0.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BTO092::~BTO092()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool BTO092::isParkingBraked()
{
    return  parking_brake.getState(p_pb);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::preStep(state_vector_t &Y, double t)
{
    // Проверка питания
    bool is_powered = static_cast<bool>(hs_p(U_pow - 0.9 * U_nom));

    // Признак активации наполнения ЦСТ
    bool is_release = is_powered && (!is_parking_brake_ON);

    // Состояние вентилей В1 (зажатие) В2 (отпуск) СТ
    double v2 = static_cast<double>(is_release);
    double v1 = 1.0 - v2;

    Q_pb = K[2] * (pAS - p_pb) * v2 * hs_n(p_pb - pPB_max) -
           K[1] * p_pb * v1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::ode_system(const state_vector_t &Y,
                        state_vector_t &dYdt,
                        double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    for (size_t i = 1; i < K.size(); ++i)
    {
        QString coeff = QString("K%1").arg(i);
        cfg.getDouble(secName, coeff, K[i]);
    }

    cfg.getDouble(secName, "pPB_max", pPB_max);

    parking_brake.setRange(0.125 * pPB_max, 0.975 * pPB_max);

    cfg.getDouble(secName, "U_nom", U_nom);
}

