#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initControlCircuit()
{
    bat110 = new Battery();
    bat110->read_custom_config(config_dir + QDir::separator() + "bat110");

    bat24 = new Battery();
    bat24->read_custom_config(config_dir + QDir::separator() + "bat24");
}
