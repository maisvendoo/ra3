#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepTraction(double t, double dt)
{
    double ip = 3.32;

    if (is_active)
    {
        hydro_trans->setTractionMode(km->isTraction());
        hydro_trans->setRefReversState(km->getReversHandlePos());
        //hydro_trans->setRefBrakeLevel(km->getBrakeLevel());
        hydro_trans->setBrakeMode(mpsu->getOutputData().hydro_brake_ON1);
    }
    else
    {
        hydro_trans->setTractionMode(static_cast<bool>(forward_inputs[SME_IS_KM_TRACTION]));
        hydro_trans->setRefReversState(static_cast<int>(forward_inputs[SME_REVERS_HANDLE]));
        //hydro_trans->setRefBrakeLevel(forward_inputs[SME_REF_BRAKE_LEVEL]);
        hydro_trans->setBrakeMode(mpsu->getOutputData().hydro_brake_ON2);
    }

    hydro_trans->setRefBrakeLevel(mpsu->getOutputData().brake_ref_level_GB);
    hydro_trans->setOmegaInput(disel->getOmega());
    hydro_trans->setOmegaOutput(ip * wheel_omega[0]);    
    hydro_trans->step(t, dt);

    if (is_active)
    {
        Q_a[1] = ip * hydro_trans->getOutputTorque() / 2.0;
        Q_a[2] = ip * hydro_trans->getOutputTorque() / 2.0;
    }
    else
    {
        Q_a[3] = ip * hydro_trans->getOutputTorque() / 2.0;
        Q_a[4] = ip * hydro_trans->getOutputTorque() / 2.0;
    }
}
