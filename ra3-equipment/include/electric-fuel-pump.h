#ifndef     ELECTRIC_FUEL_PUMP_H
#define     ELECTRIC_FUEL_PUMP_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ElectricFuelPump : public Device
{
public:

    ElectricFuelPump(QObject *parent = Q_NULLPTR);

    ~ElectricFuelPump();

    /// Вернуть давление в топливной рампе перед ТНВД
    double getFuelPressure() const;

    /// Вернуть полный потребляемый ток
    double getCurrent() const;

    /// Задать фактический уровень топлива в баке
    void setFuelLevel(double fuel_level);

    /// Задать напряжение на двигателе насоса
    void setVoltage(double U);

    /// Признак работы топливного насоса
    bool isStarted() const { return is_started; }

    /// Состояние звука топливного насоса
    sound_state_t getSoundState(size_t idx = 0) const;

    /// Сигнал состояния звука топливного насоса
    float getSoundSignal(size_t idx = 0) const;

private:

    /// Напряжение питания, В
    double  U;

    /// Ток якоря, А
    double  Ia;

    /// Ток возбуждения, А
    double  If;

    /// Сопротивление обмотки якоря, Ом
    double  Ra;

    /// Сопротивление обмотки возбуждения
    double  Rf;

    /// Коэффициент противо-ЭДС при номинальном токе
    double  cF;

    /// Момент инерции подвижных частей насоса
    double  J;

    /// Максимальное давление, создаваемое на входе ТНВД
    double  p_max;

    /// Номинальные обороты двигателя
    double omega_nom;

    /// Коэффициент сопротивления вращению насоса
    double  kc;

    /// Минимальный уровень в баке, при котором возможен забор топлива
    double level_min;

    /// Фактический уровень в баке
    double fuel_level;

    /// Фактическое давление нагнетаемого топлива
    double fuel_press;

    /// Признак работы топливного насоса
    bool is_started;

    /// Звук топливного насоса
    sound_state_t sound;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // ELECTRIC_FUEL_PUMP_H
