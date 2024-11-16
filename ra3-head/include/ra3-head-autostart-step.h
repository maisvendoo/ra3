#ifndef     RA3_HEAD_AUTOSTART_STEP_H
#define     RA3_HEAD_AUTOSTART_STEP_H

struct autostart_step_t
{
    bool    is_key_tumbler = false;
    int     id = 0;
    bool    state = false;
    double  timeout = 1.0;
    bool    is_release = true;

    autostart_step_t()
    {

    }
};

#endif // RA3_HEAD_AUTOSTART_STEP_H
