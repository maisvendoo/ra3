#ifndef MFDUMAINDISP_H
#define MFDUMAINDISP_H

#include    "display.h"


#include    <QLabel>

#include "speedometer.h"
#include "horizont-bar.h"



class MfduMainDisp : public QLabel
{
public:
    MfduMainDisp(QLabel* parent = Q_NULLPTR);

    void updateData(display_signals_t input_signals);

    void setDispVisible(bool flag = true);


private:
    Speedometer* speedometer_;


    void setBlockIcons_rightSpeedometer_(QLabel* parent);
    std::vector<QLabel*> lab110380_;
    std::vector<QLabel*> labPvu_;
    std::vector<QLabel*> labEpk_;
    std::vector<QLabel*> labFier1_;
    std::vector<QLabel*> labFier2_;
    std::vector<QLabel*> labPtf_;
    std::vector<QLabel*> labPzd_;
    std::vector<QLabel*> labPump_;
    std::vector<QLabel*> labTpn_;
    std::vector<QLabel*> labFire_;
    std::vector<QLabel*> labOz_;
    std::vector<QLabel*> labDoor_;
    std::vector<QLabel*> labGenerator_;
    std::vector<QLabel*> labVip_;
    std::vector<QLabel*> labIncOzMotor_;
    std::vector<QLabel*> labDecOzMotor_;
    std::vector<QLabel*> labWc_;
    std::vector<QLabel*> labAntyYuz_;
    std::vector<QLabel*> labRevers_;
    std::vector<QLabel*> labTransmission_;
    std::vector<QLabel*> labOilMotor_;
    std::vector<QLabel*> labPressureOilMotor_;
    std::vector<QLabel*> labMotor_;



    HorizontBar* hBar_;

};

#endif // MFDUMAINDISP_H
