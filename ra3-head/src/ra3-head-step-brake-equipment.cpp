#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepBrakeEquipment(double t, double dt)
{
    bool is_parking_braked = tumbler[PARKING_BRAKE].getState() ||
            static_cast<bool>(forward_inputs[SME_PARKING_BRAKE]);

    brake_module->setParkingBrakeState(is_parking_braked);
    brake_module->setBrakeCylinderPressure(0.0);
    brake_module->setBrakepipePressure(pTM);
    brake_module->setAirSupplyPressure(aux_res->getPressure());
    brake_module->step(t, dt);
}
