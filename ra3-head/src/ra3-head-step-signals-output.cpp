#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSignalsOutput(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Анимации модели и кабины
    animationSignalsOutput(t, dt);

    // Отображение данных на дисплей БЛОК-М
    blokSignalsOutput(t, dt);

    // Отображение данных на дисплей МФДУ
    mdfuSignalsOutput(t, dt);

    // Вывод сигналов на контрольные лампы
    controlLampsSignalsOutput(t, dt);
}
