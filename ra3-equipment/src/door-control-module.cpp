#include    "door-control-module.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
DoorControlModule::DoorControlModule(QObject *parent) : Device(parent)
{
    connect(warnSignalTimer, &Timer::process, this, &DoorControlModule::slotWarningSignalTimeout);
    connect(warnSignalChange, &Timer::process, this, &DoorControlModule::slotChangeWarningSignalState);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
DoorControlModule::~DoorControlModule()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::step(double t, double dt)
{
    // При выключенном питании ничего не делаем
    if (U_power < 0.9 * U_nom)
    {
        ref_state = false;
        step_ref_state = 0.0;
        door_skid_ref_state = 0.0;
        door_ref_state = 0.0;
        warnSignalChange->stop();
        warnSignalTimer->stop();
        warn_signal = false;
        return;
    }

    warnSignalChange->step(t, dt);
    warnSignalTimer->step(t, dt);
    Device::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::setPowerVoltage(double U)
{
    U_power = U;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::setStepsEnabled(bool is_steps_enabled)
{
    steps_enabled = is_steps_enabled;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::open()
{
    ref_state = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::close()
{
    ref_state = false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool DoorControlModule::getRefState() const
{
    return ref_state;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int DoorControlModule::getDoorControlState() const
{
    // Закрыто
    if ((getY(STEP_STATE) < 0.05) && (getY(DOOR_SKID_STATE) < 0.05) && (getY(DOOR_STATE) < 0.05))
        return 1;

    // Открыто
    if (ref_state && (getY(DOOR_STATE) > 0.95))
        return 3;

    // В процессе открытия или закрытия
    return 2;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float DoorControlModule::getStepState() const
{
    return static_cast<float>(getY(STEP_STATE));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float DoorControlModule::getDoorSkidState() const
{
    return static_cast<float>(getY(DOOR_SKID_STATE));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float DoorControlModule::getDoorState() const
{
    return static_cast<float>(getY(DOOR_STATE));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float DoorControlModule::getWarningSignal() const
{
    return static_cast<float>(warn_signal);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
sound_state_t DoorControlModule::getSoundState(size_t idx) const
{
    (void) idx;
    return sound_state_t(warn_signal);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float DoorControlModule::getSoundSignal(size_t idx) const
{
    (void) idx;
    return sound_state_t::createSoundSignal(warn_signal);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::preStep(state_vector_t &Y, double t)
{
    (void) Y;
    (void) t;

    if (ref_state)
    {
        warnSignalTimer->stop();

        if (Y[DOOR_STATE] > 0.95)
        {
            // Двери открыты и останутся открытыми
            door_ref_state = 1.0;
            door_skid_ref_state = 1.0;
            warnSignalChange->stop();
            warn_signal = false;
        }
        else
        {
            // При открытии дверей работает предупреждающий сигнал
            if (!warnSignalChange->isStarted())
            {
                warnSignalChange->start();
            }
        }

        // Открытие дверей
        // Сперва открываем выдвижную ступень, если включена
        if (steps_enabled)
        {
            step_ref_state = 1.0;

            // При выдвинутой ступени готовим направляющий рельс дверей
            if (Y[STEP_STATE] > 0.95)
                door_skid_ref_state = 1.0;
            else
                door_skid_ref_state = 0.0;
        }
        else
        {
            // При отключенной ступени сразу готовим направляющий рельс дверей
            step_ref_state = 0.0;
            door_skid_ref_state = 1.0;
        }

        // После готовности направляющего рельса открываем двери
        if (Y[DOOR_SKID_STATE] > 0.95)
            door_ref_state = 1.0;
        else
            door_ref_state = 0.0;
    }
    else
    {
        if (Y[DOOR_STATE] < 0.05)
        {
            // Двери закрыты и останутся закрытыми
            door_ref_state = 0.0;
            door_skid_ref_state = 0.0;
        }
        else
        {
            // Закрываем открытые двери - сперва включаем предупреждающий сигнал
            if (!warnSignalChange->isStarted())
            {
                // Выдержка времени с предупреждающим сигналом перед закрытием дверей
                warnSignalTimer->start();
                // Мигание лампы
                warnSignalChange->start();
            }
        }

        // Закрытие дверей
        if (warnSignalChange->isStarted())
        {
            // Собственно закрытие дверей см. в слоте таймера выдержки времени

            // После схлопывания дверей закрываем направляющий рельс
            if (Y[DOOR_STATE] < 0.05)
                door_skid_ref_state = 0.0;
            else
                door_skid_ref_state = 1.0;

            // Предупреждающий сигнал отключается после закрытия направляющего рельса
            if (Y[DOOR_SKID_STATE] < 0.05)
            {
                warnSignalChange->stop();
                warn_signal = false;
            }
        }

        // После закрытия направляющего рельса убираем выдвижную ступень
        if (steps_enabled)
        {
            if (Y[DOOR_SKID_STATE] < 0.05)
                step_ref_state = 0.0;
            else
                step_ref_state = 1.0;
        }
        else
        {
            step_ref_state = 0.0;
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{
    (void) t;

    double delta = step_ref_state - Y[STEP_STATE];
    if (abs(delta) > 0.05)
    {
        dYdt[STEP_STATE] = sign(delta) / step_moving_time;
    }
    else
    {
        dYdt[STEP_STATE] = 20.0 * delta / step_moving_time;
    }

    delta = door_skid_ref_state - Y[DOOR_SKID_STATE];
    if (abs(delta) > 0.05)
    {
        dYdt[DOOR_SKID_STATE] = sign(delta) / door_skid_moving_time;
    }
    else
    {
        dYdt[DOOR_SKID_STATE] = 20.0 * delta / door_skid_moving_time;
    }

    delta = door_ref_state - Y[DOOR_STATE];
    if (abs(delta) > 0.05)
    {
        dYdt[DOOR_STATE] = sign(delta) / door_moving_time;
    }
    else
    {
        dYdt[DOOR_STATE] = 20.0 * delta / door_moving_time;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    double tmp = 0.0;
    cfg.getDouble(secName, "U_nom", tmp);
    if (tmp > Physics::ZERO)
        U_nom = tmp;

    tmp = 0.0;
    cfg.getDouble(secName, "step_moving_time", tmp);
    if (tmp > Physics::ZERO)
        step_moving_time = tmp;

    tmp = 0.0;
    cfg.getDouble(secName, "door_moving_time", tmp);
    if (tmp > Physics::ZERO)
        door_moving_time = tmp;

    tmp = 0.0;
    cfg.getDouble(secName, "door_skid_moving_time", tmp);
    if (tmp > Physics::ZERO)
        door_skid_moving_time = tmp;

    tmp = 0.0;
    cfg.getDouble(secName, "warning_signal_period", tmp);
    if (tmp > Physics::ZERO)
        warning_signal_period = tmp;
    warnSignalChange->setTimeout(warning_signal_period / 2.0);

    cfg.getDouble(secName, "warning_time", warning_time);
    warnSignalTimer->setTimeout(warning_time);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::slotWarningSignalTimeout()
{
    warnSignalTimer->stop();
    door_ref_state = 0.0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DoorControlModule::slotChangeWarningSignalState()
{
    warn_signal = !warn_signal;
}
