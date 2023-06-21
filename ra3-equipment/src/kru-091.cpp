#include    "kru-091.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
KRU091::KRU091(QObject *parent) : BrakeCrane(parent)
  , handle_pos(POS_RELEASE)
  , min_pos(POS_RELEASE)
  , max_pos(POS_BRAKE)
  , pos_delay(0.3)
  , incTimer(new Timer(pos_delay))
  , decTimer(new Timer(pos_delay))
  , vr(1.0)
  , vb(0.0)
  , reducer(new PneumoReducer(0.5))
  , eq_res_leak(0.0)
  , A(1.0)
{
    Ver = 0.002;

    std::fill(K.begin(), K.end(), 0.0);

    positions_names << "RELEASE" << "  HOLD " << " BRAKE ";

    connect(incTimer, &Timer::process, this, &KRU091::inc_position);
    connect(decTimer, &Timer::process, this, &KRU091::dec_position);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
KRU091::~KRU091()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::step(double t, double dt)
{
    reducer->setRefPressure(p0);
    reducer->setInputPressure(pFL);
    reducer->step(t, dt);

    BrakeCrane::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::setHandlePosition(int &position)
{
    handle_pos = position;
    switch (position)
    {
    case POS_RELEASE:
        vr = 1.0;
        break;

    case POS_BRAKE:
        vb = 1.0;
        break;

    default:
        vr = vb = 0.0;
        break;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString KRU091::getPositionName() const
{
    return positions_names[handle_pos];
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double KRU091::getHandlePosition() const
{
    return static_cast<float>(handle_pos) / 2.0f;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::init(double pBP, double pFL)
{
    Q_UNUSED(pFL)

    setY(ER_PRESSURE, pBP);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(t)

    // Разница давлений в РР и ТМ
    double dp = A * (Y[ER_PRESSURE] - pBP);

    // Расчет проходных сечений клапанов РД
    // Зарядка ТМ
    double Q_charge_bp = cut(dp, 0.0, K[3]) * (pFL - pBP);

    // Разрядка ТМ
    double Q_brake_bp = cut(-dp, 0.0, K[4]) * pBP;

    // Суммарный поток в питательную магистраль
    QFL = -reducer->getInputFlow() - Q_charge_bp;

    // Суммарный поток в тормозную магистраль
    QBP = Q_charge_bp - Q_brake_bp;

    emit soundSetVolume("KRU-091_brake", qRound(2e5 * Q_brake_bp));
    emit soundSetVolume("KRU-091_release", qRound(2e6 * Q_charge_bp));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::ode_system(const state_vector_t &Y,
                        state_vector_t &dYdt,
                        double t)
{
    // Расход воздуха из редуктора в РР
    double Q_charge_er = K[1] * vr * (reducer->getOutPressure() - Y[ER_PRESSURE]);

    // Расход воздуха из РР
    double Q_brake_er = (K[2] * vb + eq_res_leak) * Y[ER_PRESSURE];

    // Задаем расход в РР
    setERflow(Q_charge_er - Q_brake_er);

    // Задаем расход из рабочего объема редуктора
    reducer->setOutFlow(-Q_charge_er);

    BrakeCrane::ode_system(Y, dYdt, t);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    double tmp = 0.0;
    cfg.getDouble(secName, "EqReservoirVolume", tmp);
    if (tmp > 0.0)
        Ver = tmp;

    for (size_t i = 1; i < K.size(); ++i)
    {
        QString coeff = QString("K%1").arg(i);
        cfg.getDouble(secName, coeff, K[i]);
    }

    int delay = 300;

    if (cfg.getInt(secName, "PosDelay", delay))
    {
        pos_delay = static_cast<double>(delay) / 1000.0;
    }

    incTimer->setTimeout(pos_delay);
    decTimer->setTimeout(pos_delay);

    reducer->read_config("pneumo-reducer");

    cfg.getDouble(secName, "EqResLeak", eq_res_leak);

    cfg.getDouble(secName, "A", A);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::stepKeysControl(double t, double dt)
{
    if (getKeyState(KEY_Semicolon))
    {
        if (!decTimer->isStarted())
            decTimer->start();
    }
    else
    {
        decTimer->stop();
    }

    if (getKeyState(KEY_Quote))
    {
        if (!incTimer->isStarted())
            incTimer->start();
    }
    else
    {
        incTimer->stop();
    }

    setHandlePosition(handle_pos);

    incTimer->step(t, dt);
    decTimer->step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::inc_position()
{
    handle_pos++;

    handle_pos = cut(handle_pos, min_pos, max_pos);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::dec_position()
{
    handle_pos--;

    handle_pos = cut(handle_pos, min_pos, max_pos);
}

