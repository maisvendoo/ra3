#ifndef     KEY_TRIGGER_H
#define     KEY_TRIGGER_H

#include    "trigger.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class KeyTrigger : public Trigger
{
public:

    KeyTrigger();

    ~KeyTrigger();

    void setState(bool key_state)
    {
        key_state_old = this->key_state;
        this->key_state = key_state;

        // Нажатие клавиши после отпускания
        if ( (key_state) && (!key_state_old) )
        {
            // Меняем состояние триггера на противоположное
            if (getState())
                reset();
            else
                set();
        }
    }

protected:

    bool key_state;

    bool key_state_old;
};

#endif // KEY_TRIGGER_H
