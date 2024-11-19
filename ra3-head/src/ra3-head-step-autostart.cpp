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
    // Завершение программы автозапуска
    if (count_step == autostart_prog.size())
    {
        autostart_timer->stop();
        is_autostart = false;
        return;
    }

    // Отключение элемента управления, включенного на предыдущем шаге, если необходимо
    if ((count_step > 0) && (autostart_prog[count_step - 1].id >= 0) && (autostart_prog[count_step - 1].is_release))
    {
        if (autostart_prog[count_step - 1].is_key_tumbler)
            key_tumbler[autostart_prog[count_step - 1].id].reset();
        else
            tumbler[autostart_prog[count_step - 1].id].reset();
    }

    autostart_timer->setTimeout(autostart_prog[count_step].timeout);

    if (autostart_prog[count_step].id < 0)
    {
        // Пустой шаг
        count_step++;
        return;
    }

    // Шаг программы автозапуска
    if (autostart_prog[count_step].is_key_tumbler)
    {
        if (autostart_prog[count_step].state)
            key_tumbler[autostart_prog[count_step].id].set();
        else
            key_tumbler[autostart_prog[count_step].id].reset();
    }
    else
    {
        if (autostart_prog[count_step].state)
            tumbler[autostart_prog[count_step].id].set();
        else
            tumbler[autostart_prog[count_step].id].reset();
    }

    // Счётчик шагов программы автозапуска
    count_step++;
}
