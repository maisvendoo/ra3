#ifndef     DOOR_CONTROL_MODULE_H
#define     DOOR_CONTROL_MODULE_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class DoorControlModule : public Device
{
public:

    DoorControlModule(QObject *parent = Q_NULLPTR);

    ~DoorControlModule();

    /// Включить выдвижные ступени
    void setStepsEnabled(bool is_steps_enabled);

    /// Команда на открытие выдвижной ступени (если включена) и дверей
    void open();

    /// Команда на включение предупреждающего сигнала, закрытие дверей и ступени
    void close();

    /// Целевое состояние двери
    bool getRefState() const;

    /// Контроль закрытия дверей
    int getDoorControlState() const;

    /// Сигнал состояния выдвижной ступени
    float getStepState() const;

    /// Сигнал состояния направляющего рельса дверей
    float getDoorSkidState() const;

    /// Сигнал состояния дверей
    float getDoorState() const;

    /// Сигнал состояния лампы, предупреждающей о закрытии дверей
    float getWarningSignal() const;

    /// Состояние звука зуммера, предупреждающего о закрытии дверей
    sound_state_t getSoundState(size_t idx = 0) const override;

    /// Сигнал состояния звука зуммера, предупреждающего о закрытии дверей
    float getSoundSignal(size_t idx = 0) const override;

private:

    enum
    {
        STEP_STATE = 0,
        DOOR_SKID_STATE = 1,
        DOOR_STATE = 2
    };

    /// Целевое состояние
    bool steps_enabled = false;

    /// Целевое состояние
    bool ref_state = false;

    /// Целевое положение выдвижной ступени
    double step_ref_state = 0.0;

    /// Целевое положение направляющего рельса дверей
    double door_skid_ref_state = 0.0;

    /// Целевое положение дверей
    double door_ref_state = 0.0;

    /// Время открытия/закрытия выдвиженой ступени, с
    double step_moving_time = 2.0;

    /// Время открытия/закрытия направляющего рельса дверей, с
    double door_skid_moving_time = 0.5;

    /// Время открытия/закрытия дверей, с
    double door_moving_time = 3.0;

    /// Периодичность предупреждающего звукового и светового сигнала, с
    double warning_signal_period = 1.0;

    /// Включение предупреждающего зуммера и сигнальной лампы
    bool warn_signal = false;

    Timer *warnSignalTimer = new Timer(warning_signal_period / 2.0, true);

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

private slots:

    void slotChangeWarningSignalState();
};

#endif // DOOR_CONTROL_MODULE_H
