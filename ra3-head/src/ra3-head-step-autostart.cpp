#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepAutostart(double t, double dt)
{
    if (autostart_timer != Q_NULLPTR)
        autostart_timer->step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::slotAutostart()
{
    if (count_step == autostart_prog.size())
    {
        autostart_timer->stop();
        is_autostart = false;
        return;
    }

    if (count_step > 0)
    {
        if (autostart_prog[count_step-1].is_release)
            tumbler[autostart_prog[count_step-1].id].reset();
    }

    if (autostart_prog[count_step].state)
        tumbler[autostart_prog[count_step].id].set();
    else
        tumbler[autostart_prog[count_step].id].reset();

    autostart_timer->setTimeout(autostart_prog[count_step].timeout);

    count_step++;
}
