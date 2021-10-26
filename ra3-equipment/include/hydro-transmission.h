#ifndef     HYDRO_TRANSMISSION_H
#define     HYDRO_TRANSMISSION_H

#include    "device.h"

#include    "linear-interpolation.h"
#include    "hysteresis.h"

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
    double getOutputTorque() const { return M_out * revers_state; }

    /// Сигнал наполнения гидротрансформатора
    void setTractionMode(bool is_fill)
    {
        is_traction = is_fill;
    }    

    /// Сигнал наполнения гидротормоза
    void setBrakeMode(bool is_fill)
    {
        is_brake = is_fill;
    }

    double getOmegaInput() const { return omega_in; }

    double getOmegaOutput() const { return omega_out; }

    void setRefReversState(int revers_pos);

    int getReversState() const { return revers_state * qAbs(revers_handle); }

    double getTractionLevel() const { return cut(getY(0) + getY(1), 0.0, 1.0); }

    double getHydroBrakeLevel() const { return getY(2); }

private:

    bool is_traction;

    bool is_brake;

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

    double i_min;

    double i_max;

    /// Заданное положение реверсивного механизма
    int revers_pos_ref;

    /// Постоянная времени реверирования
    double T_revers;

    /// Состояние реверсивного механизма
    int revers_state;

    /// Состояние переключателя реверса
    int revers_handle;

    /// Характеристика гидротрансформатора
    LinearInterpolation gt_char;

    /// Характеристика гидромуфты
    LinearInterpolation gm_char;

    /// Гистерезис для реализации переключения скоростей
    Hysteresis  switch_relay;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    double getHydroTranstCoeff(double omega_in, double omega_out);

    double getHydroCouplingCoeff(double omega_in, double omega_out);

    /// Учет зазора в меранизме реверсирования
    int gap(double x);
};

#endif // HYDRO_TRANSMISSION_H
