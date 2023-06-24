#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakesControl(double t, double dt)
{
    if (is_active)
    {
        kru->setFLpressure(main_reservoir->getPressure());
        kru->setBPpressure(brakepipe->getPressure());
        kru->setControl(keys);
        kru->step(t, dt);

        // Электропневматический клапан автостопа
        epk->setFLpressure(main_reservoir->getPressure());
        epk->setBPpressure(brakepipe->getPressure());
        epk->setKeyState(tumbler[KEY_EPK].getState());
        epk->powerOn(blok->getEPKstate());
        epk->step(t, dt);

        emerg_brake_valve->setControl(keys);
        emerg_brake_valve->setBPpressure(brakepipe->getPressure());
        emerg_brake_valve->step(t, dt);
    }
    else
    {
        if (kru->getHandlePosition() != 0.0)
        {
            int pos = 0;
            kru->setHandlePosition(pos);
            kru->step(t, dt);
        }

        if (epk->getStateKey())
        {
            epk->setKeyState(false);
            epk->step(t, dt);
        }

        if (emerg_brake_valve->isEmergencyBrake())
        {
            emerg_brake_valve->setEmergencyBrake(false);
            emerg_brake_valve->step(t, dt);
        }
    }
}
