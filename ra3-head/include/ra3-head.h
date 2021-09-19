#ifndef     RA3_HEAD_H
#define     RA3_HEAD_H

#include    "vehicle-api.h"

#include    "ra3-tumblers-define.h"
#include    "fuel-tank.h"
#include    "battery.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3HeadMotor : public Vehicle
{
public:

    RA3HeadMotor(QObject *parent = Q_NULLPTR);

    ~RA3HeadMotor() override;    

private:

    /// Аккумуляторная батарея 110 В
    Battery     *bat110;

    /// Аккумуляторная батарея 24 В
    Battery     *bat24;

    enum
    {
        NUM_TANKS = 2,
        LEFT_TANK = 0,
        RIGHT_TANK = 1
    };

    /// Напряжение питания цепей управления
    double Ucc;

    /// Топливные баки
    std::array<FuelTank *, NUM_TANKS> fuel_tank;

    /// Выключатели в кабине
    std::array<Trigger, TUMBLERS_NUM> tumbler;

    void initialization() override;

    /// Инициализация системы питания топливом
    void initFuelSystem();

    /// Инициализация цепей управления
    void initControlCircuit();

    /// Инициализация звуков
    void initSounds();

    void step(double t, double dt) override;

    /// Моедлирования работы системы питания топливом
    void stepFuelSystem(double t, double dt);

    /// Моделирование работы цепей управления
    void stepControlCircuit(double t, double dt);

    /// Отладочный вывод
    void debugOutput(double t, double dt);

    void keyProcess() override;

    void loadConfig(QString cfg_path) override;
};

#endif // RA3_HEAD_H
