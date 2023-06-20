#include    "hydro-transmission.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
HydroTransmission::HydroTransmission(QObject *parent) : Device(parent)
  , is_traction(false)
  , is_brake(false)
  , omega_in(0.0)
  , M_in(0.0)
  , M_out(0.0)
  , omega_out(0.0)
  , k(0.062)
  , T_gt(0.5)
  , T_gm(0.5)
  , T_gb(0.5)
  , u_gt(0.0)
  , u_gm(0.0)
  , u_gb(0.0)
  , i_min(0.8)
  , i_max(0.9)
  , revers_pos_ref(1)
  , T_revers(1.0)
  , revers_state(1)
  , revers_handle(0)
  , P_gb(300)
  , omega_db_max(162.0)
  , M_gb_max(0.0)
  , M_gb(0.0)
  , k_gb(0.0)
  , brake_level_ref(0.0)
  , brake_level(0.0)
  , Kp(1.0)
  , Ki(0.0)
  , delta_level(0.0)
  , switch_relay(new Hysteresis(i_min, i_max, false))
{
    setY(3, revers_pos_ref);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
HydroTransmission::~HydroTransmission()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HydroTransmission::setRefReversState(int revers_pos)
{
    revers_handle = revers_pos;

    // Реверсирование запрещено при движении
    if (qAbs(omega_out) >= 0.01)
        return;

    // Реверсирование запрещено при тяге и торможении
    if (is_traction || is_brake)
        return;

    if (revers_pos < 0)
        revers_pos_ref = -1;
    else
        revers_pos_ref = 1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int HydroTransmission::gap(double x)
{
    if ( (x > -1.0) && (x < 1.0) )
    {
        return 0;
    }
    else
    {
        if (x >= 1.0)
            return 1;

        if (x <= -1.0)
            return -1;
    }

    return 0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double HydroTransmission::brakeTorqueLimit(double omega_out)
{
    double M_lim = 0;

    if (qAbs(omega_out) >= omega_db_max)
        M_lim = P_gb * 1000.0 / qAbs(omega_out);
    else
        M_lim = M_gb_max;

    return M_lim;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HydroTransmission::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    double u_torque = static_cast<double>(is_traction);

    double u_brake = static_cast<double>(is_brake);

    double i_gp = 0;

    if (qAbs(omega_in) >= 0.1)
        i_gp = omega_out / omega_in;
    switch_relay->setValue(i_gp);

    revers_state = gap(Y[3]);

    u_gt = static_cast<double>(switch_relay->getState()) * qAbs(revers_state * revers_handle) * u_torque;
    u_gm = (1.0 - u_gt) * qAbs(revers_state * revers_handle) * u_torque;
    u_gb = u_brake;

    M_in = cut(Y[0] + Y[1], 0.0, 1.0) * k *  pow(omega_in, 2);

    double k_gm = getHydroCouplingCoeff(omega_in, omega_out);

    M_gb = k_gb * brake_level_ref * Y[2] * pow(omega_out, 2);

    M_gb = cut(M_gb, 0.0, brakeTorqueLimit(omega_out) * brake_level_ref);

    brake_level = M_gb / brakeTorqueLimit(omega_out);

    M_out = Y[0] * getHydroTranstCoeff(omega_in, omega_out) * M_in +
            Y[1] * k_gm * M_in - M_gb;
}

//------------------------------------------------------------------------------
//  Y[0] - уровень заполнения гидротрансформатора
//  Y[1] - уровень заполнения гидромуфты
//  Y[2] - уровень заполнения гидротормоза
//------------------------------------------------------------------------------
void HydroTransmission::ode_system(const state_vector_t &Y,
                                   state_vector_t &dYdt,
                                   double t)
{
    Q_UNUSED(t)

    dYdt[0] = (u_gt - Y[0]) / T_gt;

    dYdt[1] = (u_gm - Y[1]) / T_gm;

    dYdt[2] = (u_gb - Y[2]) / T_gt;

    dYdt[3] = (1.05 * revers_pos_ref - Y[3]) / T_revers;

    dYdt[4] = delta_level;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HydroTransmission::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "k", k);
    cfg.getDouble(secName, "T_gt", T_gt);
    cfg.getDouble(secName, "T_gm", T_gm);
    cfg.getDouble(secName, "T_gb", T_gb);
    cfg.getDouble(secName, "i_min", i_min);
    cfg.getDouble(secName, "i_max", i_max);

    switch_relay->setRange(i_min, i_max);

    QString path = custom_config_dir + QDir::separator() + "gdt.csv";
    gt_char.load(path.toStdString());

    path = custom_config_dir + QDir::separator() + "gdm.csv";
    gm_char.load(path.toStdString());

    cfg.getDouble(secName, "T_revers", T_revers);

    cfg.getDouble(secName, "P_gb", P_gb);
    cfg.getDouble(secName, "omega_gb_max", omega_db_max);

    M_gb_max = P_gb * 1000.0 / omega_db_max;
    k_gb = M_gb_max / omega_db_max / omega_db_max;

    cfg.getDouble(secName, "Kp", Kp);
    cfg.getDouble(secName, "Ki", Ki);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double HydroTransmission::getHydroTranstCoeff(double omega_in, double omega_out)
{
    if (qAbs(omega_in) < 0.1)
        return 0.0;

    return pf(gt_char.getValue(qAbs(omega_out) / qAbs(omega_in)));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double HydroTransmission::getHydroCouplingCoeff(double omega_in, double omega_out)
{
    if (qAbs(omega_in) < 0.1)
        return 0.0;

    return pf(gm_char.getValue(1.0 - qAbs(omega_out) / qAbs(omega_in)));
}
