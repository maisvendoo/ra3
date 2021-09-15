#ifndef     RA3_HEAD_H
#define     RA3_HEAD_H

#include    "vehicle-api.h"

#include    "fuel-tank.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class RA3HeadMotor : public Vehicle
{
public:

    RA3HeadMotor(QObject *parent = Q_NULLPTR);

    ~RA3HeadMotor() override;

private:

    enum
    {
        NUM_TANKS = 2,
        LEFT_TANK = 0,
        RIGHT_TANK = 1
    };

    std::array<FuelTank *, NUM_TANKS> fuel_tank;

    void initialization() override;

    /// Инициализация системы питания топливом
    void initFuelSystem();

    void step(double t, double dt) override;

    /// Моедлирования работы системы питания топливом
    void stepFuelSystem(double t, double dt);

    void keyProcess() override;

    void loadConfig(QString cfg_path) override;
};

#endif // RA3_HEAD_H
