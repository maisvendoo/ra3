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

    /// Блок-контакт "ЭКСТРЕННОЕ ТОРМОЖЕНИЕ"
    bool isEmergencyBrake() const;

    /// Блок-контакт "ТОРМОЖЕНИЕ"
    bool isBrake() const;

    /// Блок-контакт "ВЫБЕГ"
    bool isZero() const;

    /// Блок-контакт "ХОД"
    bool isTraction() const;

    float getHandlePosition() const;

    double getTractionLevel() const
    {
        return static_cast<double>(trac_min * (mode_pos > 0) + trac_level) / 100.0;
    }

    double getBrakeLevel() const
    {
        return static_cast<double>(brake_min * (mode_pos < 0) + brake_level) / 100.0;
    }

    double getMinTracLevel() const { return static_cast<double>(trac_min) / 100.0; }

    double getMinBrakeLevel() const { return static_cast<double>(brake_min) / 100.0; }

    float getReversHandlePos() const { return static_cast<float>(revers_pos); }

    /// Задать давление от тормозной магистрали
    void setBPpressure(double value);

    /// Поток в тормозную магистраль
    double getBPflow() const;

    void setFwdKey(bool key_state) { fwd_key = key_state; }

    void setBwdKey(bool key_state) { bwd_key = key_state; }

    enum {
        NUM_SOUNDS = 3,
        REVERS_CHANGE_POS_SOUND = 0,    ///< Звук переключения реверсора
        MAIN_CHANGE_MODE_SOUND = 1,     ///< Звук переключения контроллера
        MAIN_EMERGENCY_FLOW_SOUND = 2   ///< Звук расхода воздуха при экстренном торможении
    };
    /// Состояние звука
    sound_state_t getSoundState(size_t idx = REVERS_CHANGE_POS_SOUND) const override;

    /// Сигнал состояния звука
    float getSoundSignal(size_t idx = REVERS_CHANGE_POS_SOUND) const override;

private:

    /// Позиция, определяющая режим управления
    /// (0 - выбег, 1 - ход, -1 - торможение, -2 - экстренное торможение)
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

    /// Коэффициент утечки через клапан экстренного торможения
    double K_flow;

    /// Дввление в тормозной магистрали
    double pBP;

    /// Расход из тормозной магистрали при экстренном торможении
    double QBP;

    /// Управление рукояткой в тяге после второго нажатия
    bool traction;

    /// Управление рукояткой в торможении после второго нажатия
    bool brake;

    /// Счётчик и состояние звуков
    std::array <sound_state_t, NUM_SOUNDS> sounds;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;

private slots:

    void slotTracLevelProcess();

    void slotBrakeLevelProcess();
};

#endif // TRAC_CONTROLLER_H
