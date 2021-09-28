#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initSounds()
{
    for (size_t i = 2; i < tumbler.size(); ++i)
    {
        connect(&tumbler[i], &Trigger::soundPlay, this, &RA3HeadMotor::soundPlay);
        tumbler[i].setOnSoundName("Tumbler_On");
        tumbler[i].setOffSoundName("Tumbler_Off");
    }

    connect(KM_bat_110, &Relay::soundPlay, this, &RA3HeadMotor::soundPlay);
    KM_bat_110->setSoundName("Relay");

    connect(horn, &TrainHorn::soundPlay, this, &RA3HeadMotor::soundPlay);
    connect(horn, &TrainHorn::soundStop, this, &RA3HeadMotor::soundStop);
}
