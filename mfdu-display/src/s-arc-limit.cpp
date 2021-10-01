#include "s-arc-limit.h"

#include <QPainter>



SArcLimit::SArcLimit(QWidget *parent)
    : QLabel(parent)
    , cSL_(0)
    , aCSL_(0.0)
{
    this->resize(parent->size());

    int otstup = 20;
    rect_.setRect( otstup,
                   otstup,
                   this->width()-otstup*2,
                   this->height()-otstup*2 );
    sgp_angleArcEnd_ = 270 + 90/2;
    int sgp_arcSplitLength= 90;
    sgp_maxSpeedScale_ = 140;
    stepSpeedInDegrees_ = (360.0 - sgp_arcSplitLength)/sgp_maxSpeedScale_;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

    setVal(110);

}



void SArcLimit::setVal(int limit)
{
    this->cSL_ = limit;
    aCSL_ = stepSpeedInDegrees_*(sgp_maxSpeedScale_ - cSL_)*16;

    draw_();
}



void SArcLimit::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);


    // текущее ограничение скорости
//    paint.setPen(QPen( QColor(Qt::red),
//                       10.0,
//                       Qt::SolidLine ));
    paint.setPen(QPen( QColor(255,0,0, 120),
                       10.0,
                       Qt::SolidLine ));
    paint.drawArc(rect_,
                  sgp_angleArcEnd_*16 + 10.0,
                  aCSL_ - 10.0*3);

    paint.end();
    this->setPixmap(pix);
}
