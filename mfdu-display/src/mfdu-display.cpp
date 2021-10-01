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


    // Шапка. Дата/время
    // Текущее время
    labelCurTime_ = new QLabel(background_);
    labelCurTime_->setFont(QFont("Arial", 14, 63));
    labelCurTime_->setText(QTime::currentTime().toString());
    labelCurTime_->setStyleSheet("color: white;");
    labelCurTime_->resize(140,20);
    labelCurTime_->move(650, 5);
    labelCurTime_->setAlignment(Qt::AlignCenter);
    // Текущая дата
    labelCurDate_ = new QLabel(background_);
    labelCurDate_->setFont(QFont("Arial", 14, 63));
    labelCurDate_->setText(QDate::currentDate().toString("dd.MM.yyyy"));
    labelCurDate_->setStyleSheet("color: white;");
    labelCurDate_->resize(140,20);
    labelCurDate_->move(650, 32);
    labelCurDate_->setAlignment(Qt::AlignCenter);

    updateTimer_ = new QTimer(this);
    connect(updateTimer_, &QTimer::timeout, this, &MfduDisplay::slotUpdateTimer);
    updateTimer_->setInterval(1000);
    updateTimer_->start();



    // Элементы основного экрана. Основной экран
    mfduMainDisp_ = new MfduMainDisp(background_);





    //
    this->layout()->addWidget(background_);

    AbstractDisplay::init();
}



void MfduDisplay::slotUpdateTimer()
{
    labelCurTime_->setText(QTime::currentTime().toString());
    labelCurDate_->setText(QDate::currentDate().toString("dd.MM.yyyy"));
}






GET_DISPLAY(MfduDisplay);
