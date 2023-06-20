#include    "aux-converter.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AuxiliaryConverter::AuxiliaryConverter(QString config_dir, QObject *parent) : Device(parent)
  , k_380(0.0)
  , k_110(0.0)
  , k_27(0.0)
  , U_min(400.0)
  , U_in(0.0)
  , U_bat_110(0.0)
  , KM_gen(Q_NULLPTR)
  , power_ON(false)
  , U_380(0.0)
  , U_110(0.0)
  , U_27(0.0)
{
    setCustomConfigDir(config_dir);

    KM_gen = new Relay(2);
    KM_gen->read_custom_config(custom_config_dir + QDir::separator() + "mk");
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
    Q_UNUSED(Y)
    Q_UNUSED(t)

    // Включение входного питания по сигналу МПСУ
    // и нормальному напряжению на входе
    bool is_powered = power_ON &&
            static_cast<bool>(hs_p(U_in - U_min));

    // Напряжение питания контактора подачи входного напряжения
    // Питание от батареи или самозапитка
    double U_km_gen = max(U_bat_110,
                          static_cast<double>(KM_gen->getContactState(0)) * U_110);

    KM_gen->setVoltage(U_km_gen * static_cast<double>(is_powered));

    // Напряжение на входе в преобразователь
    double U = U_in * static_cast<double>(KM_gen->getContactState(1));

    // Выходные напряжения каналов ПСН
    U_380 = k_380 * U;
    U_110 = k_110 * U;
    U_27 = k_27 * U;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AuxiliaryConverter::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
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
    cfg.getDouble(secName, "U_min", U_min);
}

