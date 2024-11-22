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
    sand_system->setSandDeliveryOn(tumbler[IS_SAND].getState());
    sand_system->step(t, dt);
    // Пересчёт трения колесо-рельс
    psi[0] = sand_system->getWheelRailFrictionCoeff(psi[0]);
    psi[1] = sand_system->getWheelRailFrictionCoeff(psi[1]);

    hydro_pump->setDiselOmega(disel->getOmega());
    hydro_pump->step(t, dt);

    // Двери
    door_L->setPowerVoltage(Ucc_110);
    door_R->setPowerVoltage(Ucc_110);
    bool is_speed_3kmh = (Physics::kmh * wheel_omega[0] * wheel_diameter[0] / 2.0 > 3.0);
    if (active_cab_relay->getContactState(1))
    {
        // Включение выдвижной ступени
        door_L->setStepsEnabled(tumbler[IS_FIXED_STEP].getState());
        door_R->setStepsEnabled(tumbler[IS_FIXED_STEP].getState());

        if (is_speed_3kmh || tumbler[IS_FIXED_DOOR_L_CLOSE].getState())
        {
            // Безусловно закрываем, если скорость более 3 км/ч
            // или кнопка "закрыть" зафиксирована нажатой
            door_L->close();
        }
        else
        {
            // Иначе открываем по нажатию кнопки "открыть"
            if (key_tumbler[IS_BUTTON_DOOR_L_OPEN].getState())
                door_L->open();
        }

        if (is_speed_3kmh || tumbler[IS_FIXED_DOOR_R_CLOSE].getState())
        {
            // Безусловно закрываем, если скорость более 3 км/ч
            // или кнопка "закрыть" зафиксирована нажатой
            door_R->close();
        }
        else
        {
            // Иначе открываем по нажатию кнопки "открыть"
            if (key_tumbler[IS_BUTTON_DOOR_R_OPEN].getState())
                door_R->open();
        }
    }
    else
    {
        // Включение выдвижной ступени по сигналам СМЕ
        bool is_step = (sme_fwd->getSignal(SME_IS_STEP) + sme_bwd->getSignal(SME_IS_STEP)) >= 1.0;
        door_L->setStepsEnabled(is_step);
        door_R->setStepsEnabled(is_step);

        if (is_speed_3kmh)
        {
            // Безусловно закрываем, если скорость более 3 км/ч
            door_L->close();
            door_R->close();
        }
        else
        {
            // Управление дверями по сигналам СМЕ
            // Принимаем спереди зеркально, сзади правильно
            bool is_L = (sme_fwd->getSignal(SME_DOOR_R_OPEN) + sme_bwd->getSignal(SME_DOOR_L_OPEN)) >= 1.0;
            bool is_R = (sme_fwd->getSignal(SME_DOOR_L_OPEN) + sme_bwd->getSignal(SME_DOOR_R_OPEN)) >= 1.0;

            if (is_L)
            {
                door_L->open();
            }
            else
            {
                door_L->close();
            }

            if (is_R)
            {
                door_R->open();
            }
            else
            {
                door_R->close();
            }
        }
    }

    door_L->step(t, dt);
    door_R->step(t, dt);
}
