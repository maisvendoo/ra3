#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::animationSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    // Кнопки "БОРТСЕТЬ"
    analogSignal[SIG_BUTTON_ON] = static_cast<float>(tumbler[BUTTON_PWR_ON].getState());
    analogSignal[SIG_BUTTON_OFF] = static_cast<float>(!tumbler[NO_BUTTON_PWR_OFF].getState());

    analogSignal[STRELKA_VOLTMETER110] = static_cast<float>(Ucc_110 / 150.0);
    analogSignal[STRELKA_VOLTMETER24] = static_cast<float>(Ucc_24 / 30.0);

    analogSignal[STRELKA_P_GR] = static_cast<float>(main_reservoir->getPressure() / 1.2);
    analogSignal[STRELKA_P_TM] = static_cast<float>(brakepipe->getPressure() / 1.2);
    analogSignal[STRELKA_P_TC1] = static_cast<float>(brake_mech[TROLLEY_FWD]->getBCpressure() / 0.6);
    analogSignal[STRELKA_P_TC2] = static_cast<float>(brake_mech[TROLLEY_BWD]->getBCpressure() / 0.6);

    // Кнопки пуска и остановки дизелей
    analogSignal[SIG_BUTTON_START] = static_cast<float>(tumbler[BUTTON_START].getState());
    analogSignal[SIG_BUTTON_STOP] = static_cast<float>(tumbler[BUTTON_STOP].getState());

    analogSignal[SW_PARKING_BRAKE] = static_cast<float>(tumbler[SWITCH_PARKING_BRAKE].getState());

    analogSignal[HANDLE_KRU_091] = kru->getHandlePosition();

    analogSignal[LS_W] = analogSignal[LS_W_1] =  blok->getLampState(WHITE_LAMP);
    analogSignal[LS_R] = analogSignal[LS_R_1] =  blok->getLampState(RED_LAMP);
    analogSignal[LS_RY] = analogSignal[LS_RY_1] =  blok->getLampState(RED_YELLOW_LAMP);
    analogSignal[LS_Y] = analogSignal[LS_Y_1] =  blok->getLampState(YELLOW_LAMP);
    analogSignal[LS_G1] = analogSignal[LS_G1_1] =  blok->getLampState(GREEN_LAMP1);
    analogSignal[LS_G2] = analogSignal[LS_G2_1] =  blok->getLampState(GREEN_LAMP2);
    analogSignal[LS_G3] = analogSignal[LS_G3_1] =  blok->getLampState(GREEN_LAMP3);
    analogSignal[LS_G4] = analogSignal[LS_G4_1] =  blok->getLampState(GREEN_LAMP4);

    // Свисток и тифон
    analogSignal[SIG_BUTTON_WHISTLE] = static_cast<float>(horn->isSvistok());
    analogSignal[SIG_BUTTON_TYPHON] = static_cast<float>(horn->isTifon());

    analogSignal[DRIVER_CONTROLLER] = km->getHandlePosition();
    analogSignal[DIRECTION_OF_MOVEMENT] = km->getReversHandlePos();

    analogSignal[EMERGENCY_STOP_BUTTON] = static_cast<float>(emerg_brake_valve->isEmergencyBrake());

    analogSignal[RB] = static_cast<float>(tumbler[BUTTON_RB].getState());
    analogSignal[RBS] = static_cast<float>(tumbler[BUTTON_RBS].getState());

    analogSignal[EPK] = static_cast<float>(epk->getStateKey());

    analogSignal[SPEED_SELECTION] = static_cast<float>(tumbler[BUTTON_SPEED_SELECTION].getState());
    analogSignal[SPEED_PLUS] = static_cast<float>(tumbler[BUTTON_SPEED_PLUS].getState());
    analogSignal[SPEED_MINUS] = static_cast<float>(tumbler[BUTTON_SPEED_MINUS].getState());
    analogSignal[HOLD_SPEED] = static_cast<float>(button_speed_hold.getState());


    // Карданы
    analogSignal[SHAFT_1] = static_cast<float>( ip1 * wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[SHAFT_2] = static_cast<float>(-ip1 * ip2 * wheel_rotation_angle[0] / 2.0 / Physics::PI);

    // Колесные пары
    analogSignal[WHEEL_1] = static_cast<float>(wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[WHEEL_2] = static_cast<float>(wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[WHEEL_3] = static_cast<float>(wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[WHEEL_4] = static_cast<float>(wheel_rotation_angle[3] / 2.0 / Physics::PI);
}
