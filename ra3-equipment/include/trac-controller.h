#ifndef     TRAC_CONTROLLER_H
#define     TRAC_CONTROLLER_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class TracController : public Device
{
public:

    TracController(QObject *parent = Q_NULLPTR);

    ~TracController();

    /// Признак нулевого положения
    bool isZero()
    {
        return mode_pos == 0;
    }

    bool isTraction() { return mode_pos == 1; }

    bool isBrake() { return mode_pos == -1; }

    float getHandlePosition() const;

    double getTractionLevel() const
    {
        return static_cast<double>(trac_min * pf(mode_pos) + trac_level) / 100.0;
    }

    double getBrakeLevel() const
    {
        return static_cast<double>(brake_min * nf(mode_pos) + brake_level) / 100.0;
    }

    double getMinTracLevel() const { return static_cast<double>(trac_min) / 100.0; }

    double getMinBrakeLevel() const { return static_cast<double>(brake_min) / 100.0; }

    float getReversHandlePos() const { return static_cast<float>(revers_pos); }

    void setMainHandleSoundName(QString name) { mainHandleSoundName = name; }

    void setReversHandleSoundName(QString name) { reversSoundName = name; }

    /// Задать давление от тормозной магистрали
    void setBPpressure(double value);

    /// Поток в тормозную магистраль
    double getBPflow() const;

    /// Экстренное торможение
    bool isEmergencyBrake() const;

    void setFwdKey(bool key_state) { fwd_key = key_state; }

    void setBwdKey(bool key_state) { bwd_key = key_state; }

private:

    /// Позиция, определяющая режим управления
    /// (0 - выбег, 1 - ход, -1 - торможение)
    int mode_pos;

    int mode_pos_old;

    bool old_traction_key;

    bool old_brake_key;

    bool fwd_key;

    bool old_fwd_key;

    bool bwd_key;

    bool old_bwd_key;

    int revers_pos;

    int trac_min;

    int brake_min;

    int trac_level;

    int brake_level;

    double handle_pos;

    double omega_handle;

    int dir;

    Timer *brakeTimer;

    Timer *tracTimer;

    QString mainHandleSoundName;

    QString reversSoundName;

    /// Коэффициент утечки через клапан экстренного торможения
    double K_flow;

    /// Дввление в тормозной магистрали
    double pBP;

    /// Расход из тормозной магистрали при экстренном торможении
    double QBP;

    /// Блок-контакт "ХОД"
    Trigger traction;

    /// Блок-контакт "ТОРМОЖЕНИЕ"
    Trigger brake;

    /// Блок-контакт "ЭКСТРЕННОЕ ТОРМОЖЕНИЕ"
    Trigger emerg_brake;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;

    void processDiscretePositions(bool key_state, bool old_key_state, int dir);

private slots:

    void slotTracLevelProcess();

    void slotBrakeLevelProcess();
};

#endif // TRAC_CONTROLLER_H
