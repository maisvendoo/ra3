#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSafetyDevices(double t, double dt)
{
    // Не работать в неактивной кабине
    if (!is_active)
        return;

    blok->setVoltage(Ucc_110);
    blok->setAlsnCode(alsn_info.code_alsn);
    blok->setRBstate(tumbler[BUTTON_RB].getState());
    blok->setRBSstate(tumbler[BUTTON_RBS].getState());
    blok->setRailCoord(railway_coord + dir * getLength() / 2.0);
    blok->setVelocity(wheel_omega[0] * wheel_diameter[0] / 2.0);
    blok->setTrainLength(mpsu->getOutputData().train_length);
    blok->setKeyEPK(epk->getStateKey());
    blok->step(t, dt);
}
