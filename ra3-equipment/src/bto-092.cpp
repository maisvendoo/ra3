#include    "bto-092.h"

#include    <QDir>

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
  , sw_valve(new SwitchingValve)
  , bc_reducer(new PneumoReducer)
  , bc_relay(new PneumoReley)
  , pBC_max(0.4)
  , A(0.5)
  , ps(0.5)
  , work_res(new Reservoir(0.001))
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
void BTO092::step(double t, double dt)
{
    sw_valve->step(t, dt);

    bc_reducer->step(t, dt);

    bc_relay->step(t, dt);

    work_res->step(t, dt);

    AirDistributor::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::stepParkingBrake()
{
    // Проверка питания
    bool is_powered = static_cast<bool>(hs_p(U_pow - 0.9 * U_nom));

    // Признак активации наполнения ЦСТ
    bool is_release = is_powered && (!is_parking_brake_ON);

    // Состояние вентилей В1 (зажатие) В2 (отпуск) СТ
    double v2 = static_cast<double>(is_release);
    double v1 = 1.0 - v2;

    // Расход воздуха в цилиндры СТ
    Q_pb = K[2] * (pAS - p_pb) * v2 * hs_n(p_pb - pPB_max) -
            K[1] * p_pb * v1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::stepPneumoBrake()
{
    double Qwr = K[7] * (bc_reducer->getOutPressure() - work_res->getPressure());

    work_res->setAirFlow(Qwr);

    bc_reducer->setRefPressure(pBC_max);
    bc_reducer->setInputPressure(pAS);
    bc_reducer->setQ_out(-Qwr);

    // Разность давлений на чувствительном органе КПУ
    double dp = pTM + A * pBC - ps;

    // Клапан выпуска из ТЦ
    double v1 = cut(pf(K[3] * dp), 0.0, 1.0);

    // Клапан наполнения ТЦ
    double v2 = cut(nf(K[5] * dp), 0.0, 1.0);

    // Расход на наполнение ПК от КПУ
    double p1 = sw_valve->getPressure1();

    double Qpk1 = K[6] * (bc_reducer->getOutPressure() - p1) * v2 -
                 K[4] * p1 * v1;

    sw_valve->setInputFlow1(Qpk1);
    sw_valve->setInputFlow2(0.0);
    sw_valve->setOutputPressure(bc_relay->getWorkPressure());

    bc_relay->setWorkAirFlow(sw_valve->getOutputFlow());
    bc_relay->setBrakeCylPressure(pBC);
    bc_relay->setPipelinePressure(pAS);

    Qbc = bc_relay->getBrakeCylAirFlow();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::preStep(state_vector_t &Y, double t)
{
    stepParkingBrake();

    stepPneumoBrake();
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

    cfg.getDouble(secName, "pBC_max", pBC_max);
    cfg.getDouble(secName, "A", A);
    cfg.getDouble(secName, "ps", ps);

    sw_valve->read_config("zpk");
    bc_relay->read_config("rd304");
    bc_reducer->read_custom_config(custom_config_dir +
                                   QDir::separator() +
                                   "pneumo-reducer");
}

