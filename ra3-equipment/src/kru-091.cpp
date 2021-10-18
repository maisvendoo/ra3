#include    "kru-091.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
KRU091::KRU091(QObject *parent) : BrakeCrane(parent)
  , handle_pos(0)
  , min_pos(POS_RELEASE)
  , max_pos(POS_BRAKE)
  , pos_delay(0.3)
  , incTimer(new Timer(pos_delay))
  , decTimer(new Timer(pos_delay))
  , eq_res(new Reservoir(0.002))
  , vr(1.0)
  , vb(0.0)
  , reducer(new PneumoReducer)
{
    std::fill(K.begin(), K.end(), 0.0);

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
    incTimer->step(t, dt);
    decTimer->step(t, dt);

    reducer->setRefPressure(p0);
    reducer->setInputPressure(pFL);
    reducer->step(t, dt);

    eq_res->setFlowCoeff(eq_res_leak);
    eq_res->step(t, dt);

    BrakeCrane::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::setPosition(int &position)
{
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
QString KRU091::getPositionName()
{
    return QString();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float KRU091::getHandlePosition()
{
    return static_cast<float>(handle_pos) / 2.0f;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::preStep(state_vector_t &Y, double t)
{
    // Поток воздуха в РР
    Y[ER_PRESSURE] = eq_res->getPressure();

    // Расход воздуха из редуктора
    double Qr = K[1] * (reducer->getOutPressure() - Y[ER_PRESSURE]);

    // Расход воздуха из РР
    double Qer = Qr * vr - K[2] * Y[ER_PRESSURE] * vb;

    eq_res->setAirFlow(Qer);

    reducer->setQ_out(-Qr * vr);

    DebugMsg = QString(" RD: %1").arg(reducer->getOutPressure(), 4, 'f', 2);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::ode_system(const state_vector_t &Y,
                        state_vector_t &dYdt,
                        double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::load_config(CfgReader &cfg)
{
    QString secName = "Device";

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

    reducer->read_custom_config(custom_config_dir +
                                QDir::separator() +
                                "pneumo-reducer");

    cfg.getDouble(secName, "EqResLeak", eq_res_leak);
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

    setPosition(handle_pos);
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

