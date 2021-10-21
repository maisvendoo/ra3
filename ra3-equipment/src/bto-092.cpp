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
  , is_release(false)
  , keb(new ElectroLockValve)
  , release_valve(new Relay(1))
  , brake_valve(new Relay(1))
  , p_ref(0.0)
  , ept_eps(0.01)
  , p_min(0.1)
  , state_ept(0)
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

    keb->step(t, dt);

    release_valve->step(t, dt);

    brake_valve->step(t, dt);

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

    // Состояние вентилей ЭПТ
    pressureRegulatorEPT(p_ref, keb->getP_in());

    double vr = qAbs(state_ept);
    double vb = pf(state_ept);

    release_valve->setVoltage(U_pow * vr);
    brake_valve->setVoltage(U_pow * vb);

    // Расход воздуха в ПК при работе ЭПТ
    double p2 = sw_valve->getPressure2();

    double ub = static_cast<double>(brake_valve->getContactState(0));
    double ur = static_cast<double>(release_valve->getContactState(0));

    double Qpk2 = K[8] * (pAS - p2) * ub - K[9] * p2 * ur;

    // Переключательный клапан (ПК)
    sw_valve->setInputFlow1(Qpk1); // Пневматическое торможение от КПУ
    sw_valve->setInputFlow2(Qpk2); // Электропневматическое торможение (ЭПТ)
    sw_valve->setOutputPressure(keb->getP_in());

    // КЭБ
    keb->setVoltage(U_pow);
    keb->setState(is_release);
    keb->setQ_in(sw_valve->getOutputFlow());
    keb->setP_out(bc_relay->getWorkPressure());

    // Реле давления
    bc_relay->setWorkAirFlow(keb->getQ_out());
    bc_relay->setBrakeCylPressure(pBC);
    bc_relay->setPipelinePressure(pAS);

    Qbc = bc_relay->getBrakeCylAirFlow();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::pressureRegulatorEPT(double p_ref, double p)
{
    double dp = p_ref - p;

    if (qAbs(dp) < ept_eps / 2.0)
        state_ept = -1;

    if (dp >= ept_eps / 2.0)
        state_ept = 1;

    if (dp <= -ept_eps / 2.0)
        state_ept = 0;
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

    keb->setCustomConfigDir(custom_config_dir);
    keb->read_custom_config(custom_config_dir + QDir::separator() + "keb");

    release_valve->read_custom_config(custom_config_dir +
                                      QDir::separator() +
                                      "ept_valve");

    release_valve->setInitContactState(0, true);

    brake_valve->read_custom_config(custom_config_dir +
                                    QDir::separator() +
                                    "ept_valve");

    brake_valve->setInitContactState(0, false);

    cfg.getDouble(secName, "ept_eps", ept_eps);
    cfg.getDouble(secName, "p_min", p_min);
}

