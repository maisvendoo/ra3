#include    "blok-off-screen.h"

BlokOffScreen::BlokOffScreen(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));
    this->move(0, 0);
    this->resize(1024, 768);
}
