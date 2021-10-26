#include "mfdu-disp-off.h"



MfduDispOff::MfduDispOff(QLabel *parent)
    : QLabel(parent)
{
    QPixmap pic;
    this->setFrameShape(QLabel::NoFrame);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));
    this->move(0, 0);
    this->resize(800, 588);
}
