#ifndef MFDUMAINDISP_H
#define MFDUMAINDISP_H

#include    <QLabel>

#include    "ra3-head-signals.h"

#include    "display-types.h"
#include    "trigger-label.h"

class Speedometer;
class VerticalScaleBar;



class MfduMainDisp : public QLabel
{
public:
    MfduMainDisp(QLabel* parent = Q_NULLPTR);

    void updateData(display_signals_t input_signals);


private:
    Speedometer* speedometer_;


    // блок иконок справа от спидометра
    void setBlockIcons_rightSpeedometer_(QLabel* parent);
    int labMotor_state;
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

    // блок иконок слева от спидометра
    void setBlockIcons_leftSpeedometer_(QLabel* parent);
    int labMotorCompressor_state;
    std::vector<QLabel*> labMotorCompressor_;
    std::vector<QLabel*> labMkFrame_;
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labMotorCompressorOn_;
    std::array<TriggerLabel*, MAX_TRAIN_SIZE> labMotorCompressorNum_;
    std::vector<QLabel*> labAttention_;
    std::vector<QLabel*> labStop_;
    std::vector<QLabel*> labFwd_;
    std::vector<QLabel*> labBwd_;
    std::vector<QLabel*> labBwdFwd_;
    std::vector<QLabel*> labXren1_;
    std::vector<QLabel*> labXren2_;
    std::vector<QLabel*> labXren3_;

    // Вертикальная шкала тяги/торможения
    VerticalScaleBar* verticalScaleBar_;

    // блок нижних параметров
    void setBlockDownParameters_(QLabel* parent);
    void drawLabel_(QLabel* parent, TriggerLabel* &lab, QPoint pos, QString color = "00ffff",
                    Qt::Alignment align = Qt::AlignCenter);
    TriggerLabel* labPpm_;
    TriggerLabel* labPtm_;
    TriggerLabel* labPtc_max_;
    TriggerLabel* labPtc_min_;
    TriggerLabel* labTkab_;
    TriggerLabel* labIakb24_;
    TriggerLabel* labIakb110_;

    // блок иконок сверху от спидометра
    TriggerLabel* labNoHead_;
    void setBlockIcon_topSpeedometer_(QLabel* parent);
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labTrainUnit_;
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labDoorR_;
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labDoorL_;
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labCAN_;
    std::array<TriggerLabel*, MAX_TRAIN_SIZE> labNo1_;
    std::array<TriggerLabel*, MAX_TRAIN_SIZE> labNo2_;
    std::array<TriggerLabel*, MAX_TRAIN_SIZE> labT_;
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labVagonEquipment_;
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labDiesel_;
    std::array<std::vector<QLabel*>, MAX_TRAIN_SIZE> labBrakes_;

    // Сообщения об ошибках
    void setErrosMsgBox_(QLabel *parent);
    std::vector<QLabel *> labErros_;

    void setNeededIcon_(std::vector<QLabel*> &vec_lab, int val);
    void setNeededIcon_(std::vector<QLabel*> &vec_lab, int val, int x, int y);
};

#endif // MFDUMAINDISP_H
