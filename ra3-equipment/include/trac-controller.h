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
        return !(traction.getState() || brake.getState());
    }

    float getHandlePosition() const;

    double getTractionLevel() const
    {
        return trac_min * qAbs(mode_pos) + static_cast<double>(trac_level) / 100.0;
    }

    double getBrakeLevel() const
    {
        return brake_min * qAbs(mode_pos) + static_cast<double>(brake_level) / 100.0;
    }

private:

    /// Позиция, определяющая режим управления
    /// (0 - выбег, 1 - ход, -1 - торможение)
    int mode_pos;

    bool old_traction_key;

    bool old_brake_key;

    double trac_min;

    double brake_min;

    int trac_level;

    int brake_level;

    double handle_pos;

    double omega_handle;

    int dir;

    Timer *brakeTimer;

    Timer *tracTimer;

    /// Блок-контакт "ХОД"
    Trigger traction;

    /// Блок-контакт "ТОРМОЖЕНИЕ"
    Trigger brake;

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
