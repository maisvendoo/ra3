#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initRegistrator()
{
    if (!is_Registarator_on)
        return;

    reg = new Registrator();
    reg->read_custom_config(config_dir +
                            QDir::separator() +
                            "registrator");
}
