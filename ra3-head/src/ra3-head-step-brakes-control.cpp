#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakesControl(double t, double dt)
{
    kru->setFLpressure(main_reservoir->getPressure());
    kru->setBPpressure(brakepipe->getPressure());
    kru->setActive(active_cab_relay->getContactState(1) &&
                   (!emerg_brake_valve->isEmergencyBrake()) &&
                   (!km->isEmergencyBrake()));
    kru->setControl(keys);
    kru->step(t, dt);

    // Электропневматический клапан автостопа
    // Только в активной кабине
    if (active_cab_relay->getContactState(1))
    {
        epk->setFLpressure(main_reservoir->getPressure());
        epk->setBPpressure(brakepipe->getPressure());
        epk->setKeyOn(key_tumbler[IS_KEY_EPK].getState());
        epk->setPowered(blok->getEPKstate());
        epk->step(t, dt);
    }
    else
    {
        if (epk->isKeyOn())
        {
            epk->setKeyOn(false);
            epk->step(t, dt);
        }
    }

    emerg_brake_valve->setControl(keys);
    emerg_brake_valve->setBPpressure(brakepipe->getPressure());
    emerg_brake_valve->step(t, dt);
}
