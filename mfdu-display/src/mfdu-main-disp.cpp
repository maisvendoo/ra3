#include "mfdu-main-disp.h"



MfduMainDisp::MfduMainDisp(QLabel *parent)
    : QLabel(parent)
{
    speedometer_ = new Speedometer(QSize(348,342), parent);
    speedometer_->move(325, 187);
//    speedometer_->resize(360, 350);
    //speedometer_->setStyleSheet("border: 4px solid green");



    // блок иконок справа от спидометра
    setBlockIcons_rightSpeedometer_(parent);







    hBar_ = new HorizontBar(QSize(202, 25), parent);
//    hBar_->move(50, 150);

}



void MfduMainDisp::updateData(display_signals_t input_signals)
{

}



void MfduMainDisp::setDispVisible(bool flag)
{
    speedometer_->setVisible(flag);
}



void MfduMainDisp::setBlockIcons_rightSpeedometer_(QLabel *parent)
{
    int startX = speedometer_->x() + speedometer_->width() + 15;
    int startY = speedometer_->y() + 5;
    int fooX = 0;
    int fooY = 0;
    int fooDeltaX = 65;
    int fooDeltaY = 70;
    QPixmap pixmap;
    QLabel* labFoo = Q_NULLPTR;

    //
    fooX = startX;
    fooY = startY;

    //
    if (!pixmap.load(":/mfdu/main_110380_380")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    lab110380_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_110380_110")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    lab110380_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_110380_380110")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    lab110380_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_110380_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    lab110380_.push_back(labFoo);

    int SIG_ACTIVE_CHARGE = 0;
    for (int i = 0, n = lab110380_.size(); i < n; ++i)
    {
        lab110380_[i]->setVisible(i == SIG_ACTIVE_CHARGE);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_pvu")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPvu_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pvu_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPvu_.push_back(labFoo);

    int SIG_PVU = 0;
    for (int i = 0, n = labPvu_.size(); i < n; ++i)
    {
        labPvu_[i]->setVisible(i == SIG_PVU);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_epk_on")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labEpk_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_epk_off")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labEpk_.push_back(labFoo);

    int SIG_EPK = 0;
    for (int i = 0, n = labEpk_.size(); i < n; ++i)
    {
        labEpk_[i]->setVisible(i == SIG_EPK);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_fier1_noSignals")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier1_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_fier1_maneuver")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier1_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_fier1_redFiers")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier1_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_fier1_2signals")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier1_.push_back(labFoo);

    int SIG_FIER_1 = 1;
    for (int i = 0, n = labFier1_.size(); i < n; ++i)
    {
        labFier1_[i]->setVisible(i == SIG_FIER_1);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_fier2_noSignals")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier2_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_fier2_whiteFiers")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier2_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_fier2_whiteRedFiers")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier2_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_fier2_2signals")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier2_.push_back(labFoo);

    int SIG_FIER_2 = 1;
    for (int i = 0, n = labFier2_.size(); i < n; ++i)
    {
        labFier2_[i]->setVisible(i == SIG_FIER_2);
    }


    fooX = startX + fooDeltaX;
    fooY += fooDeltaY;
    //
    if (!pixmap.load(":/mfdu/main_ptf")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPtf_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_ptf_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPtf_.push_back(labFoo);

    int SIG_PTF = 0;
    for (int i = 0, n = labPtf_.size(); i < n; ++i)
    {
        labPtf_[i]->setVisible(i == SIG_PTF);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_pzd")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPzd_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pzd_burn")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPzd_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pzd_fail")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPzd_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pzd_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPzd_.push_back(labFoo);

    int SIG_PZD = 0;
    for (int i = 0, n = labPzd_.size(); i < n; ++i)
    {
        labPzd_[i]->setVisible(i == SIG_PZD);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_pump")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPump_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pump_fail")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPump_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pump_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPump_.push_back(labFoo);

    int SIG_PUMP = 0;
    for (int i = 0, n = labPump_.size(); i < n; ++i)
    {
        labPump_[i]->setVisible(i == SIG_PUMP);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_tpn")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labTpn_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_tpn_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labTpn_.push_back(labFoo);

    int SIG_TPN = 0;
    for (int i = 0, n = labTpn_.size(); i < n; ++i)
    {
        labTpn_[i]->setVisible(i == SIG_TPN);
    }


    fooX = startX;
    fooY += fooDeltaY;
    //
    if (!pixmap.load(":/mfdu/main_fire")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFire_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_fire_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFire_.push_back(labFoo);

    int SIG_FIRE = 0;
    for (int i = 0, n = labFire_.size(); i < n; ++i)
    {
        labFire_[i]->setVisible(i == SIG_FIRE);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_oz_1")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOz_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_oz_2")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOz_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_oz_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOz_.push_back(labFoo);

    int SIG_OZ = 0;
    for (int i = 0, n = labOz_.size(); i < n; ++i)
    {
        labOz_[i]->setVisible(i == SIG_OZ);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_door")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labDoor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_door_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labDoor_.push_back(labFoo);

    int SIG_DOOR = 0;
    for (int i = 0, n = labDoor_.size(); i < n; ++i)
    {
        labDoor_[i]->setVisible(i == SIG_DOOR);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_generator")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labGenerator_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_generator_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labGenerator_.push_back(labFoo);

    int SIG_GENERATOR = 0;
    for (int i = 0, n = labGenerator_.size(); i < n; ++i)
    {
        labGenerator_[i]->setVisible(i == SIG_GENERATOR);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_vip")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVip_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_vip_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVip_.push_back(labFoo);

    int SIG_VIP = 0;
    for (int i = 0, n = labVip_.size(); i < n; ++i)
    {
        labVip_[i]->setVisible(i == SIG_VIP);
    }


    fooX = startX;
    fooY += fooDeltaY;
    //
    if (!pixmap.load(":/mfdu/main_incOzMotor_1")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labIncOzMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_incOzMotor_2")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labIncOzMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_incOzMotor_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labIncOzMotor_.push_back(labFoo);

    int SIG_INC_OZ_MOTOR = 0;
    for (int i = 0, n = labIncOzMotor_.size(); i < n; ++i)
    {
        labIncOzMotor_[i]->setVisible(i == SIG_INC_OZ_MOTOR);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_decOzMotor_1")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labDecOzMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_decOzMotor_2")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labDecOzMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_decOzMotor_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labDecOzMotor_.push_back(labFoo);

    int SIG_DEC_OZ_MOTOR = 0;
    for (int i = 0, n = labDecOzMotor_.size(); i < n; ++i)
    {
        labDecOzMotor_[i]->setVisible(i == SIG_DEC_OZ_MOTOR);
    }


    fooX += fooDeltaX*2;
    //
    if (!pixmap.load(":/mfdu/main_wc")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labWc_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_wc_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labWc_.push_back(labFoo);

    int SIG_WC = 0;
    for (int i = 0, n = labWc_.size(); i < n; ++i)
    {
        labWc_[i]->setVisible(i == SIG_WC);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_antyYuz_work")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labAntyYuz_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_antyYuz_fail")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labAntyYuz_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_antyYuz_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labAntyYuz_.push_back(labFoo);

    int SIG_ANTY_YUZ = 0;
    for (int i = 0, n = labAntyYuz_.size(); i < n; ++i)
    {
        labAntyYuz_[i]->setVisible(i == SIG_ANTY_YUZ);
    }


    fooX = startX;
    fooY += fooDeltaY;
    //
    if (!pixmap.load(":/mfdu/main_revers")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labRevers_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_revers_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labRevers_.push_back(labFoo);

    int SIG_REVERS = 0;
    for (int i = 0, n = labRevers_.size(); i < n; ++i)
    {
        labRevers_[i]->setVisible(i == SIG_REVERS);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_transmission")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labTransmission_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_transmission_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labTransmission_.push_back(labFoo);

    int SIG_TRANSMISSION = 0;
    for (int i = 0, n = labTransmission_.size(); i < n; ++i)
    {
        labTransmission_[i]->setVisible(i == SIG_TRANSMISSION);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_oilMotor_up")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOilMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_oilMotor_down")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOilMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_oilMotor_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOilMotor_.push_back(labFoo);

    int SIG_OIL_MOTOR = 0;
    for (int i = 0, n = labOilMotor_.size(); i < n; ++i)
    {
        labOilMotor_[i]->setVisible(i == SIG_OIL_MOTOR);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_pressureOilMotor_up")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPressureOilMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pressureOilMotor_down")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPressureOilMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_pressureOilMotor_noActive")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPressureOilMotor_.push_back(labFoo);

    int SIG_PRESSURE_OIL_MOTOR = 0;
    for (int i = 0, n = labPressureOilMotor_.size(); i < n; ++i)
    {
        labPressureOilMotor_[i]->setVisible(i == SIG_PRESSURE_OIL_MOTOR);
    }


    fooX += fooDeltaX;
    //
    if (!pixmap.load(":/mfdu/main_motor_work")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_motor_warn")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labMotor_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_motor_error")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labMotor_.push_back(labFoo);

    int SIG_MOTOR = 0;
    for (int i = 0, n = labMotor_.size(); i < n; ++i)
    {
        labMotor_[i]->setVisible(i == SIG_MOTOR);
    }




}


