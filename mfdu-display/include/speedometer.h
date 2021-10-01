#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QLabel>


class SArcLimit;
class SArrow;



class Speedometer : public QLabel
{
public:
    Speedometer(QSize _size, QWidget* parent = Q_NULLPTR);

private:
    SArcLimit* sArcLimit_;
    SArrow* sArrow_;

    QLabel* labSpeedFoo_;
    QLabel* labSpeedFoo2_;
};

#endif // SPEEDOMETER_H
