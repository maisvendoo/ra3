#ifndef     RA3_SME_CONNECTOR_H
#define     RA3_SME_CONNECTOR_H

#include    "device.h"

#include    "ra3-sme-signals.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3SME : public Device
{
public:

    /// Конструктор
    RA3SME(QObject *parent = Q_NULLPTR);

    /// Деструктор
    ~RA3SME();

    /// Соединить межвагонные соединения
    void connect();

    /// Разъединить межвагонные соединения
    void disconnect();

    /// Состояние межвагонных соединений
    bool isConnected() const;

    /// Задать исходящий сигнал
    void setSignal(size_t idx, double value);

    /// Получить входящий сигнал
    double getSignal(size_t idx) const;

    virtual void step(double t, double dt);

private:

    /// Флаг вызова команд управления соединением рукавов
    bool is_ref_state_command;

    virtual void ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t);
};

#endif // RA3_SME_CONNECTOR_H
