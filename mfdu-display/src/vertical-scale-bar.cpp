#include "vertical-scale-bar.h"

#include <QPainter>



VerticalScaleBar::VerticalScaleBar(QSize _size, QWidget *parent)
    : QLabel(parent)
{
    this->resize(_size);

    h_2 = this->height()/2.0;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

    labTraction_ = new QLabel("0%", this);
    labTraction_->resize(this->width(), 20);
    labTraction_->move(0, h_2/2 - 10);
    labTraction_->setFont(QFont("Arial", 10, 75));
    labTraction_->setAlignment(Qt::AlignCenter);
    labTraction_->setStyleSheet("border: none;"
                                "color: limegreen;");

    labBrakingForce_ = new QLabel("0%", this);
    labBrakingForce_->resize(this->width(), 20);
    labBrakingForce_->move(0, h_2*3/2 - 10);
    labBrakingForce_->setFont(QFont("Arial", 10, 75));
    labBrakingForce_->setAlignment(Qt::AlignCenter);
    labBrakingForce_->setStyleSheet("border: none;"
                                    "color: yellow;");

    val_old = 0;
    setVal(0);
}

void VerticalScaleBar::setVal(int val)
{
    if (val == val_old)
        return;

    val_old = val;

    if (val > 100)
        val = 100;
    if (val < -100)
        val = -100;


    if (val >= 0)
    {
        labTraction_->setText(QString::number(val) + "%");

        if (val > 48)
            labTraction_->setStyleSheet("border: none; color: black;");
        else
            labTraction_->setStyleSheet("border: none; color: limegreen;");
    }
    if (val <= 0)
    {
        labBrakingForce_->setText(QString::number(std::abs(val)) + "%");

        if (val < -48)
            labBrakingForce_->setStyleSheet("border: none; color: black;");
        else
            labBrakingForce_->setStyleSheet("border: none; color: yellow;");
    }

    img_.fill(Qt::transparent);

    draw_(val);
}



void VerticalScaleBar::draw_(int val)
{
    val = -h_2*val/100;

    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);


    // столбик
    QPolygon polygon;
    polygon << QPoint(0, h_2 + val)
            << QPoint(this->width(), h_2 + val)
            << QPoint(this->width(), h_2)
            << QPoint(0, h_2);
    paint.setPen(Qt::transparent);

    if (val <= 0)
        paint.setBrush(QColor("#00ff00"));
    else
        paint.setBrush(QColor("#ffff00"));

    paint.drawPolygon(polygon);

    paint.end();

    this->setPixmap(pix);
}
