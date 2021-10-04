#ifndef     STARTER_H
#define     STARTER_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Starter : public Device
{
public:

    Starter(QObject *parent = Q_NULLPTR);

    ~Starter();

    double getTorque() const;

    void setVoltage(double U) { this->U = U; }

    void setOmega(double omega) { this->omega = omega; }

    void setSoundName(QString soundName) { this->soundName = soundName; }

    double getCurrent() const { return I; }

private:

    /// Номинальная механическая мощность
    double P_nom;

    /// Номинальная частота вращения
    double omega_nom;

    /// Номинальное напряжение питания
    double U_nom;

    /// Номинальный ток
    double I_nom;

    /// Ток якоря
    double I;

    /// Постоянная намагничивания
    double cPhi;

    /// Эквивалентное сопротивление цепи якоря
    double Ra;

    /// Угловая скорость вращения вала
    double omega;

    /// Напряжение на якоре
    double U;

    /// Имя звукового файла
    QString soundName;

    bool is_sound;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);
};

#endif // STARTER_H
