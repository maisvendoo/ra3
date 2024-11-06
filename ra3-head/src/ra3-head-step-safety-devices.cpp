#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSafetyDevices(double t, double dt)
{
    // Приёмная катушка АЛСН
    coil_ALSN_fwd->step(t, dt);

    // Не работать в неактивной кабине
    if (!active_cab_relay->getContactState(1))
        return;

    // Дешифратор АЛСН
    alsn_decoder->setCoilSignal(coil_ALSN_fwd->getCode());
    alsn_decoder->step(t, dt);

    blok->setVoltage(Ucc_110);
    blok->setAlsnCode(alsn_decoder->getCode());
    blok->setKeyEPK(epk->isKeyOn());
    blok->setCoord(profile_point_data.position);
    blok->setRailCoord(profile_point_data.railway_coord);
    blok->setVelocity(wheel_omega[0] * wheel_diameter[0] / 2.0);
    blok->setTrainLength(mpsu->getOutputData().train_length);
    blok->setRBstate(tumbler[IS_BUTTON_RB].getState());
    blok->setRBSstate(tumbler[IS_BUTTON_RBS].getState());
    blok->step(t, dt);
}
