#include    "motor-compressor.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MotorCompressor::MotorCompressor(QObject *parent) : ACMotorCompressor(parent)
  , P_nom(6000.0)
  , omega_nom(151.3)
  , zp(2)
  , freq(50.0)
  , lambda(2.5)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MotorCompressor::~MotorCompressor()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MotorCompressor::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "U_nom", U_nom);
    cfg.getDouble(secName, "omega0", omega0);
    cfg.getDouble(secName, "Mmax", Mmax);
    cfg.getDouble(secName, "s_kr", s_kr);
    cfg.getDouble(secName, "J", J);
    cfg.getDouble(secName, "Mxx", Mxx);

    cfg.getDouble(secName, "P_nom", P_nom);
    cfg.getDouble(secName, "omega_nom", omega_nom);
    cfg.getInt(secName, "zp", zp);
    cfg.getDouble(secName, "freq", freq);
    cfg.getDouble(secName, "lambda", lambda);

    omega0 = 2.0 * Physics::PI * freq / zp;
    double sn = 1 - omega_nom / omega0;
    s_kr = sn * (lambda + sqrt( lambda * lambda - 1 ) );

    Mmax = P_nom * lambda / omega_nom;

    cfg.getDouble(secName, "K_pressure", K_pressure);
    cfg.getDouble(secName, "K_flow", K_flow);

    cfg.getString(secName, "SoundName", soundName);
    cfg.getBool(secName, "RegulateSoundByOnOff", reg_sound_by_on_off);
    cfg.getBool(secName, "RegulateSoundByPitch", reg_sound_by_pitch);
}
