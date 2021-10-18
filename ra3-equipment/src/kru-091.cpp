#include    "kru-091.h"

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

    BrakeCrane::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void KRU091::setPosition(int &position)
{

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

