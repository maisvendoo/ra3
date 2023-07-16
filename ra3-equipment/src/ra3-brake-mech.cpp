#include    "ra3-brake-mech.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3BrakeMech::RA3BrakeMech(size_t axis_num, QObject *parent) : BrakeMech(axis_num, parent)
  , V_st(5.0e-3)
  , Q_st(0.0)
  , num_ea(2)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3BrakeMech::~RA3BrakeMech()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3BrakeMech::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(t)

    // Рассчитываем положение штока стояночного тормоза
    pb_stock_out_coeff = cut((1 - Y[1] / p_max), 0.0, 1.0);
    pb_stock_out_cur = pb_stock_out_coeff * stock_out_max;

    // Нажатие от пружинного аккумулятора стояночного тормоза (тс)
    double K_st = pb_stock_out_coeff * Kmax;

    // Ограничение тормозного нажатия (тс), учитывающее зазор
    // в механизмах блок-тормоза с пружинным энергоаккумулятором
    double K_lim = pf(Kmax - K_st);

    // Нажатие от блок-тормоза без энергоаккумулятора
    double K_b1 = 0.0;

    // Нажатие от блок-тормоза с энергоаккумулятором
    double K_b2 = K_st;

    // Рассчитываем положение штока ТЦ
    stock_out_coeff = cut((Y[0] - p_begin) / (p_end - p_begin), 0.0, 1.0);
    stock_out_cur = stock_out_coeff * stock_out_max;

    // Если шток вышел полностью - считаем тормозное нажатие
    if (Y[0] - p_end > Physics::ZERO)
    {
        // Вычисляем нажатие на одну колодку (тс)
        Kcoef = (Y[0] - p_end) / (p_max - p_end);
        K = Kcoef * Kmax;

        K_b1 += K;
        K_b2 += cut(K, 0.0, K_lim);
    }

    for (size_t i = 0; i < axis_num; ++i)
    {
        double v = axis_omega[i] * wheel_r;

        // Тормозное усилие от б/т без энергоаккумулятора (Н)
        double shoe_brake_force1 = K_b1 * phi(K_b1, v) * Physics::g * 1000.0;

        // Тормозное усилие от б/т с энергоаккумулятором (Н)
        double shoe_brake_force2 = K_b2 * phi(K_b2, v) * Physics::g * 1000.0;

        // Момент от тормозных сил на колесной паре (Н * м)
        brake_torque[i] = (shoe_brake_force1 + shoe_brake_force2) * eff_r;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3BrakeMech::ode_system(const state_vector_t &Y,
                              state_vector_t &dYdt,
                              double t)
{
    dYdt[1] = Q_st / V_st / num_ea;

    BrakeMech::ode_system(Y, dYdt, t);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3BrakeMech::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "V_st", V_st);
    cfg.getInt(secName, "num_ea", num_ea);

    BrakeMech::load_config(cfg);
}
