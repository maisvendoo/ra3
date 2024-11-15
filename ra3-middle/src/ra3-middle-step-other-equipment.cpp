#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepOtherEquipment(double t, double dt)
{
    // Двери
    door_L->setPowerVoltage(Ucc_110);
    door_L2->setPowerVoltage(Ucc_110);
    door_R->setPowerVoltage(Ucc_110);
    door_R2->setPowerVoltage(Ucc_110);

    // Включение выдвижной ступени по сигналам СМЕ
    bool is_step = (sme_fwd->getSignal(SME_IS_STEP) + sme_bwd->getSignal(SME_IS_STEP)) >= 1.0;

    // Управление дверями по сигналам СМЕ
    // Принимаем спереди зеркально, сзади правильно
    bool is_L = (sme_fwd->getSignal(SME_DOOR_R_OPEN) + sme_bwd->getSignal(SME_DOOR_L_OPEN)) >= 1.0;
    bool is_R = (sme_fwd->getSignal(SME_DOOR_L_OPEN) + sme_bwd->getSignal(SME_DOOR_R_OPEN)) >= 1.0;

    door_L->setStepsEnabled(is_step);
    door_L2->setStepsEnabled(is_step);
    if (is_L)
    {
        door_L->open();
        door_L2->open();
    }
    else
    {
        door_L->close();
        door_L2->close();
    }

    door_R->setStepsEnabled(is_step);
    door_R2->setStepsEnabled(is_step);
    if (is_R)
    {
        door_R->open();
        door_R2->open();
    }
    else
    {
        door_R->close();
        door_R2->close();
    }

    door_L->step(t, dt);
    door_L2->step(t, dt);
    door_R->step(t, dt);
    door_R2->step(t, dt);
}
