#ifndef     RA3_BRAKE_MECH_H
#define     RA3_BRAKE_MECH_H

#include    "brake-mech.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3BrakeMech : public BrakeMech
{
public:

    RA3BrakeMech(size_t axis_num = 2, QObject *parent = Q_NULLPTR);

    ~RA3BrakeMech();

    /// Задать поток в камеры отпуска стояночного тормоза
    void setPBflow(double Q_st) { this->Q_st = Q_st; }

    /// Давление в камерах отпуска стояночного тормоза
    double getPBpressure() const { return getY(1); }

    /// Текущий относительный выход штока стояночного тормоза
    /// (от 0.0 - отпускное положение до 1.0 - тормозное положение)
    double getPBStockOutCoeff() const;

    /// Текущий выход штока стояночного тормоза, м
    double getPBStockOut() const;

    /// Нажатие на тормозную колодку при максимальном давлении в ТЦ
    double getMaxShoeForce() const { return Kmax; }

private:

    /// Объем камеры стояночного тормоза
    double V_st;

    /// Общий расход в камеры стояночного тормоза
    double Q_st;

    /// Общее число пружинных энергоаккумуляторов
    int num_ea;

    /// Текущий относительный выход штока стояночного тормоза
    double  pb_stock_out_coeff;

    /// Текущий выход штока стояночного тормоза, м
    double  pb_stock_out_cur;

    void preStep(state_vector_t &Y, double t) override;

    virtual void ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // RA3_BRAKE_MECH_H
