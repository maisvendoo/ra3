#include    "bto-092.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BTO092::BTO092(QObject *parent) : AirDistributor(parent)
  , pPB(0.0)
  , QPB(0.0)
  , pPB_max(0.4)
  , ref_parking_brake_state(false)
  , parking_brake_state(new Hysteresis(0.125 * pPB_max, 0.975 * pPB_max, false))
  , U_pow(0.0)
  , U_nom(110.0)
  , pBC_max(0.4)
  , bc_reducer(new PneumoReducer(pBC_max))
  , sw_valve(new SwitchingValve())
  , bc_relay1(new PneumoRelay())
  , bc_relay2(new PneumoRelay())
  , A(0.5)
  , ps(0.5)
  , is_release(false)
//  , keb(new ElectroLockValve())
  , release_valve(new Relay(1))
  , brake_valve(new Relay(1))
  , p_ref(0.0)
  , ept_eps(0.01)
  //, p_min(0.1)
  , state_ept(0)
  , pb_brake_play(false)
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
void BTO092::setPowerVoltage(double value)
{
    U_pow = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::setBCpressure1(double value)
{
    pBC_motor = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double BTO092::getBCflow1() const
{
    return QBC_motor;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::setBCpressure2(double value)
{
    pBC = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double BTO092::getBCflow2() const
{
    return QBC;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::setPBpressure(double value)
{
    pPB = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double BTO092::getPBflow() const
{
    return QPB;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::setParkingBrakeState(bool is_parking_braked)
{
    ref_parking_brake_state = is_parking_braked;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool BTO092::isParkingBraked()
{
    return !parking_brake_state->getState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::releaseBrakes(bool release)
{
    is_release = release;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::setRefEPBlevel(double ref_level)
{
    p_ref = ref_level * pBC_max;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double BTO092::getMaxBCpressure() const
{
    return pBC_max;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::step(double t, double dt)
{
    parking_brake_state->setValue(pPB);

    sw_valve->step(t, dt);

    bc_reducer->setInputPressure(pSR);
    bc_reducer->step(t, dt);

    bc_relay1->step(t, dt);

    bc_relay2->step(t, dt);
/*
    keb->step(t, dt);
*/
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
    double is_powered = hs_p(U_pow - 0.9 * U_nom);

    // Признак активации наполнения ЦСТ
    double is_release = is_powered * static_cast<double>(!ref_parking_brake_state);

    // Состояние вентилей В1 (зажатие) В2 (отпуск) СТ
    double v2 = is_release * hs_n(pPB - pPB_max);
    double v1 = (1.0 - is_release);

    // Расход воздуха в ЦСТ из запасного резервуара
    double Q_fl_pb = v2 * K[1] * (pSR - pPB);

    // Расход воздуха в ЦСТ и разрядка из ЦСТ в атмосферу
    QPB = Q_fl_pb - v1 * K[2] * pPB;

    // Начинаем считать поток в запасный резервуар
    QSR = -Q_fl_pb;

    // Озвучка применения стояночного тормоза (выхода воздуха из ЦСТ)
    if (static_cast<bool>(v1))
    {
        if (!pb_brake_play)
        {
            emit soundPlay("PB_brake");
            pb_brake_play = true;
        }
    }
    else
    {
        pb_brake_play = false;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BTO092::stepPneumoBrake()
{
    // Работа клапана пропорционального уравнения (пневматического торможения)
    // Разность давлений на чувствительном органе КПУ
    double p1 = sw_valve->getPressure1();
    double dp = pBP + A * p1 - ps;

    // Клапан выпуска из ТЦ
    double v1 = cut(K[3] * dp, 0.0, K[4]);

    // Клапан наполнения ТЦ
    double v2 = cut(-K[5] * dp, 0.0, K[6]);

    // Расход на наполнение переключательного клапана от КПУ
    double Q_fl_pk1 = v2 * (bc_reducer->getOutPressure() - p1);
    double Q_pk1_atm = v1 * p1;

    // Работа электропневматического торможения
    // Состояние вентилей ЭПТ
    double p2 = sw_valve->getPressure2();
    pressureRegulatorEPT(p_ref, p2);

    double vr = qAbs(state_ept);
    double vb = pf(state_ept);

    release_valve->setVoltage(U_pow * vr);
    brake_valve->setVoltage(U_pow * vb);

    double ub = K[7] * static_cast<double>(brake_valve->getContactState(0));
    double ur = K[8] * static_cast<double>(release_valve->getContactState(0));

    // Расход на наполнение переключательного клапана от работы ЭПТ
    double Q_fl_pk2 = ub * (bc_reducer->getOutPressure() - p2);
    double Q_pk2_atm = ur * p2;

    // Переключательный клапан (ПК)
    // Пневматическое торможение от КПУ
    sw_valve->setInputFlow1(Q_fl_pk1 - Q_pk1_atm);
    // Электропневматическое торможение (ЭПТ)
    sw_valve->setInputFlow2(Q_fl_pk2 - Q_pk2_atm);
    // Выход к реле давления наполнения ТЦ через КЭБ
    sw_valve->setOutputPressure(bc_relay2->getControlPressure());
/*
    // КЭБ
    keb->setVoltage(U_pow);
    keb->setState(is_release);
    keb->setQ_in(sw_valve->getOutputFlow());
    keb->setP_out(bc_relay->getControlPressure());
*/
    // Реле давления задней (безмоторной) тележки
    // управляет тормозами напрямую
    bc_relay2->setControlFlow(sw_valve->getOutputFlow());
    bc_relay2->setPipePressure(pBC);
    bc_relay2->setFLpressure(bc_reducer->getOutPressure());

    // Реле давления передней (моторной) тележки
    // управляет тормозами при отключенном электроблокировочном клапане (КЭБ)
    double is_keb = hs_p(U_pow - 0.9 * U_nom) * static_cast<double>(is_release);
    bc_relay1->setControlPressure((1 - is_keb) * bc_relay2->getControlPressure());
    bc_relay1->setPipePressure(pBC_motor);
    bc_relay1->setFLpressure(bc_reducer->getOutPressure());

    // Поток в тормозные цилиндры задней (безмоторной) тележки
    QBC = bc_relay2->getPipeFlow();

    // Поток в тормозные цилиндры передней (моторной) тележки
    QBC_motor = bc_relay1->getPipeFlow();

    // Поток на выходе из редуктора
    bc_reducer->setOutFlow(- Q_fl_pk1 - Q_fl_pk2
                           + bc_relay1->getFLflow()
                           + bc_relay2->getFLflow());

    // Добавляем расход в редуктор к потоку в запасный резервуар
    QSR += bc_reducer->getInputFlow();
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
    Q_UNUSED(Y)
    Q_UNUSED(t)

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
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
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
    parking_brake_state->setRange(0.125 * pPB_max, 0.975 * pPB_max);

    cfg.getDouble(secName, "U_nom", U_nom);

    cfg.getDouble(secName, "pBC_max", pBC_max);

    cfg.getDouble(secName, "A", A);
    cfg.getDouble(secName, "ps", ps);

    sw_valve->read_config("zpk");
    bc_relay1->read_config("rd304");
    bc_relay2->read_config("rd304");
    bc_reducer->read_config("pneumo-reducer");
    bc_reducer->setRefPressure(pBC_max);
/*
    keb->setCustomConfigDir(custom_config_dir);
    keb->read_custom_config(custom_config_dir + QDir::separator() + "keb");
*/
    release_valve->read_custom_config(custom_config_dir +
                                      QDir::separator() +
                                      "ept_valve");

    release_valve->setInitContactState(0, true);

    brake_valve->read_custom_config(custom_config_dir +
                                    QDir::separator() +
                                    "ept_valve");

    brake_valve->setInitContactState(0, false);

    cfg.getDouble(secName, "ept_eps", ept_eps);
    //cfg.getDouble(secName, "p_min", p_min);
}
