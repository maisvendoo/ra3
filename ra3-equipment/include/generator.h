#ifndef     GENERATOR_H
#define     GENERATOR_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Generator : public Device
{
public:

    Generator(QObject *parent = Q_NULLPTR);

    ~Generator();

    void setDiselOmega(double omega) { this->omega = omega; }

    void setLoadCurrent(double I) { this->I = I; }

    double getOmega() const { return getY(0); }

    double getVoltage110() const { return U * U_110 / U_nom; }

    double getVoltage27() const { return U * U_27 / U_nom; }

    double getVoltage() const { return U / sqrt(3.0); }

private:

    double P_nom;

    double U_nom;

    double I_nom;

    double omega_nom;

    double cF;

    /// Сопротивление фазы генератора
    double r;

    /// приведенный момент инерции вала
    double J;

    /// Угловая скорость вращения коленчатого вала дизеля
    double omega;

    /// Ток нагрузки фазы
    double I;

    /// Линейное напряжение
    double U;

    /// Управляющее воздействие от системы регулирования оборотов
    double u;

    /// Ошибка по угловой скорости
    double delta_omega;

    ///
    double U_110;

    double U_27;

    double Mc;

    enum
    {
        NUM_COEFFS = 10
    };

    std::array<double, NUM_COEFFS> K;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // GENERATOR_H
