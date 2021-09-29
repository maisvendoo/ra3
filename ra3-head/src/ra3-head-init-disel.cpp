#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initDisel()
{
    disel = new Disel();
    disel->read_custom_config(config_dir + QDir::separator() + "disel");

    starter = new Starter();
    starter->read_custom_config(config_dir + QDir::separator() + "starter");
}
