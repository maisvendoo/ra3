#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initSounds()
{
    connect(fuel_pump, &ElectricFuelPump::soundPlay, this, &RA3HeadMotor::soundPlay);
    connect(fuel_pump, &ElectricFuelPump::soundStop, this, &RA3HeadMotor::soundStop);
    connect(fuel_pump, &ElectricFuelPump::soundSetPitch, this, &RA3HeadMotor::soundSetPitch);
    connect(fuel_pump, &ElectricFuelPump::soundSetVolume, this, &RA3HeadMotor::soundSetVolume);

    connect(starter, &Starter::soundPlay, this, &RA3HeadMotor::soundPlay);
    connect(starter, &Starter::soundStop, this, &RA3HeadMotor::soundStop);

    connect(disel, &Disel::soundPlay, this, &RA3HeadMotor::soundPlay);
    connect(disel, &Disel::soundStop, this, &RA3HeadMotor::soundStop);
    connect(disel, &Disel::soundSetPitch, this, &RA3HeadMotor::soundSetPitch);
    connect(disel, &Disel::soundSetVolume, this, &RA3HeadMotor::soundSetVolume);

        fuel_pump->setSoundName("Fuel_Pump1");
        starter->setSoundName("Starter1");
}
