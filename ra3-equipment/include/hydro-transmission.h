#ifndef     HYDRO_TRANSMISSION_H
#define     HYDRO_TRANSMISSION_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class HydroTransmission : public Device
{
public:

    HydroTransmission(QObject *parent = Q_NULLPTR);

    ~HydroTransmission();

    /// Задать угловую скорость вражения выходного вала
    double setOmega(double omega) { this->omega_in = omega; }

    /// Вернуть момент на входном валу
    double getInputTorque() const { return M_in; }

    /// Вернуть момент на выходном валу
    double getOutputTorque() const { return M_out; }

    /// Задать угловую скорость на выходном валу
    void setOutputTorque(double omega) { this->omega_out = omega; }

private:

    double omega_in;

    double M_in;

    double M_out;

    double omega_out;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // HYDRO_TRANSMISSION_H
