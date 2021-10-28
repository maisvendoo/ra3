#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepTraction(double t, double dt)
{
    double ip = 3.32;

    bool is_traction = (!mpsu->getOutputData().motion_disable) &&
            (km->isTraction() || static_cast<bool>(forward_inputs[SME_HYDRO_TRANS_FILL]));

    hydro_trans->setTractionMode(is_traction);

    if (is_active)
        hydro_trans->setRefReversState(km->getReversHandlePos());
    else
        hydro_trans->setRefReversState(static_cast<int>(forward_inputs[SME_REVERS_HANDLE]));

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
