#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initSounds()
{
    connect(KM_bat_110, &Relay::soundPlay, this, &RA3HeadMotor::soundPlay);
    KM_bat_110->setSoundName("Relay");

    connect(horn, &TrainHorn::soundPlay, this, &RA3HeadMotor::soundPlay);
    connect(horn, &TrainHorn::soundStop, this, &RA3HeadMotor::soundStop);

    connect(fuel_pump, &ElectricFuelPump::soundPlay, this, &RA3HeadMotor::soundPlay);
    connect(fuel_pump, &ElectricFuelPump::soundStop, this, &RA3HeadMotor::soundStop);
    connect(fuel_pump, &ElectricFuelPump::soundSetPitch, this, &RA3HeadMotor::soundSetPitch);
    connect(fuel_pump, &ElectricFuelPump::soundSetVolume, this, &RA3HeadMotor::soundSetVolume);

    if (is_active)
        fuel_pump->setSoundName("Fuel_Pump1");
    else
        fuel_pump->setSoundName("Fuel_Pump2");
}
