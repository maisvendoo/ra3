#ifndef     AUX_CONVERTER_H
#define     AUX_CONVERTER_H

#include    "device.h"
#include    "relay.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class AuxiliaryConverter : public Device
{
public:

    AuxiliaryConverter(QString config_dir, QObject *parent = Q_NULLPTR);

    ~AuxiliaryConverter();

    void setPowerON(bool power_ON) { this->power_ON = power_ON; }

    void setInputVoltage(double U_in) { this->U_in = U_in; }

    void setBatteryVoltage(double U_bat_110) { this->U_bat_110 = U_bat_110; }

    void step(double t, double dt) override;

    double getU_380() const { return U_110; }

    double getU_110() const { return U_110; }

    double getU_27() const { return U_27; }

private:

    double  k_380;

    double  k_110;

    double  k_27;

    /// Минимальное входное напряжение для запуска
    double U_min;

    /// Напряжение от бортового генератора
    double  U_in;

    /// Напряжение от батареи 110 В
    double  U_bat_110;

    /// Контактор бортового генератора
    Relay   *KM_gen;

    /// Сигнал включения ПСН
    bool    power_ON;

    /// Линейное напряжение трехфазной шины
    double U_380;

    /// Напряжение шины постоянного тока 110 В
    double U_110;

    /// Напряжение шины постоянного тока 27 В
    double U_27;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // AUX_CONVERTER_H
