#ifndef     RA3_BRAKE_MECH_H
#define     RA3_BRAKE_MECH_H

#include    "brake-mech.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3BrakeMech : public BrakeMech
{
public:

    RA3BrakeMech(QObject *parent = Q_NULLPTR);

    ~RA3BrakeMech();

private:

    void load_config(CfgReader &cfg) override;
};

#endif // RA3_BRAKE_MECH_H
