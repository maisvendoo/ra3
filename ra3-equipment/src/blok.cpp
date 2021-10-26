#include    "blok.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BLOK::BLOK(QObject *parent) : Device(parent)
  , code_alsn(1)
  , old_code_alsn(1)
  , state_RB(false)
  , state_RBS(false)
  , state_EPK(false)
  , v_kmh(0.0)
  , key_epk(false)
  , is_dislplay_ON(false)
  , safety_timer(new Timer(45.0, false))
{
    epk_state.reset();

    connect(safety_timer, &Timer::process, this, &BLOK::onSafetyTimer);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BLOK::~BLOK()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::step(double t, double dt)
{
    safety_timer->step(t, dt);
    Device::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::preStep(state_vector_t &Y, double t)
{
    // Очищаем состояние ламп
    std::fill(lamps.begin(), lamps.end(), 0.0f);

    // Ничего не делаем при выключенном питании
    if (hs_n(U_pow - 100.0))
    {
        is_dislplay_ON = false;
        return;
    }

    is_dislplay_ON = true;

    // Ничего не делаем при выключенном ЭПК
    if (!key_epk)
    {
        epk_state.reset();
        return;
    }

    if (code_alsn < old_code_alsn)
        epk_state.reset();

    alsn_process(code_alsn);

    if (code_alsn == 1)
    {
        if (v_kmh > 60.0)
        {
            epk_state.reset();
            return;
        }

        if ( (!safety_timer->isStarted()) && (v_kmh > 5) )
        {
            safety_timer->start();
        }
        else
        {
            safety_timer->stop();
        }
    }

    if (code_alsn == 2)
    {
        if (v_kmh > 60.0)
        {
            if (!safety_timer->isStarted())
                safety_timer->start();
        }
        else
        {
            safety_timer->stop();
        }
    }

    if (state_RB || state_RBS)
    {
        epk_state.set();
        safety_timer->stop();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::ode_system(const state_vector_t &Y,
                      state_vector_t &dYdt,
                      double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    double safety_check_interval = 45.0;

    cfg.getDouble(secName, "SafetyCheckInterval", safety_check_interval);

    safety_timer->setTimeout(safety_check_interval);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::alsn_process(int code_alsn)
{
    switch (code_alsn)
    {
    case 0:
        {
            lamps[WHITE_LAMP] = 1.0f;

            break;
        }
    case 1:
        {
            lamps[RED_YELLOW_LAMP] = 1.0f;

            break;
        }

    case 2:
        {
            lamps[YELLOW_LAMP] = 1.0f;

            break;
        }

    case 3:
        {
            lamps[GREEN_LAMP1] = 1.0f;

            break;
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BLOK::onSafetyTimer()
{
    epk_state.reset();
}
