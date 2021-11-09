#ifndef     RA3_HEAD_AUTOSTART_STEP_H
#define     RA3_HEAD_AUTOSTART_STEP_H

struct autostart_step_t
{
    int     id;
    bool    state;
    double  timeout;
    bool    is_release;

    autostart_step_t()
        : id(0)
        , state(false)
        , timeout(1.0)
        , is_release(true)
    {

    }
};

#endif // RA3_HEAD_AUTOSTART_STEP_H
