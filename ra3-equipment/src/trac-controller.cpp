#include    "trac-controller.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TracController::TracController(QObject *parent) : Device(parent)
  , mode_pos(0)
  , mode_pos_old(mode_pos)
  , old_traction_key(false)
  , old_brake_key(false)
  , fwd_key(false)
  , old_fwd_key(false)
  , bwd_key(false)
  , old_bwd_key(false)
  , revers_pos(0)
  , trac_min(17)
  , brake_min(26)
  , trac_level(0)
  , brake_level(0)
  , handle_pos(0.0)
  , omega_handle(0.5)
  , dir(0)
  , brakeTimer(new Timer)
  , tracTimer(new Timer)
  , mainHandleSoundName("KM_main")
  , reversSoundName("KM_revers")
  , K_flow(5.0e-2)
  , pBP(0.0)
  , QBP(0.0)
{
    connect(brakeTimer, &Timer::process, this, &TracController::slotBrakeLevelProcess);
    connect(tracTimer, &Timer::process, this, &TracController::slotTracLevelProcess);

    emerg_brake.setOnSoundName("KM_main");
    emerg_brake.setOffSoundName("KM_main");
    connect(&emerg_brake, &Trigger::soundPlay, this, &TracController::soundPlay);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TracController::~TracController()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::setBPpressure(double value)
{
    pBP = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double TracController::getBPflow() const
{
    return QBP;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool TracController::isEmergencyBrake() const
{
    return emerg_brake.getState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float TracController::getHandlePosition() const
{
    double level = mode_pos * 100 + trac_level - brake_level - 300 * static_cast<int>(emerg_brake.getState());

    return static_cast<float>(level) / 500.0f;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    if (mode_pos != mode_pos_old)
    {
        emit soundPlay(mainHandleSoundName);
        mode_pos_old = mode_pos;
    }

    double u = static_cast<double>(emerg_brake.getState());

    QBP = - K_flow * pBP * u;

    emit soundSetVolume("KM_vipusk", qRound(10.0 * nf(QBP)));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{
    Q_UNUSED(t)
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getInt(secName, "trac_min", trac_min);
    cfg.getInt(secName, "brake_min", brake_min);
    cfg.getDouble(secName, "omega_handle", omega_handle);

    cfg.getDouble(secName, "K_flow", K_flow);

    brakeTimer->setTimeout(0.02);
    tracTimer->setTimeout(0.02);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::stepKeysControl(double t, double dt)
{
    processDiscretePositions(getKeyState(KEY_A), old_traction_key, 1);
    processDiscretePositions(getKeyState(KEY_D), old_brake_key, -1);

    if (mode_pos == -1)
    {
        traction.reset();
        dir = 0;

        if (!brakeTimer->isStarted())
            brakeTimer->start();

        if (getKeyState(KEY_A))
        {
            if (brake_level == 0)
            {
                mode_pos = 0;
                brakeTimer->stop();
                brake.reset();
            }
            else
            {
                dir = 1;
            }

            if (emerg_brake.getState())
            {
                if (!old_traction_key)
                    emerg_brake.reset();
            }
        }

        if (getKeyState(KEY_D))
        {
            if (brake.getState())
                dir = -1;

            if (brake_level == 90)
            {
                if (!old_brake_key)
                    emerg_brake.set();
            }
        }
        else
        {
            brake.set();
        }
    }

    brakeTimer->step(t, dt);

    if (mode_pos == 1)
    {
        brake.reset();
        dir = 0;

        if (!tracTimer->isStarted())
            tracTimer->start();

        if (getKeyState(KEY_D))
        {
            if (trac_level == 0)
            {
                mode_pos = 0;
                tracTimer->stop();
                traction.reset();
            }
            else
            {
                dir = -1;
            }
        }

        if (getKeyState(KEY_A))
        {
            if (traction.getState())
                dir = 1;

        }
        else
        {
            traction.set();
        }
    }

    tracTimer->step(t, dt);

    old_traction_key = getKeyState(KEY_A);
    old_brake_key = getKeyState(KEY_D);

    if (fwd_key && !old_fwd_key && (revers_pos < 1))
    {
        revers_pos++;
        emit soundPlay(reversSoundName);
    }

    if (bwd_key && !old_bwd_key && (revers_pos > -1))
    {
        revers_pos--;
        emit soundPlay(reversSoundName);
    }

    old_fwd_key = fwd_key;
    old_bwd_key = bwd_key;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::processDiscretePositions(bool key_state, bool old_key_state, int dir)
{
    if (mode_pos != 0)
        return;

    trac_level = brake_level = 0;
    traction.reset();
    brake.reset();

    if ( (key_state) && (!old_key_state) )
    {
        mode_pos += dir;
        mode_pos = cut(mode_pos, -1, 1);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::slotTracLevelProcess()
{
    trac_level += dir * mode_pos;

    trac_level = cut(trac_level, 0, 100 - trac_min);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::slotBrakeLevelProcess()
{
    brake_level += dir * mode_pos;

    brake_level = cut(brake_level, 0, 100 - brake_min);
}
