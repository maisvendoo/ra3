#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepMPSU(double t, double dt)
{
    mpsu_input_t mpsu_input;
    mpsu_input.is_power_on = static_cast<bool>(hs_p(Ucc - 90.0));
    mpsu_input.start_disel = tumbler[BUTTON_START].getState();
    mpsu_input.stop_disel = tumbler[BUTTON_STOP].getState();
    mpsu_input.fuel_press1 = fuel_pump->getFuelPressure();
    mpsu_input.fuel_press2 = static_cast<double>(backward_inputs[SME_BWD_FUEL_PRESS]);
    mpsu_input.oil_press1 = disel->getOilPressure();
    mpsu_input.oil_press2 = static_cast<double>(backward_inputs[SME_BWD_OIL_PRESS]);
    mpsu_input.disel1_shaft_freq = disel->getShaftFreq();
    mpsu_input.disel2_shaft_freq = static_cast<double>(backward_inputs[SME_BWD_OMEGA]);
    mpsu_input.trac_min = km->getMinTracLevel();
    mpsu_input.brake_min = km->getMinBrakeLevel();
    mpsu_input.trac_level = km->getTractionLevel();
    mpsu_input.brake_level = km->getBrakeLevel();

    mpsu->setInputData(mpsu_input);
    mpsu->step(t, dt);    
}
