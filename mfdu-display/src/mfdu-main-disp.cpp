#include "mfdu-main-disp.h"

#include <QPainter>


MfduMainDisp::MfduMainDisp(QLabel *parent)
    : QLabel(parent)
{
    speedometer_ = new Speedometer(QSize(274,264), parent);
    speedometer_->move(261, 147);
//    speedometer_->resize(360, 350);
//    speedometer_->setStyleSheet("border: 1px solid green");



    // блок иконок справа от спидометра
    setBlockIcons_rightSpeedometer_(parent);
    // блок иконок слева от спидометра
    setBlockIcons_leftSpeedometer_(parent);
    // вертикальная шкала тяги/торможения
    verticalScaleBar_ = new VerticalScaleBar(QSize(36, 348), parent);
    verticalScaleBar_->move(51,163);
    //verticalScaleBar_->setStyleSheet("border: 1px solid red");
    // блок нижних параметров
    setBlockDownParameters_(parent);
    // блок иконок сверху от спидометра
    setBlockIcon_topSpeedometer_(parent);


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
    int startX = speedometer_->x() + speedometer_->width() + 13;
    int startY = speedometer_->y() + 5;
    int fooX = 0;
    int fooY = 0;
    int fooDeltaX = 50;
    int fooDeltaY = 52;
    QPixmap pixmap;
    QLabel* labFoo = Q_NULLPTR;

    //
    fooX = startX;
    fooY = startY;

    // 11
    fooNoneAdd_(pixmap, parent, lab110380_, fooX, fooY);
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
    // 12
    fooNoneAdd_(pixmap, parent, labPvu_, fooX, fooY);
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
    // 13
    fooNoneAdd_(pixmap, parent, labEpk_, fooX, fooY);
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
    // 14
    fooNoneAdd_(pixmap, parent, labFier1_, fooX, fooY);
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
    // 15
    fooNoneAdd_(pixmap, parent, labFier2_, fooX, fooY);
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
    // 22
    fooNoneAdd_(pixmap, parent, labPtf_, fooX, fooY);
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
    // 23
    fooNoneAdd_(pixmap, parent, labPzd_, fooX, fooY);
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
    // 24
    fooNoneAdd_(pixmap, parent, labPump_, fooX, fooY);
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
    // 25
    fooNoneAdd_(pixmap, parent, labTpn_, fooX, fooY);
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
    // 31
    fooNoneAdd_(pixmap, parent, labFire_, fooX, fooY);
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
    // 32
    fooNoneAdd_(pixmap, parent, labOz_, fooX, fooY);
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
    // 33
    fooNoneAdd_(pixmap, parent, labDoor_, fooX, fooY);
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
    // 34
    fooNoneAdd_(pixmap, parent, labGenerator_, fooX, fooY);
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
    // 35
    fooNoneAdd_(pixmap, parent, labVip_, fooX, fooY);
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
    // 41
    fooNoneAdd_(pixmap, parent, labIncOzMotor_, fooX, fooY);
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
    // 42
    fooNoneAdd_(pixmap, parent, labDecOzMotor_, fooX, fooY);
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
    // 44
    fooNoneAdd_(pixmap, parent, labWc_, fooX, fooY);
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
    // 45
    fooNoneAdd_(pixmap, parent, labAntyYuz_, fooX, fooY);
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
    // 51
    fooNoneAdd_(pixmap, parent, labRevers_, fooX, fooY);
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
    // 52
    fooNoneAdd_(pixmap, parent, labTransmission_, fooX, fooY);
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
    // 53
    fooNoneAdd_(pixmap, parent, labOilMotor_, fooX, fooY);
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
    // 54
    fooNoneAdd_(pixmap, parent, labPressureOilMotor_, fooX, fooY);
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
    // 55
    fooNoneAdd_(pixmap, parent, labMotor_, fooX, fooY);
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



void MfduMainDisp::setBlockIcons_leftSpeedometer_(QLabel *parent)
{
    int startX = 92;
    int startY = 155;
    int fooX = 0;
    int fooY = 0;

    QPixmap pixmap;

    QLabel* labFoo = new QLabel(parent);
    labFoo->resize(151, 76);
    labFoo->move(startX, startY);
    labFoo->setStyleSheet("border: 1px solid white;"
                          "border-radius: 5px;");

    fooX = startX + 15;
    fooY = startY + 17;
    if (!pixmap.load(":/mfdu/main_motor-compressor-on")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labMotorCompressor_.push_back(labFoo);

    int SIG_MOTOR_COMPRESSOR = 0;
    for (int i = 0, n = labMotorCompressor_.size(); i < n; ++i)
    {
        labMotorCompressor_[i]->setVisible(i == SIG_MOTOR_COMPRESSOR);
    }


    fooX = startX + 74;
    if (!pixmap.load(":/mfdu/main_motor_compressor_1_on")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX, startY + 4);
    labFoo->setPixmap(pixmap);
    labMotorCompressor1_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_motor_compressor_1_off")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX, startY + 4);
    labFoo->setPixmap(pixmap);
    labMotorCompressor1_.push_back(labFoo);

    int SIG_MOTOR_COMPRESSOR_1 = 0;
    for (int i = 0, n = labMotorCompressor1_.size(); i < n; ++i)
    {
        labMotorCompressor1_[i]->setVisible(i == SIG_MOTOR_COMPRESSOR_1);
    }


    fooX += 38;
    if (!pixmap.load(":/mfdu/main_motor_compressor_2_on")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX, startY + 4);
    labFoo->setPixmap(pixmap);
    labMotorCompressor2_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_motor_compressor_2_off")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX, startY + 4);
    labFoo->setPixmap(pixmap);
    labMotorCompressor2_.push_back(labFoo);

    int SIG_MOTOR_COMPRESSOR_2 = 0;
    for (int i = 0, n = labMotorCompressor2_.size(); i < n; ++i)
    {
        labMotorCompressor2_[i]->setVisible(i == SIG_MOTOR_COMPRESSOR_2);
    }


    if (!pixmap.load(":/mfdu/main_attention")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(startX + 2, startY + 104);
    labFoo->setPixmap(pixmap);
    labAttention_.push_back(labFoo);

    int SIG_ATTENTION = 0;
    for (int i = 0, n = labAttention_.size(); i < n; ++i)
    {
        labAttention_[i]->setVisible(i == SIG_ATTENTION);
    }


    if (!pixmap.load(":/mfdu/main_stop")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(startX + 100, startY + 101);
    labFoo->setPixmap(pixmap);
    labStop_.push_back(labFoo);

    int SIG_STOP = 0;
    for (int i = 0, n = labStop_.size(); i < n; ++i)
    {
        labStop_[i]->setVisible(i == SIG_STOP);
    }


    if (!pixmap.load(":/mfdu/main_fwd")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(startX + 60, startY + 82);
    labFoo->setPixmap(pixmap);
    labFwd_.push_back(labFoo);

    int SIG_FWD = 0;
    for (int i = 0, n = labFwd_.size(); i < n; ++i)
    {
        labFwd_[i]->setVisible(i == SIG_FWD);
    }


    if (!pixmap.load(":/mfdu/main_bwd")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(startX + 60, startY + 142);
    labFoo->setPixmap(pixmap);
    labBwd_.push_back(labFoo);

    int SIG_BWD = 0;
    for (int i = 0, n = labBwd_.size(); i < n; ++i)
    {
        labBwd_[i]->setVisible(i == SIG_BWD);
    }


    if (!pixmap.load(":/mfdu/main_bwdfwd")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(startX + 60, startY + 112);
    labFoo->setPixmap(pixmap);
    labBwdFwd_.push_back(labFoo);

    int SIG_BWDFWD = 0;
    for (int i = 0, n = labBwdFwd_.size(); i < n; ++i)
    {
        labBwdFwd_[i]->setVisible(i == SIG_BWDFWD);
    }


    fooX = startX;
    if (!pixmap.load(":/mfdu/main_xren1")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX, startY + 190);
    labFoo->setPixmap(pixmap);
    labXren1_.push_back(labFoo);

    int SIG_XREN1 = 0;
    for (int i = 0, n = labXren1_.size(); i < n; ++i)
    {
        labXren1_[i]->setVisible(i == SIG_XREN1);
    }


    fooX += 52;
    if (!pixmap.load(":/mfdu/main_xren2")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX, startY + 190);
    labFoo->setPixmap(pixmap);
    labXren2_.push_back(labFoo);

    int SIG_XREN2 = 0;
    for (int i = 0, n = labXren2_.size(); i < n; ++i)
    {
        labXren2_[i]->setVisible(i == SIG_XREN2);
    }


    fooX += 52;
    if (!pixmap.load(":/mfdu/main_xren3")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX, startY + 190);
    labFoo->setPixmap(pixmap);
    labXren3_.push_back(labFoo);

    int SIG_XREN3 = 0;
    for (int i = 0, n = labXren3_.size(); i < n; ++i)
    {
        labXren3_[i]->setVisible(i == SIG_XREN3);
    }


}



void MfduMainDisp::setBlockDownParameters_(QLabel *parent)
{
    int fooX = 90;
    int fooY = 438;

    //
    drawLabel_(parent, labPpm_, QPoint(fooX,fooY));
    drawLabel_(parent, labPtm_, QPoint(fooX + 66,fooY));
    drawLabel_(parent, labPtc_max_, QPoint(fooX,fooY + 42));
    drawLabel_(parent, labPtc_min_, QPoint(fooX + 66,fooY + 42));
    drawLabel_(parent, labTkab_, QPoint(fooX + 570,fooY + 10), "00ffff", Qt::AlignRight | Qt::AlignVCenter);
    drawLabel_(parent, labIakb24_, QPoint(fooX + 570,fooY + 46), "ffff00");
    drawLabel_(parent, labIakb110_, QPoint(fooX + 570 + 69,fooY + 46), "ffff00");


    // в отдельный метод (установка значений)
    labPpm_->setText(QString::number(0.0, 'f', 3));
    labPtm_->setText(QString::number(0.5, 'f', 3));
    labPtc_max_->setText(QString::number(0.0, 'f', 3));
    labPtc_min_->setText(QString::number(0.0, 'f', 3));
    labTkab_->setText(QString::number(0, 'f', 1));
    labIakb24_->setText(QString::number(103.7, 'f', 1));
    labIakb110_->setText(QString::number(103.7, 'f', 1));

}



void MfduMainDisp::drawLabel_(QLabel *parent, QLabel *&lab, QPoint pos, QString color, Qt::Alignment align)
{
    lab = new QLabel("0", parent);
    lab->move(pos);
    lab->resize(66, 20);
    lab->setAlignment(Qt::AlignCenter);
    lab->setFont(QFont("Arial", 14, 63));
    lab->setStyleSheet("border: none;"
                       "color: #" + color);
    lab->setAlignment(align);
}



void MfduMainDisp::setBlockIcon_topSpeedometer_(QLabel *parent)
{
    int fooX = 277;
    int fooY = 102;
    int fooDelta12 = 134;


    labT_left_ = new QLabel("0", parent);
    labT_left_->move(fooX + 43, fooY - 27);
    labT_left_->resize(50, 20);
    labT_left_->setAlignment(Qt::AlignCenter);
    labT_left_->setFont(QFont("Arial", 12, 63));
    labT_left_->setStyleSheet("color: white;");
    labT_left_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    labT_left_->setText(QString::number(0.0, 'f', 1));

    labT_right_ = new QLabel("0", parent);
    labT_right_->move(fooX + 43 + fooDelta12, fooY - 27);
    labT_right_->resize(50, 20);
    labT_right_->setAlignment(Qt::AlignCenter);
    labT_right_->setFont(QFont("Arial", 12, 63));
    labT_right_->setStyleSheet("color: white;");
    labT_right_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    labT_right_->setText(QString::number(0.0, 'f', 1));




    QPixmap pixmap;

    QLabel* labFoo = Q_NULLPTR;


    fooNoneAdd2_(pixmap, parent, labCan_right_, fooX + fooDelta12, fooY);
    if (!pixmap.load(":/mfdu/main_can")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labCan_right_.push_back(labFoo);

    int SIG_CAN_RIGHT = 0;
    for (int i = 0, n = labCan_right_.size(); i < n; ++i)
    {
        labCan_right_[i]->setVisible(i == SIG_CAN_RIGHT);
    }




    fooNoneAdd2_(pixmap, parent, labVagonEquipment_left_, fooX, fooY);
    if (!pixmap.load(":/mfdu/main_vagonEquipment_work")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVagonEquipment_left_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_vagonEquipment_warn")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVagonEquipment_left_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_vagonEquipment_error")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVagonEquipment_left_.push_back(labFoo);

    int SIG_VAGON_EQUIPMENT_LEFT = 0;
    for (int i = 0, n = labVagonEquipment_left_.size(); i < n; ++i)
    {
        labVagonEquipment_left_[i]->setVisible(i == SIG_VAGON_EQUIPMENT_LEFT);
    }


    fooNoneAdd2_(pixmap, parent, labVagonEquipment_right_, fooX + fooDelta12, fooY);
    if (!pixmap.load(":/mfdu/main_vagonEquipment_work")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX + fooDelta12,fooY);
    labFoo->setPixmap(pixmap);
    labVagonEquipment_right_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_vagonEquipment_warn")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVagonEquipment_right_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_vagonEquipment_error")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVagonEquipment_right_.push_back(labFoo);

    int SIG_VAGON_EQUIPMENT_RIGHT = 0;
    for (int i = 0, n = labVagonEquipment_right_.size(); i < n; ++i)
    {
        labVagonEquipment_right_[i]->setVisible(i == SIG_VAGON_EQUIPMENT_RIGHT);
    }


    fooX += 36;
    fooNoneAdd2_(pixmap, parent, labPzdMini_left_, fooX, fooY);
    if (!pixmap.load(":/mfdu/main_pzdMini")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPzdMini_left_.push_back(labFoo);

    int SIG_PZD_MINI_LEFT = 0;
    for (int i = 0, n = labPzdMini_left_.size(); i < n; ++i)
    {
        labPzdMini_left_[i]->setVisible(i == SIG_PZD_MINI_LEFT);
    }


    fooNoneAdd2_(pixmap, parent, labPzdMini_right_, fooX + fooDelta12, fooY);
    if (!pixmap.load(":/mfdu/main_pzdMini")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX + fooDelta12,fooY);
    labFoo->setPixmap(pixmap);
    labPzdMini_right_.push_back(labFoo);

    int SIG_PZD_MINI_RIGHT = 0;
    for (int i = 0, n = labPzdMini_right_.size(); i < n; ++i)
    {
        labPzdMini_right_[i]->setVisible(i == SIG_PZD_MINI_RIGHT);
    }


    fooX += 36;
    fooNoneAdd2_(pixmap, parent, labBrakes_left_, fooX, fooY);
    if (!pixmap.load(":/mfdu/main_brakes_gidro")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_left_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_brakes_mix")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_left_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_brakes_ept")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_left_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_brakes_parking")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_left_.push_back(labFoo);

    int SIG_BRAKES_LEFT = 0;
    for (int i = 0, n = labBrakes_left_.size(); i < n; ++i)
    {
        labBrakes_left_[i]->setVisible(i == SIG_BRAKES_LEFT);
    }


    fooNoneAdd2_(pixmap, parent, labBrakes_right_, fooX + fooDelta12, fooY);
    if (!pixmap.load(":/mfdu/main_brakes_gidro")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX + fooDelta12,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_right_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_brakes_mix")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX + fooDelta12,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_right_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_brakes_ept")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX + fooDelta12,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_right_.push_back(labFoo);
    if (!pixmap.load(":/mfdu/main_brakes_parking")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX + fooDelta12,fooY);
    labFoo->setPixmap(pixmap);
    labBrakes_right_.push_back(labFoo);

    int SIG_BRAKES_RIGHT = 0;
    for (int i = 0, n = labBrakes_right_.size(); i < n; ++i)
    {
        labBrakes_right_[i]->setVisible(i == SIG_BRAKES_RIGHT);
    }
}

void MfduMainDisp::fooNoneAdd_(QPixmap &pixmap, QLabel *parent, std::vector<QLabel *> &label, int x, int y)
{
//    if (!pixmap.load(":/mfdu/none")) { return; }
//    QLabel* lab = new QLabel(parent);
//    lab->move(x,y);
//    lab->setPixmap(pixmap);
//    label.push_back(lab);
}

void MfduMainDisp::fooNoneAdd2_(QPixmap &pixmap, QLabel *parent, std::vector<QLabel *> &label, int x, int y)
{
//    if (!pixmap.load(":/mfdu/none35")) { return; }
//    QLabel* lab = new QLabel(parent);
//    lab->move(x,y);
//    lab->setPixmap(pixmap);
//    label.push_back(lab);
}



