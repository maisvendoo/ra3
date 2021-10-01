#include    "mfdu-display.h"

#include    "tep70-signals.h"

#include    <QLayout>
#include    <QPainter>
#include    <QtCore/qmath.h>
#include    <QDate>


#include "mfdu-main-disp.h"



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MfduDisplay::MfduDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f)
{
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
//    this->resize(644, 465);
//    this->resize(1000, 600);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));
    this->setAttribute(Qt::WA_TransparentForMouseEvents);

    this->setLayout(new QVBoxLayout);
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    this->layout()->setContentsMargins(0, 0, 0, 0);


}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MfduDisplay::~MfduDisplay()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MfduDisplay::init()
{
    //
    background_ = new QLabel(this);
    background_->setFrameShape(QLabel::NoFrame);
    if (!pic_.load(":/mfdu/mfdu-main-disp")) { return; }
    background_->setFixedSize(pic_.size());
    background_->setPixmap(pic_);




    // Элементы основного экрана. Основной экран
    mfduMainDisp_ = new MfduMainDisp(background_);





    //
    this->layout()->addWidget(background_);

    AbstractDisplay::init();
}






GET_DISPLAY(MfduDisplay);
