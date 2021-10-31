#ifndef     EMERGENCY_BRAKE_VALVE_H
#define     EMERGENCY_BRAKE_VALVE_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class EmergencyBrakeValve : public Device
{
public:

    EmergencyBrakeValve(QObject *parent = Q_NULLPTR);

    ~EmergencyBrakeValve();

    void setBrakePipePressure(double pTM) { this->pTM = pTM; }

    double getEmergencyRate() const { return emergencyRate; }

    bool isEmergencyBrake() const { return brake.getState(); }

private:

    double emergencyRate;

    double pTM;

    double K_flow;

    Trigger brake;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // EMERGENCY_BRAKE_VALVE_H
