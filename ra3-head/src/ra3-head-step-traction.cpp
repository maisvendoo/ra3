#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepTraction(double t, double dt)
{
    double ip = ip1 * ip2;

    bool is_auto_traction = mpsu->getOutputData().auto_trac_level > 0.01;

    if (is_active)
    {
        hydro_trans->setRefReversState(km->getReversHandlePos());
        hydro_trans->setTractionMode( (km->isTraction() || is_auto_traction) &&
                                      (!mpsu->getOutputData().motion_disable) &&
                                      epk->isTractionAllowed());
        hydro_trans->setBrakeMode(mpsu->getOutputData().hydro_brake_ON);
    }
    else
    {
        // Сигнал позиции реверсора принимаем спереди наоборот, сзади правильно
        hydro_trans->setRefReversState(
                    - static_cast<int>(sme_fwd->getSignal(SME_REVERS_HANDLE))
                    + static_cast<int>(sme_bwd->getSignal(SME_REVERS_HANDLE)) );
        hydro_trans->setTractionMode(
                       (sme_fwd->getSignal(SME_TRACTION_LEVEL) > Physics::ZERO)
                    || (sme_bwd->getSignal(SME_TRACTION_LEVEL) > Physics::ZERO) );
        hydro_trans->setBrakeMode(mpsu->getOutputData().hydro_brake_ON);
    }

    hydro_trans->setRefBrakeLevel(mpsu->getOutputData().brake_ref_level_GB);
    hydro_trans->setOmegaInput(disel->getOmega());
    hydro_trans->setOmegaOutput(ip * wheel_omega[0]);
    hydro_trans->step(t, dt);

    Q_a[1] = ip * hydro_trans->getOutputTorque() / 2.0;
    Q_a[2] = ip * hydro_trans->getOutputTorque() / 2.0;
}
