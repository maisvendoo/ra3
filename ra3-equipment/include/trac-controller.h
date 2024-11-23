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
    int mode_pos = 0;

    int mode_pos_old = 0;

    bool old_traction_key = false;

    bool old_brake_key = false;

    bool fwd_key = false;

    bool old_fwd_key = false;

    bool bwd_key = false;

    bool old_bwd_key = false;

    int revers_pos = 0;

    int trac_min = 10;

    int brake_min = 10;

    int trac_level = 0;

    int brake_level = 0;

    double handle_pos = 0.0;

    /// Вращение контроллера по сигналу таймера
    int handle_motion_speed = 0;

    /// Коэффициент ускорения контроллера с нажатым Shift
    int handle_high_speed_coeff = 8;

    Timer *brakeTimer = new Timer(0.1, true);

    Timer *tracTimer = new Timer(0.1, true);

    /// Коэффициент утечки через клапан экстренного торможения
    double K_flow = 5.0e-2;

    /// Дввление в тормозной магистрали
    double pBP = 0.0;

    /// Расход из тормозной магистрали при экстренном торможении
    double QBP = 0.0;

    /// Управление рукояткой в тяге после второго нажатия
    bool traction = false;

    /// Управление рукояткой в торможении после второго нажатия
    bool brake = false;

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
