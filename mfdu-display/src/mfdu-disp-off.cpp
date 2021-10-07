#include "mfdu-disp-off.h"



MfduDispOff::MfduDispOff(QLabel *parent)
    : QLabel(parent)
{
    QPixmap pic;
    this->setFrameShape(QLabel::NoFrame);
    if (!pic.load(":/mfdu/mfdu-disp-off")) { return; }
    this->setFixedSize(pic.size());
    this->setPixmap(pic);

}
