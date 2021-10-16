#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initBrakeMech()
{
    for (size_t i = 0; i < brake_mech.size(); ++i)
    {
        brake_mech[i] = new RA3BrakeMech();
        brake_mech[i]->read_custom_config(config_dir + QDir::separator() +
                                          "brake-mech");

        brake_mech[i]->setEffFricRadius(wheel_diameter / 2.0);
    }
}
