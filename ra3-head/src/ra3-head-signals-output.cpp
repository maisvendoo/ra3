#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::stepSignalsOutput(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Кнопки "БОРТСЕТЬ"
    analogSignal[SIG_BUTTON_ON] = static_cast<float>(tumbler[BUTTON_PWR_ON].getState());
    analogSignal[SIG_BUTTON_OFF] = static_cast<float>(!tumbler[BUTTON_PWR_OFF].getState());

    analogSignal[STRELKA_VOLTMETER110] = static_cast<float>(Ucc / 150.0);
    //analogSignal[STRELKA_VOLTMETER24] = static_cast<float>(0);//bat24->getVoltage() / 30.0);

    // Кнопки пуска и остановки дизелей
    analogSignal[SIG_BUTTON_START] = static_cast<float>(tumbler[BUTTON_START].getState());
    analogSignal[SIG_BUTTON_STOP] = static_cast<float>(tumbler[BUTTON_STOP].getState());


    analogSignal[BLOK_REVERS] = static_cast<float>(mpsu->getOutputData().getReversorDir());

    // Колесные пары
    analogSignal[WHEEL_1] = static_cast<float>(dir * wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[WHEEL_2] = static_cast<float>(dir * wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[WHEEL_3] = static_cast<float>(dir * wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[WHEEL_4] = static_cast<float>(dir * wheel_rotation_angle[3] / 2.0 / Physics::PI);


    analogSignal[LS_G1] = analogSignal[LS_G1_1] =  1.0f;

    mdfuSignalsOutput(t, dt);

    controlLampsSignalsOutput(t, dt);
}
