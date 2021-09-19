#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initSounds()
{
    for (size_t i = 0; i < tumbler.size(); ++i)
    {
        connect(&tumbler[i], &Trigger::soundPlay, this, &RA3HeadMotor::soundPlay);
        tumbler[i].setOnSoundName("Tumbler_On");
        tumbler[i].setOffSoundName("Tumbler_Off");
    }
}
