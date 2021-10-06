#include    "aux-converter.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AuxiliaryConverter::AuxiliaryConverter(QObject *parent) : Device(parent)
  , k_380(0.0)
  , k_110(0.0)
  , k_27(0.0)
  , U_in(0.0)
  , U_bat_110(0.0)
  , KM_gen(Q_NULLPTR)
{
    KM_gen = new Relay(2);
    KM_gen->setInitContactState(0, false);
    KM_gen->setInitContactState(1, false);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AuxiliaryConverter::~AuxiliaryConverter()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AuxiliaryConverter::step(double t, double dt)
{
    KM_gen->step(t, dt);
    Device::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AuxiliaryConverter::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AuxiliaryConverter::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AuxiliaryConverter::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "k_380", k_380);
    cfg.getDouble(secName, "k_110", k_110);
    cfg.getDouble(secName, "k_27", k_27);
}

