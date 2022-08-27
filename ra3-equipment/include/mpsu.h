#ifndef     MPSU_H
#define     MPSU_H

#include    "device.h"

#include    "mpsu-data.h"
#include    "ra3-sme-signals.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MPSU : public Device
{
public:

    MPSU(QObject *parent = Q_NULLPTR);

    ~MPSU();

    void step(double t, double dt) override;

    void setInputData(const mpsu_input_t &mpsu_input);

    mpsu_output_t getOutputData() const;

private:

    /// Признак сброса МПСУ
    bool is_reseted;

    /// Предыдущее состояние кнопки "СТАРТ"
    bool old_start_state;

    /// Уставка минимальных оборотов дизеля
    double n_min;

    /// Уставка максимальных оборотов дизеля
    double n_max;

    /// Минимальные обороты дизеля при ГДТ
    double n_min_gb;

    /// Уставка скорости срабатывания удерживающего тормоза
    double v_HB;

    /// Уставка давления в ТЦ для удерживающего тормоза
    double p_HB;

    /// Таймер контроля нажатия кнопки "Старт"
    Timer *startButtonTimer;

    /// Старое состояние кнопки "Выбор скорости"
    bool button_select_old;

    /// Старое состояние кнопки "Скорость +"
    bool button_speed_plus_old;

    /// Старое состояние кнопки "Скорость -"
    bool button_speed_minus_old;

    /// Запрет режима поддержания заданной скорости
    bool is_speed_hold_disable;

    /// Пропорциональны коэффициент регулятора скорости
    double Kp;

    /// Интегральный коэффициент регулятора скорости
    double Ki;

    /// Ошибка по скорости
    double dv;

    /// Управляющее воздействие с регулятора скорости
    double u;

    /// Постоянная времени задатчика усилия
    double T;

    /// Длина головного вагона
    double lengthHead;

    /// Длина промежуточного вагона
    double lengthMiddle;

    /// Входные сигналы
    mpsu_input_t    mpsu_input;

    /// Выходные сигналы
    mpsu_output_t   mpsu_output;

    /// Триггер активации запуска дизеля
    Trigger trig_disel_start;

    /// Триггер открытия топливных клапанов
    Trigger trig_fuel_valve;

    /// Тригер фиксации сообщения об ошибке
    Trigger error_fixed;

    /// Триггер блокирования движения после ЭТ
    Trigger motion_lock;

    /// Ячейки текущих запретов
    std::array<bool, ERRORS_NUM> errors;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    /// Сброс МПСУ
    void reset();

    /// Главный цикл управления
    void main_loop_step(double t, double dt);

    /// Обработка опроса конфигурации СМЕ
    void train_config_process();

    /// Разбор конфигурации СМЕ
    void train_config_parsing(int tc);

    /// Обработка кнопки старт
    void start_button_process(bool is_start_button);

    /// Запуск дизелей
    void start_disels();

    /// Останов дизелей
    void stop_disels();

    /// Контроль давления масла дизелей
    int check_disels_oil_pressure(double p_oil);

    /// Диагностика дизелей
    int check_disels(int mfdu_oil_press_level);

    void check_alarm_level();

    /// Задатчик оборотов дизеля в тяге
    double getTracRefDiselFreq(double trac_level, double brake_level);

    /// Проверка состояния реверсирования
    void check_revers();

    /// Проверка на запрет движения
    void check_moition_disable();

    /// Алгоритм работы удерживающего тормоза
    void holding_brake_step();

    /// Обработка ошибок
    void output_error_msg();

    /// Определение уровня тормозного усилия от ПТ/ЭПТ
    void calc_brake_level_PB();

    /// Управление гидродинамическим торможением
    void hydro_brake_control();

    /// Определение типа торможения
    void unit_brakes_sheck();

    /// Расчет максимального тормозного усилия ЭПТ при данной скорости
    double calcMaxBrakeForce(double V);

    /// Контроль давления масла дизелей
    void check_disels_oil_pressure();

    /// Обработка кнопок ПУ-4 по режиму "Поддержание скорости"
    void hold_speed_buttons_process();

    /// Регулятор скорости
    void speed_regulator();

private slots:

    void slotStartButtonTimer();
};

#endif // MPSU_H
