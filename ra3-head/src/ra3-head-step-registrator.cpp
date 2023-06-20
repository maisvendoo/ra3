#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepRegistrator(double t, double dt)
{
    if (reg == Q_NULLPTR)
        return;

    QString msg = QString("%1 %2 %3 %4")
            .arg(railway_coord, 10, 'f', 2)
            .arg(blok->getVelocityKmh(), 4, 'f', 2);

    reg->print_msg(msg, t, dt);
}
