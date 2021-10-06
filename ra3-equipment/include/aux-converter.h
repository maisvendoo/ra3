#ifndef     AUX_CONVERTER_H
#define     AUX_CONVERTER_H

#include    "device.h"
#include    "relay.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class AuxiliaryConverter : public Device
{
public:

    AuxiliaryConverter(QObject *parent = Q_NULLPTR);

    ~AuxiliaryConverter();

    void setInputVoltage(double U_in) { this->U_in = U_in; }

    void setBatteryVoltage(double U_bat_110) { this->U_bat_110 = U_bat_110; }

    void step(double t, double dt) override;

private:

    double  k_380;

    double  k_110;

    double  k_27;

    /// Напряжение от бортового генератора
    double  U_in;

    /// Напряжение от батареи 110 В
    double  U_bat_110;

    /// Контактор бортового генератора
    Relay   *KM_gen;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // AUX_CONVERTER_H
