#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepRegistrator(double t, double dt)
{
    if (!is_Registrator_on)
        return;

    QString msg = QString("%1 %2 %3 %4 %5")
            .arg(velocity * Physics::kmh, 10, 'f', 2)
            .arg(2.0 * tractionForce / 1000.0, 4, 'f', 2)
            .arg(disel->getShaftFreq(), 4, 'f', 2)
                      .arg(hydro_trans->getY(0), 4, 'f', 2)
                      .arg(hydro_trans->getY(1), 4, 'f', 2);

    reg->print(msg, t, dt);
}
