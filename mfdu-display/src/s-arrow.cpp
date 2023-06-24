#include "s-arrow.h"

#include    <QPainter>
#include    <QtCore/qmath.h>



SArrow::SArrow(int otstupSverhu, QWidget *parent)
    : QLabel(parent)
    , maxVal_(140)
{
    this->resize(parent->size());

    w_2_ = this->width()/2.0;
    h_2_ = this->height()/2.0;

    cpX_ = this->width()/2.0;
    cpY_ = this->height()/2.0 + otstupSverhu;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);


    labCenter_ = new QLabel("0", this);
    labCenter_->setGeometry(cpX_ - 30, cpY_ - 30, 60,60);
    labCenter_->setAlignment(Qt::AlignCenter);
    //labCenter_->move(cpX_ - 25, cpY_ - 25);
    labCenter_->setFont(QFont("Arial", 20, 57));
    labCenter_->setStyleSheet("color: white");
//    labCenter_->resize(20, 20);
//    labCenter_->setPixmap()


    val_old = 0;
    draw_(0);

}



void SArrow::setVal(float val)
{
    if (qRound(val) == val_old)
        return;

    val_old = qRound(val);

    if (val < 0) val = -val;
    if (val > maxVal_) val = maxVal_;

    draw_(val);

    labCenter_->setText(QString::number(qRound(val)));
}



void SArrow::draw_(double _val)
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    int sgp_angleArcEnd = 270 + 90/2;
    double stepDeg_ = (360.0 - 90.0)/maxVal_;



    //double angleInDeg = (360.0-sgp_angleArcEnd) - 90;
    double angleInDeg = (360.0-sgp_angleArcEnd) - (maxVal_ - _val)*stepDeg_;




    double angle = 0;

    angle = qDegreesToRadians(angleInDeg);
    double fooAngle = qDegreesToRadians(90.0);
    // длина стрелки
    double r  = 0.98;
    // половина ширины основания стрелки
    double r2 = 10.0;


    QPolygonF triangle;
    triangle << QPointF( cpX_ + (w_2_*r)*cos(angle),
                         cpY_ + (w_2_*r)*sin(angle) )
             << QPointF( cpX_ + r2*cos(angle+fooAngle),
                         cpY_ + r2*sin(angle+fooAngle) )
             << QPointF( cpX_ + r2*cos(angle-fooAngle),
                         cpY_ + r2*sin(angle-fooAngle) );

    paint.setPen(QPen(Qt::red, 2, Qt::SolidLine));
    paint.setBrush(Qt::transparent);
    paint.drawPolygon(triangle);


    paint.setPen(QPen( QColor(Qt::red),
                       58,
                       Qt::SolidLine,
                       Qt::RoundCap ));
    paint.drawPoint(QPoint(cpX_, cpY_));
    paint.setPen(QPen( QColor(Qt::black),
                       54,
                       Qt::SolidLine,
                       Qt::RoundCap ));
    paint.drawPoint(QPoint(cpX_, cpY_));



//    paint.setPen(QPen(Qt::green, 2, Qt::SolidLine));
//    QRect rect(0,/*28*/40, this->width(), this->width());
//    paint.drawArc(rect, sgp_angleArcEnd*16, sgp_lenArcScale*16);

    paint.end();
    this->setPixmap(pix);
}




// +++++++++++++++++++++++++++++++
//void ScaleArrow::draw_(int _val)
//{
//    img_.fill(Qt::transparent);
//    QPixmap pix = QPixmap::fromImage(img_);
//    QPainter paint(&pix);
//    paint.setRenderHint(QPainter::Antialiasing, true);

//    int sgp_angleArcEnd = 45; // +++
//    int sgp_maxSpeedScale = 60;
//    int sgp_lenArcScale = 90; // +++
//    double stepDeg_ = (360.0-270)/sgp_maxSpeedScale;



//    //double angleInDeg = (360.0-sgp_angleArcEnd) - 90;
//    double angleInDeg = (360.0-sgp_angleArcEnd) - (sgp_maxSpeedScale - _val)*stepDeg_;


//    paint.setPen(QPen(Qt::black, 1, Qt::SolidLine));
//    paint.setBrush(Qt::red);

//    double angle = 0;

//    angle = qDegreesToRadians(angleInDeg);
//    double fooAngle = qDegreesToRadians(90.0);
//    // длина стрелки
//    double r  = 1;
//    // половина ширины основания стрелки
//    double r2 = 1.5;

//    double r2Lk = 0.66;

//    QPolygonF triangle;
//    triangle << QPointF( cpX_ + (w_2_*r)*cos(angle),
//                         cpY_ + (w_2_*r)*sin(angle) )
//             << QPointF( cpX_ + (w_2_*r2Lk*r)*cos(angle) + r2*cos(angle+fooAngle),
//                         cpY_ + (w_2_*r2Lk*r)*sin(angle) + r2*sin(angle+fooAngle) )
//             << QPointF( cpX_ + (w_2_*r2Lk*r)*cos(angle) + r2*cos(angle-fooAngle),
//                         cpY_ + (w_2_*r2Lk*r)*sin(angle) + r2*sin(angle-fooAngle) );

//    paint.drawPolygon(triangle);


//    paint.setPen(QPen(Qt::green, 2, Qt::SolidLine));
//    QRect rect(0,28, this->width(), this->width());
//    paint.drawArc(rect, sgp_angleArcEnd*16, sgp_lenArcScale*16);

//    paint.end();
//    this->setPixmap(pix);
//}


