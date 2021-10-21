#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::animationSignalsOutput(double t, double dt)
{
    // Кнопки "БОРТСЕТЬ"
    analogSignal[SIG_BUTTON_ON] = static_cast<float>(tumbler[BUTTON_PWR_ON].getState());
    analogSignal[SIG_BUTTON_OFF] = static_cast<float>(!tumbler[BUTTON_PWR_OFF].getState());

    analogSignal[STRELKA_VOLTMETER110] = static_cast<float>(Ucc / 150.0);
    analogSignal[STRELKA_VOLTMETER24] = static_cast<float>(bat24->getVoltage() / 30.0);

    analogSignal[STRELKA_P_GR] = static_cast<float>(main_res->getPressure() / 1.2);
    analogSignal[STRELKA_P_TM] = static_cast<float>(pTM / 1.2);
    analogSignal[STRELKA_P_TC1] = static_cast<float>(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure() / 0.6);
    analogSignal[STRELKA_P_TC2] = static_cast<float>(brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure() / 0.6);

    // Кнопки пуска и остановки дизелей
    analogSignal[SIG_BUTTON_START] = static_cast<float>(tumbler[BUTTON_START].getState());
    analogSignal[SIG_BUTTON_STOP] = static_cast<float>(tumbler[BUTTON_STOP].getState());

    analogSignal[SW_PARKING_BRAKE] = static_cast<float>(tumbler[SWITCH_PARKING_BRAKE].getState());

    analogSignal[HANDLE_KRU_091] = kru->getHandlePosition();

    analogSignal[LS_G1] = analogSignal[LS_G1_1] =  1.0f;

    // Свисток и тифон
    analogSignal[SIG_BUTTON_WHISTLE] = static_cast<float>(horn->isSvistok());
    analogSignal[SIG_BUTTON_TYPHON] = static_cast<float>(horn->isTifon());

    analogSignal[DRIVER_CONTROLLER] = km->getHandlePosition();

    // Колесные пары
    analogSignal[WHEEL_1] = static_cast<float>(dir * wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[WHEEL_2] = static_cast<float>(dir * wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[WHEEL_3] = static_cast<float>(dir * wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[WHEEL_4] = static_cast<float>(dir * wheel_rotation_angle[3] / 2.0 / Physics::PI);
}
