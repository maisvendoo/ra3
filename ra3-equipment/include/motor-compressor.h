#ifndef     MOTOR_COMPRESSOR_H
#define     MOTOR_COMPRESSOR_H

#include    "device.h"
#include    "motor-compressor-ac.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MotorCompressor : public ACMotorCompressor
{
public:

    MotorCompressor(QObject *parent = Q_NULLPTR);

    ~MotorCompressor();

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

    void load_config(CfgReader &cfg);
};

#endif // MOTOR_COMPRESSOR_H
