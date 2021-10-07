#ifndef     MOTOR_COMPRESSOR_H
#define     MOTOR_COMPRESSOR_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MotorCompressor : public Device
{
public:

    MotorCompressor(QObject *parent = Q_NULLPTR);

    ~MotorCompressor();

    void setExternalPressure(double press);

    double getAirFlow() const;

    void setU_power(double value);

private:

    /// Номинальная мощность
    double P_nom;

    /// Номинальная угловая скорость
    double omega_nom;

    /// Число пар полюсов обмотки статора
    int zp;

    /// Частота питающего напряжения
    double freq;

    /// Перегрузочная способность по моменту
    double lambda;

    /// Внешнее противодавление
    double  p;

    /// Расход возхуа
    double  Q;

    /// "Подача" компрессора
    double  p0;

    double  Mmax;

    double  s_kr;

    double  Un;

    double  U_power;

    double  omega0;

    double  J;

    double  Mc;

    double  Vnk;

    enum
    {
        NUM_COEFFS = 6
    };

    std::array<double, NUM_COEFFS>  K;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);    
};

#endif // MOTOR_COMPRESSOR_H
