#ifndef     HYDRO_TRANSMISSION_H
#define     HYDRO_TRANSMISSION_H

#include    "device.h"

#include    "linear-interpolation.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class HydroTransmission : public Device
{
public:

    HydroTransmission(QObject *parent = Q_NULLPTR);

    ~HydroTransmission();

    /// Задать угловую скорость вражения выходного вала
    double setOmegaInput(double omega) { this->omega_in = omega; }

    double setOmegaOutput(double omega) { this->omega_out = omega; }

    /// Вернуть момент на входном валу
    double getInputTorque() const { return M_in; }

    /// Вернуть момент на выходном валу
    double getOutputTorque() const { return M_out; }    

    /// Сигнал наполнения гидротрансформатора
    void setHydroTransFill(bool is_fill)
    {
        u_gt = static_cast<double>(is_fill);
    }

    /// Сигнал наполнения гидромуфты
    void setHydroCouplingFill(bool is_fill)
    {
        u_gm = static_cast<double>(is_fill);
    }

    /// Сигнал наполнения гидротормоза
    void setHydroBrakeFill(bool is_fill)
    {
        u_gb = static_cast<double>(is_fill);
    }

private:

    double omega_in;

    double M_in;

    double M_out;

    double omega_out;

    /// Коэффициент гидравлического сопротивления вращению насосных колес
    double k;

    /// Постянная времени наполнения гидротрансформатора
    double T_gt;

    /// Постоянная времения наполнения гидромуфты
    double T_gm;

    /// Постоянная времения наполнения гидротормоза
    double T_gb;

    double u_gt;

    double u_gm;

    double u_gb;

    /// Характеристика гидротрансформатора
    LinearInterpolation gt_char;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    double getHydroTranstCoeff(double omega_in, double omega_out);
};

#endif // HYDRO_TRANSMISSION_H
