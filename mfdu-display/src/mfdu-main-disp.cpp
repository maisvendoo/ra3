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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    lab110380_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPvu_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labEpk_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier1_.push_back(labFoo);
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

    int SIG_FIER_1 = 0; // 111111111111111111111111111111111111111111111111111111111
    for (int i = 0, n = labFier1_.size(); i < n; ++i)
    {
        labFier1_[i]->setVisible(i == SIG_FIER_1);
    }


    fooX += fooDeltaX;
    // 15
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFier2_.push_back(labFoo);
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

    int SIG_FIER_2 = 0; //111111111111111111111111111111111111111111111111111111111111111
    for (int i = 0, n = labFier2_.size(); i < n; ++i)
    {
        labFier2_[i]->setVisible(i == SIG_FIER_2);
    }


    fooX = startX + fooDeltaX;
    fooY += fooDeltaY;
    // 22
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPtf_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPzd_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPump_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labTpn_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labFire_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOz_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labDoor_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labGenerator_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labVip_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labIncOzMotor_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labDecOzMotor_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labWc_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labAntyYuz_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labRevers_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labTransmission_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labOilMotor_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labPressureOilMotor_.push_back(labFoo);
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
    if (!pixmap.load(":/mfdu/none")) { return; }
    labFoo = new QLabel(parent);
    labFoo->move(fooX,fooY);
    labFoo->setPixmap(pixmap);
    labMotor_.push_back(labFoo);
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




