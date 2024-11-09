#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepOtherEquipment(double t, double dt)
{
    horn->setFLpressure(main_reservoir->getPressure());
    horn->setControl(keys);
    horn->step(t, dt);

    // Система подачи песка под оси передней (моторной) тележки
    sand_system->setFLpressure(main_reservoir->getPressure());
    sand_system->setControl(keys);
    sand_system->step(t, dt);
    // Пересчёт трения колесо-рельс
    psi[0] = sand_system->getWheelRailFrictionCoeff(psi[0]);
    psi[1] = sand_system->getWheelRailFrictionCoeff(psi[1]);

    hydro_pump->setDiselOmega(disel->getOmega());
    hydro_pump->step(t, dt);

    // Двери
    if (active_cab_relay->getContactState(1))
    {
        door_L->setStepsEnabled(tumbler[IS_BUTTON_STEP].getState());
        if (tumbler[IS_FIXED_DOOR_L_CLOSE].getState())
        {
            door_L->close();
        }
        else
        {
            if (tumbler[IS_BUTTON_DOOR_L_OPEN].getState())
                door_L->open();
        }

        door_R->setStepsEnabled(tumbler[IS_BUTTON_STEP].getState());
        if (tumbler[IS_FIXED_DOOR_R_CLOSE].getState())
        {
            door_R->close();
        }
        else
        {
            if (tumbler[IS_BUTTON_DOOR_R_OPEN].getState())
                door_R->open();
        }
    }
    else
    {
        bool is_step = (sme_fwd->getSignal(SME_IS_STEP) + sme_bwd->getSignal(SME_IS_STEP)) >= 1.0;
        bool is_L = (sme_fwd->getSignal(SME_DOOR_L_OPEN) + sme_bwd->getSignal(SME_DOOR_L_OPEN)) >= 1.0;
        bool is_R = (sme_fwd->getSignal(SME_DOOR_R_OPEN) + sme_bwd->getSignal(SME_DOOR_R_OPEN)) >= 1.0;

        door_L->setStepsEnabled(is_step);
        is_L ? door_L->open() : door_L->close();

        door_R->setStepsEnabled(is_step);
        is_R ? door_R->open() : door_R->close();
    }
    door_L->step(t, dt);
    door_R->step(t, dt);
}
