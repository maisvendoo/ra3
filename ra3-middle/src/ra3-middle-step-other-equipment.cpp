#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::stepOtherEquipment(double t, double dt)
{
    // Включение выдвижной ступени по сигналам СМЕ
    bool is_step = (sme_fwd->getSignal(SME_IS_STEP) + sme_bwd->getSignal(SME_IS_STEP)) >= 1.0;

    // Управление дверями по сигналам СМЕ
    // Принимаем спереди зеркально, сзади правильно
    bool is_L = (sme_fwd->getSignal(SME_DOOR_R_OPEN) + sme_bwd->getSignal(SME_DOOR_L_OPEN)) >= 1.0;
    bool is_R = (sme_fwd->getSignal(SME_DOOR_L_OPEN) + sme_bwd->getSignal(SME_DOOR_R_OPEN)) >= 1.0;

    door_L->setStepsEnabled(is_step);
    is_L ? door_L->open() : door_L->close();

    door_R->setStepsEnabled(is_step);
    is_R ? door_R->open() : door_R->close();

    door_L->step(t, dt);
    door_R->step(t, dt);
}
