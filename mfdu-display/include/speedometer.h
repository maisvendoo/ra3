#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QLabel>


class SArcLimit;
class SArrow;



class Speedometer : public QLabel
{
public:
    Speedometer(QSize _size, QWidget* parent = Q_NULLPTR);

    void setSpeed(float speed);
    void setSpeedLimit(int speedLimit);
    void setGreenDigit(int val);
    void setWhiteDigit(float val);

private:
    SArcLimit* sArcLimit_;
    SArrow* sArrow_;

    QLabel* labSpeedFoo_;
    QLabel* labSpeedFoo2_;
};

#endif // SPEEDOMETER_H
