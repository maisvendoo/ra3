#include    "ra3-middle.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::initControlCircuit()
{
    bat110 = new Battery();
    bat110->read_custom_config(config_dir + QDir::separator() + "bat110");

    KM_power = new Relay(3);
    KM_power->read_custom_config(config_dir + QDir::separator() + "mk");
    KM_power->setInitContactState(0, false);
    KM_power->setInitContactState(1, false);
    KM_power->setInitContactState(2, false);
}
