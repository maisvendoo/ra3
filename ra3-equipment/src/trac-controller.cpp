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
  , K_flow(5.0e-2)
  , pBP(0.0)
  , QBP(0.0)
{
    connect(brakeTimer, &Timer::process, this, &TracController::slotBrakeLevelProcess);
    connect(tracTimer, &Timer::process, this, &TracController::slotTracLevelProcess);
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
    return mode_pos == -2;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool TracController::isBrake() const
{
    return mode_pos == -1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool TracController::isZero() const
{
    return mode_pos == 0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool TracController::isTraction() const
{
    return mode_pos == 1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float TracController::getHandlePosition() const
{
    float level = static_cast<float>(mode_pos * 10 + trac_level - brake_level);

    return level / 100.0f;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
sound_state_t TracController::getSoundState(size_t idx) const
{
    if (idx < sounds.size())
        return sounds[idx];
    return Device::getSoundState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float TracController::getSoundSignal(size_t idx) const
{
    if (idx < sounds.size())
        return sounds[idx].createSoundSignal();
    return Device::getSoundSignal();
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
        sounds[MAIN_CHANGE_MODE_SOUND].play();
        mode_pos_old = mode_pos;
    }

    double u = static_cast<double>(mode_pos == -2);

    QBP = - K_flow * pBP * u;

    sounds[MAIN_EMERGENCY_FLOW_SOUND].state = (mode_pos == -2);
    sounds[MAIN_EMERGENCY_FLOW_SOUND].volume = 2.0 * pBP;
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
    // Контроллер в нулевой позиции (выбег)
    if (mode_pos == 0)
    {
        trac_level = brake_level = 0;

        if ( (getKeyState(KEY_D)) && (!old_brake_key) )
        {
            --mode_pos;
            // Запрещаем непрерывное управление до второго нажатия клавиши
            brake = false;
        }
        else if ( (getKeyState(KEY_A)) && (!old_traction_key) )
        {
            ++mode_pos;
            // Запрещаем непрерывное управление до второго нажатия клавиши
            traction = false;
        }
    }

    // Контроллер в экстренном торможении
    if (mode_pos == -2)
    {
        traction = false;
        brake = true;
        // Возврат в максимальный уровень торможения
        if (getKeyState(KEY_A))
        {
            mode_pos = -1;
            brake_level = 90;
        }
    }

    // Контроллер в торможении
    if (mode_pos == -1)
    {
        traction = false;
        dir = 0;

        if (!brakeTimer->isStarted())
            brakeTimer->start();

        if (getKeyState(KEY_A))
        {
            // Возврат в выбег
            if (brake_level == 0)
            {
                mode_pos = 0;
                brakeTimer->stop();
                brake = false;
            }
            else
            {
                dir = 1;
            }
        }

        if (getKeyState(KEY_D))
        {
            // Управляем дальше только после второго нажатия клавиши
            if (brake)
                dir = -1;

            // После максимального уровня торможения переход в экстренное
            if (brake_level == 90)
            {
                // Только новым нажатием клавиши
                if (!old_brake_key)
                {
                    mode_pos = -2;
                }
            }
        }
        else
        {
            // Разрешаем управление, отпустив клавишу после первого нажатия
            brake = true;
        }
    }

    brakeTimer->step(t, dt);

    // Контроллер в тяге
    if (mode_pos == 1)
    {
        brake = false;
        dir = 0;

        if (!tracTimer->isStarted())
            tracTimer->start();

        if (getKeyState(KEY_D))
        {
            // Возврат в выбег
            if (trac_level == 0)
            {
                mode_pos = 0;
                tracTimer->stop();
                traction = false;
            }
            else
            {
                dir = -1;
            }
        }

        if (getKeyState(KEY_A))
        {
            // Управляем дальше только после второго нажатия клавиши
            if (traction)
                dir = 1;

        }
        else
        {
            // Разрешаем управление, отпустив клавишу после первого нажатия
            traction = true;
        }
    }

    tracTimer->step(t, dt);

    old_traction_key = getKeyState(KEY_A);
    old_brake_key = getKeyState(KEY_D);

    // Управление реверсом
    if (fwd_key && !old_fwd_key && (revers_pos < 1))
    {
        revers_pos++;
        sounds[REVERS_CHANGE_POS_SOUND].play();
    }

    if (bwd_key && !old_bwd_key && (revers_pos > -1))
    {
        revers_pos--;
        sounds[REVERS_CHANGE_POS_SOUND].play();
    }

    old_fwd_key = fwd_key;
    old_bwd_key = bwd_key;
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
