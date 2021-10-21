#include    "trac-controller.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TracController::TracController(QObject *parent) : Device(parent)
  , mode_pos(0)
  , old_traction_key(false)
  , old_brake_key(false)
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
    float handle_pos = 0.17f * static_cast<float>(traction.getState()) -
                       0.26f * static_cast<float>(brake.getState());

    return handle_pos;
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
            mode_pos++;
        }

        if (brake.getState())
        {
            brake.reset();
            mode_pos--;
        }
    }

    if (getKeyState(KEY_D))
    {
        if (isZero() && !old_brake_key)
        {
            brake.set();
            mode_pos--;
        }

        if (traction.getState())
        {
            traction.reset();
            mode_pos++;
        }
    }

    old_traction_key = getKeyState(KEY_A);
    old_brake_key = getKeyState(KEY_D);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TracController::slotHandleRotate()
{

}
