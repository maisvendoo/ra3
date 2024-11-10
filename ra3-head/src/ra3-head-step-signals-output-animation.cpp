#include    "ra3-head.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::animationSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    // === АНИМАЦИИ КУЗОВА ===
    // Колесные пары
    analogSignal[WHEELSET_1] = static_cast<float>(wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[WHEELSET_2] = static_cast<float>(wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[WHEELSET_3] = static_cast<float>(wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[WHEELSET_4] = static_cast<float>(wheel_rotation_angle[3] / 2.0 / Physics::PI);

    // Карданные валы
    analogSignal[DRIVESHAFT] = static_cast<float>(-ip1 * ip2 * wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[INTERAXLE_DRIVESHAFT] = static_cast<float>( ip1 * wheel_rotation_angle[0] / 2.0 / Physics::PI);

    // Двери
    analogSignal[DOOR_L_WARNING_INDICATOR] = door_L->getWarningSignal();
    analogSignal[DOOR_L_STEP] = door_L->getStepState();
    analogSignal[DOOR_L_SKID] = door_L->getDoorSkidState();
    analogSignal[DOOR_L_LEFT] = door_L->getDoorState();
    analogSignal[DOOR_L_RIGHT] = door_L->getDoorState();
    analogSignal[DOOR_R_WARNING_INDICATOR] = door_R->getWarningSignal();
    analogSignal[DOOR_R_STEP] = door_R->getStepState();
    analogSignal[DOOR_R_SKID] = door_R->getDoorSkidState();
    analogSignal[DOOR_R_LEFT] = door_R->getDoorState();
    analogSignal[DOOR_R_RIGHT] = door_R->getDoorState();

    // === АНИМАЦИИ КАБИНЫ ===
    // Включаем подсветку кнопок в активной кабине
    bool is_active = active_cab_relay->getContactState(1);

    // Панель органов управления ПОУ
    // Кнопки "БОРТСЕТЬ"
    analogSignal[BUTTON_BOARDNET_ON] = static_cast<float>(tumbler[IS_BUTTON_PWR_ON].getState());
    analogSignal[BUTTON_BOARDNET_OFF] = static_cast<float>(!tumbler[NO_BUTTON_PWR_OFF].getState());
    //analogSignal[BUTTON_TRANSIT] = 0.0f;
    //analogSignal[BUTTON_TRANSIT_PROTECTIVE_COVER] = 0.0f;
    //analogSignal[BUTTON_TRANSIT_INDICATOR] = 0.0f;
    //analogSignal[TOOGLE_EMERGENCY_CONTROL] = 0.0f;
    //analogSignal[BUTTON_POWER_SUPPLY] = 0.0f;
    //analogSignal[BUTTON_POWER_SUPPLY_PROTECTIVE_COVER] = 0.0f;
    //analogSignal[BUTTON_POWER_SUPPLY_INDICATOR] = 0.0f;
    analogSignal[ARROW_VOLTMETER_24V] = static_cast<float>(Ucc_110 / 150.0);
    analogSignal[ARROW_VOLTMETER_110V] = static_cast<float>(Ucc_24 / 30.0);
    analogSignal[TOOGLE_TROLLEY_LIGHTING] = 0.0f;
    analogSignal[TOOGLE_PZD] = 0.0f;
    analogSignal[TOOGLE_RESERV] = 0.0f;
    analogSignal[TOOGLE_GLASS_HEATING] = 0.0f;
    analogSignal[TOOGLE_SALON_CLIMATE_CONTROL] = 0.0f;
    analogSignal[TOOGLE_CABINE_VENTILATION] = 0.0f;
    analogSignal[TOOGLE_CABINE_CONDITIONER] = 0.0f;
    analogSignal[TOOGLE_CABINE_HEATER] = 0.0f;
    //analogSignal[CONTROL_GEAR_CABINE_TEMPERATURE] = 0.0f;

    // Блок защиты и коммутации БЗК
    analogSignal[AZV_1_HEATING_TF1_MTU] = 1.0f;
    analogSignal[AZV_2_HEATING_TF2_MTU] = 1.0f;
    analogSignal[AZV_3_CONTROL_MTU] = 1.0f;
    analogSignal[AZV_4_CONTROL_GMP] = 1.0f;
    analogSignal[AZV_5_STARTER] = 1.0f;
    analogSignal[AZV_6_GENERATOR_POWER_SUPPLY] = 1.0f;
    analogSignal[AZV_7_PUMP] = 1.0f;
    analogSignal[AZV_8_PZD1] = 1.0f;
    analogSignal[AZV_9_PZD2] = 1.0f;
    analogSignal[AZV_10_BREAKING] = 1.0f;
    analogSignal[AZV_11_110V_SU] = 1.0f;
    analogSignal[AZV_12_CONSUMERS_SU_PK] = 1.0f;
    analogSignal[AZV_13_CONTROL_PANEL_MFDU] = 1.0f;
    analogSignal[AZV_14_24V_CONTROL_CIRCUITS] = 1.0f;
    analogSignal[AZV_15_BLOK] = 1.0f;
    analogSignal[AZV_16_KVARC] = 1.0f;
    analogSignal[AZV_17_CIK_P] = 1.0f;
    analogSignal[AZV_18_CIK_L] = 1.0f;
    analogSignal[AZV_19_BOARDNET] = 1.0f;
    analogSignal[AZV_20_CONTROL_CIRCUITS] = 1.0f;
    analogSignal[AZV_21_HEADLIGHT] = 1.0f;
    analogSignal[AZV_22_LANTERNS] = 1.0f;
    analogSignal[AZV_23_RADIO_STATION] = 1.0f;
    analogSignal[AZV_24_ADD_EQUIPMENT] = 1.0f;
    analogSignal[AZV_25_MIRRORS] = 1.0f;
    analogSignal[AZV_26_WINDSCREEN_WIPERS] = 1.0f;
    analogSignal[AZV_27_SOCKETS_24V] = 1.0f;
    analogSignal[AZV_28_CONTROL_DOORS] = 1.0f;
    analogSignal[AZV_29_ASOTP] = 1.0f;
    analogSignal[AZV_30_RESERVE1] = 0.0f;
    analogSignal[AZV_31_RESERVE2] = 0.0f;

    // Органы управления
    analogSignal[TRACTION_CONTROLLER_HANDLE] = km->getHandlePosition();
    analogSignal[BRAKES_CONTROLLER_HANDLE] = kru->getHandlePosition();
    analogSignal[BUTTON_EMERGENCY_STOP] = static_cast<float>(emerg_brake_valve->isEmergencyBrake());
    analogSignal[BUTTON_RBS] = static_cast<float>(tumbler[IS_BUTTON_RBS].getState());
    analogSignal[BUTTON_RB] = static_cast<float>(tumbler[IS_BUTTON_RB].getState());
    analogSignal[TOOGLE_EPK] = static_cast<float>(tumbler[IS_KEY_EPK].getState());

    // Панель управления ПУ-1
    analogSignal[BUTTON_EMERGENCY_CONTROL] = 0.0f;
    //analogSignal[BUTTON_EMERGENCY_CONTROL_PROTECTIVE_COVER] = 0.0f;
    analogSignal[BUTTON_DIESEL_START] = static_cast<float>(tumbler[IS_BUTTON_START].getState());
    analogSignal[BUTTON_DISEL_STOP] = static_cast<float>(tumbler[IS_BUTTON_STOP].getState());
    //analogSignal[BUTTON_REPEAT] = 0.0f;
    analogSignal[TOOGLE_BUFFERLIGHTS_MANEUROUS_OR_MOTION] = 0.0f;
    analogSignal[TOOGLE_BUFFERLIGHTS_WHITE_OR_REDWHITE] = 0.0f;
    analogSignal[TOOGLE_DIRECTION_OF_MOVEMENT] = km->getReversHandlePos();
    analogSignal[BUTTON_PLAY_RECORD] = 0.0f;
    analogSignal[BUTTON_MICROPHONE] = 0.0f;

    // Панель управления ПУ-2
    analogSignal[TOOGLE_WINDSCREEN_WIPERS] = 0.0f;
    analogSignal[BUTTON_WINDSCREEN_WASHERS] = 0.0f;
    analogSignal[BUTTON_WHISTLE_M] = static_cast<float>(horn->isSvistok());
    analogSignal[BUTTON_TYPHON_M] = static_cast<float>(horn->isTifon());

    // Панель управления ПУ-3
    analogSignal[BUTTON_RBP] = 0.0f;
    analogSignal[BUTTON_WHISTLE_MP] = 0.0f;
    analogSignal[BUTTON_TYPHON_MP] = 0.0f;

    // Панель управления ПУ-4
    // Верхний ряд
    analogSignal[BUTTON_OPEN_L_DOORS] = static_cast<float>(tumbler[IS_BUTTON_DOOR_L_OPEN].getState());
    analogSignal[BUTTON_OPEN_L_DOORS_INDICATOR] = static_cast<float>(is_active && (door_L->getDoorControlState() > 1));
    analogSignal[BUTTON_CLOSE_L_DOORS] = static_cast<float>(tumbler[IS_FIXED_DOOR_L_CLOSE].getState()) * 0.5f +
                                         static_cast<float>(tumbler[IS_BUTTON_DOOR_L_CLOSE].getState()) * 0.5f;
    analogSignal[BUTTON_CLOSE_L_DOORS_INDICATOR] = static_cast<float>(is_active && (tumbler[IS_FIXED_DOOR_L_CLOSE].getState()));
    //analogSignal[BUTTON_SAND] = sand_system->isSandDelivery();
    analogSignal[TOOGLE_SALON_LIGHTING] = 0.0f;
    analogSignal[BUTTON_STEPS] = static_cast<float>(tumbler[IS_BUTTON_STEP].getState());
    analogSignal[BUTTON_STEPS_INDICATOR] = static_cast<float>(is_active && tumbler[IS_BUTTON_STEP].getState());
    analogSignal[BUTTON_OPEN_R_DOORS] = static_cast<float>(tumbler[IS_BUTTON_DOOR_R_OPEN].getState());
    analogSignal[BUTTON_OPEN_R_DOORS_INDICATOR] = static_cast<float>(is_active && (door_R->getDoorControlState() > 1));
    analogSignal[BUTTON_CLOSE_R_DOORS] = static_cast<float>(tumbler[IS_FIXED_DOOR_R_CLOSE].getState()) * 0.5f +
                                         static_cast<float>(tumbler[IS_BUTTON_DOOR_R_CLOSE].getState()) * 0.5f;
    analogSignal[BUTTON_CLOSE_R_DOORS_INDICATOR] = static_cast<float>(is_active && (tumbler[IS_FIXED_DOOR_R_CLOSE].getState()));
    // Нижний ряд
    analogSignal[BUTTON_SPEED_MAINTAINING] = static_cast<float>(tumbler[IS_FIXED_SPEED_HOLD].getState()) * 0.5f +
                                            static_cast<float>(tumbler[IS_BUTTON_SPEED_HOLD].getState()) * 0.5f;
    analogSignal[BUTTON_SPEED_MAINTAINING_INDICATOR] = static_cast<float>(mpsu->getOutputData().is_speed_hold_ON);
    analogSignal[BUTTON_SPEED_SELECTION] = static_cast<float>(tumbler[IS_BUTTON_SPEED_SELECTION].getState());
    analogSignal[BUTTON_SPEED_PLUS] = static_cast<float>(tumbler[IS_BUTTON_SPEED_PLUS].getState());
    analogSignal[BUTTON_SPEED_MINUS] = static_cast<float>(tumbler[IS_BUTTON_SPEED_MINUS].getState());

    // Панель управления ПУ-5
    analogSignal[TOOGLE_CONTROL_PANEL_LIGHTING_MP] = 0.0f;
    //analogSignal[CONTROL_GEAR_CONTROL_PANEL_BRIGTNESS_MP] = 0.0f;

    // Панель управления ПУ-6
    analogSignal[TOOGLE_CABINE_LIGHTING] = 0.0f;
    analogSignal[TOOGLE_CONTROL_PANEL_LIGHTING_M] = 0.0f;
    //analogSignal[CONTROL_GEAR_CONTROL_PANEL_BRIGTNESS_M] = 0.0f;

    // Лампы локомотивного светофора на блоке индикации БИ-2
    analogSignal[INDICATOR_LS_W_MP] = blok->getLampState(WHITE_LAMP);
    analogSignal[INDICATOR_LS_R_MP] = blok->getLampState(RED_LAMP);
    analogSignal[INDICATOR_LS_RY_MP] = blok->getLampState(RED_YELLOW_LAMP);
    analogSignal[INDICATOR_LS_Y_MP] = blok->getLampState(YELLOW_LAMP);
    analogSignal[INDICATOR_LS_G1_MP] = blok->getLampState(GREEN_LAMP1);
    analogSignal[INDICATOR_LS_G2_MP] = blok->getLampState(GREEN_LAMP2);
    analogSignal[INDICATOR_LS_G3_MP] = blok->getLampState(GREEN_LAMP3);
    analogSignal[INDICATOR_LS_G4_MP] = blok->getLampState(GREEN_LAMP4);

    // Лампы локомотивного светофора на блоке индикации БИ-4
    analogSignal[INDICATOR_LS_W_M] = blok->getLampState(WHITE_LAMP);
    analogSignal[INDICATOR_LS_R_M] = blok->getLampState(RED_LAMP);
    analogSignal[INDICATOR_LS_RY_M] = blok->getLampState(RED_YELLOW_LAMP);
    analogSignal[INDICATOR_LS_Y_M] = blok->getLampState(YELLOW_LAMP);
    analogSignal[INDICATOR_LS_G1_M] = blok->getLampState(GREEN_LAMP1);
    analogSignal[INDICATOR_LS_G2_M] = blok->getLampState(GREEN_LAMP2);
    analogSignal[INDICATOR_LS_G3_M] = blok->getLampState(GREEN_LAMP3);
    analogSignal[INDICATOR_LS_G4_M] = blok->getLampState(GREEN_LAMP4);

    // Блок индикации БИ-5
    analogSignal[ARROW_FL_PRESSURE] = static_cast<float>(main_reservoir->getPressure() / 1.2);
    analogSignal[ARROW_BP_PRESSURE] = static_cast<float>(brakepipe->getPressure() / 1.2);
    analogSignal[ARROW_BC_FWD_PRESSURE] = static_cast<float>(brake_mech[TROLLEY_FWD]->getBCpressure() / 0.6);
    analogSignal[ARROW_BC_BWD_PRESSURE] = static_cast<float>(brake_mech[TROLLEY_BWD]->getBCpressure() / 0.6);
    analogSignal[TOOGLE_PARKING_BRAKE] = static_cast<float>(tumbler[IS_SWITCH_PARKING_BRAKE].getState());
    analogSignal[BUTTON_MIRRORS_HEATING] = 0.0f;
    analogSignal[BUTTON_MIRRORS_HEATING_INDICATOR] = 0.0f;
    //analogSignal[JOYSTIK_MIRROR_SELECTION] = 0.0f;
    //analogSignal[JOYSTIK_MIRROR_HORIZONTAL_AXIS] = 0.0f;
    //analogSignal[JOYSTIK_MIRROR_VERTICAL_AXIS] = 0.0f;
    //analogSignal[CONTROL_GEAR_MANOMETER_BRIGTHNESS] = 0.0f;
}
