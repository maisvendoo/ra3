#include    "trac-controller.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TracController::TracController(QObject *parent) : Device(parent)
  , mode_pos(0)
  , old_traction_key(false)
  , old_brake_key(false)
  , trac_min(0.17)
  , brake_min(0.26)
  , trac_level(0.0)
  , brake_level(0.0)
  , handle_pos(0.0)
  , handle_omega(0.5)
  , dir(0)
{

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
float TracController::getHandlePosition() const
{
    return handle_pos / 5.0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "trac_min", trac_min);
    cfg.getDouble(secName, "brake_min", brake_min);
    cfg.getDouble(secName, "handle_omega", handle_omega);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::stepKeysControl(double t, double dt)
{
    if (getKeyState(KEY_A))
    {
        if (isZero() && !old_traction_key)
        {
            traction.set();
            handle_pos = 1;
        }

        dir = 1;
    }
    else
    {
        dir = 0;
    }

    if (getKeyState(KEY_D))
    {
        if (isZero() && !old_brake_key)
        {
            brake.set();
            handle_pos = -1;
        }

        dir = -1;
    }
    else
    {
        dir = 0;
    }

    handle_pos += handle_omega * dir *dt;

    handle_pos = cut(handle_pos, -2.0, 2.0);

    /*if ( (handle_pos >= -1) && (handle_pos <= 1) )
    {
        dir = 0;
        handle_pos = 0;
        traction.reset();
        brake.reset();
    }*/

    old_traction_key = getKeyState(KEY_A);
    old_brake_key = getKeyState(KEY_D);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::slotHandleRotate()
{

}
