#include "speedometer.h"

#include "s-arc-limit.h"
#include "s-arrow.h"



Speedometer::Speedometer(QSize _size, QWidget *parent)
    : QLabel(parent)
{
    this->resize(_size);


    sArcLimit_ = new SArcLimit(this);
    //sArcLimit_->setVal(50);

    //
    labSpeedFoo_ = new QLabel("45", this);
    labSpeedFoo_->setGeometry(this->width()/2.0 - 30, this->height() - 82, 60,60);
    labSpeedFoo_->setAlignment(Qt::AlignCenter);
    labSpeedFoo_->setStyleSheet("color: green");
    labSpeedFoo_->setFont(QFont("Arial", 18, 63));

    labSpeedFoo2_ = new QLabel("12.3", this);
    labSpeedFoo2_->setGeometry(this->width()/2.0 - 30, this->height() - 46, 60,60);
    labSpeedFoo2_->setAlignment(Qt::AlignCenter);
    labSpeedFoo2_->setStyleSheet("color: white");
    labSpeedFoo2_->setFont(QFont("Arial", 18, 57));


    //
    sArrow_ = new SArrow(/*_size*/this->size(), 0, this);
    //sArrow_->setStyleSheet("border: 2px solid red;");
    //sArrow_->setVal(0.00 + 30.0);

}
