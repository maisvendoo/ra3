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

    double getTractionLevel() const { return trac_level; }

    double getBrakeLevel() const { return brake_level; }

private:

    /// Позиция, определяющая режим управления
    /// (0 - выбег, 1 - ход, -1 - торможение)
    int mode_pos;

    bool old_traction_key;

    bool old_brake_key;

    double trac_min;

    double brake_min;

    double trac_level;

    double brake_level;

    double handle_pos;

    double handle_omega;

    int dir;

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

private slots:

    void slotHandleRotate();
};

#endif // TRAC_CONTROLLER_H
