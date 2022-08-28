#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3Middle::RA3Middle(QObject *parent) : Vehicle(parent)
  , num(4003)
  , is_orient_same(true)
  , door_R_state(1)
  , door_L_state(1)
  , U_bat_110(0.0)
  , Ucc_110(0.0)
  , bat110(Q_NULLPTR)
  , KM_power(Q_NULLPTR)
  , main_res(Q_NULLPTR)
  , aux_res(Q_NULLPTR)
  , main_res_leak(0.0)
  , brake_module(Q_NULLPTR)
  , pb_split(Q_NULLPTR)
  , bc_split(Q_NULLPTR)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3Middle::~RA3Middle()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::initialization()
{
    initControlCircuit();

    initPneumoSystem();

    initBrakeMech();

    initBrakeEquipment();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::step(double t, double dt)
{
    stepControlCircuit(t, dt);

    stepPneumoSystem(t, dt);

    stepBrakeMech(t, dt);

    stepBrakeEquipment(t, dt);

    stepSignalsOutput(t, dt);

    stepSMESignalsOutput(t, dt);

    stepVehiclesConnect();

    debugOutput(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::loadConfig(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString secName = "Vehicle";

        cfg.getDouble(secName, "MainResLeak", main_res_leak);
        cfg.getInt(secName, "Number", num);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_VEHICLE(RA3Middle)
