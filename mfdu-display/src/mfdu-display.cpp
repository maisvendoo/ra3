#include    "mfdu-display.h"

#include    <QLayout>
#include    <QDate>

#include "ra3-head-signals.h"
#include "mfdu-disp-off.h"
#include "mfdu-main-disp.h"



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MfduDisplay::MfduDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f)
{
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(800, 588);
//    this->resize(1000, 600);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(255, 0, 0)));
    this->setAttribute(Qt::WA_TransparentForMouseEvents);

    this->setLayout(new QVBoxLayout);
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    this->layout()->setContentsMargins(0, 0, 0, 0);

    connect(&updateTimer_, &QTimer::timeout, this, &MfduDisplay::slotUpdateTimer, Qt::QueuedConnection);
    updateTimer_.setInterval(1000);
    updateTimer_.start();
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




    // "Выключить" окно.
    mfduDispOff_ = new MfduDispOff(background_);

    // Элементы основного экрана. Основной экран
    mfduMainDisp_ = new MfduMainDisp(background_);


    input_signals[MFDU_DISPLAY_ON] = 0;
    // UPDATE ДАННЫХ ОСНОВНОГО ЭКРАНА
    // Спидометр
    input_signals[MFDU_S_SPEED] = 55.0;             // Спидометр. Скорость
    input_signals[MFDU_S_SPEED_LIMIT] = 25;         // Спидометр. Ограничение скорости
    input_signals[MFDU_S_GREEN_DIGIT] = 80;         // Спидометр. Зеленое число
    input_signals[MFDU_S_WHITE_DIGIT] = 120.5;      // Спидометр. Белое число
    // Иконки справа от спидометра
    input_signals[MFDU_ACTIVE_CHARGE] = 1;      // Подпитка
    input_signals[MFDU_PVU] = 0;                // Подвагонное управление
    input_signals[MFDU_EPK] = 1;                // ЭПК
    input_signals[MFDU_MANEUVER_LIGHTS1] = 1;   // Маневровые огни 1
    input_signals[MFDU_MANEUVER_LIGHTS2] = 1;   // Маневровые огни 2
    input_signals[MFDU_PTF] = 0;                // ПТФ
    input_signals[MFDU_PZD] = 1;                // ПЖД
    input_signals[MFDU_PUMP] = 1;               // Помпы
    input_signals[MFDU_TPN] = 0;                // ТПН
    input_signals[MFDU_FIRE] = 0;               // Пожар
    input_signals[MFDU_OZ] = 1;                 // Пониженный уровень ОЖ контура ПЖД
    input_signals[MFDU_DOOR] = 0;               // Аварийное открытие дверей
    input_signals[MFDU_GENERATOR] = 0;          // Генератор
    input_signals[MFDU_VIP] = 0;                // ВИП
    input_signals[MFDU_INC_OZ_MOTOR] = 1;       // Повышена температура ОЖ двигателя
    input_signals[MFDU_DEC_OZ_MOTOR] = 1;       // Пониженный уровень ОЖ контура двигателя
    input_signals[MFDU_WC] = 0;                 // Туалет
    input_signals[MFDU_ANTY_YUZ] = 1;           // Противоюз
    input_signals[MFDU_REVERS] = 0;             // Реверс двигателя не завершён
    input_signals[MFDU_TRANSMISSION] = 0;       // Ошибка трансмиссии
    input_signals[MFDU_OIL_MOTOR] = 1;          // Уровень масла двигателя
    input_signals[MFDU_PRESSURE_OIL_MOTOR] = 1; // Пониженное давление масла двигателя
    input_signals[MFDU_MOTOR] = 1;              // Двигатель
    // Иконки слева от спидометра
    input_signals[MFDU_COMPRESSOR] = 0;     // Компрессор
    input_signals[MFDU_COMPRESSOR_1] = 0;   // Компрессор 1
    input_signals[MFDU_COMPRESSOR_2] = 0;   // Компрессор 2
    input_signals[MFDU_ATTENTION] = 0;      // Внимание!
    input_signals[MFDU_STOP] = 0;           // СТОП
    input_signals[MFDU_REVERS_FWD] = 0;     // Реверсор вперед
    input_signals[MFDU_REVERS_BWD] = 0;     // Реверсор назад
    input_signals[MFDU_REVERS_NEUTRAL] = 0; // Реверсор нейтальное положение
    input_signals[MFDU_XREN1] = 0;          //
    input_signals[MFDU_XREN2] = 0;          //
    input_signals[MFDU_XREN3] = 0;          //
    // Тяга/торможение
    input_signals[MFDU_TRACTION_BRAKING] = 30;
    // Блок нижних параметров
    input_signals[MFDU_PRESSURE_PM] = 0.0;      // Давление ПМ
    input_signals[MFDU_PRESSURE_TM] = 0.5;      // Давление ТМ
    input_signals[MFDU_PRESSURE_TC_MAX] = 0.0;  // Давление ТЦ max
    input_signals[MFDU_PRESSURE_TC_MIN] = 0.0;  // Давление ТЦ min
    input_signals[MFDU_TEMPERATURE_KAB] = 0;    // Температура кабины
    input_signals[MFDU_I_AKB_24] = -103.7;      // Ток акб 24
    input_signals[MFDU_I_AKB_110] = -103.7;     // Ток акб 110
    // Блок иконок сверху от спидометра
    input_signals[MFDU_VAGON_EQUIPMENT_LEFT] = 0;   // Вагонное оборудование
    input_signals[MFDU_VAGON_EQUIPMENT_RIGHT] = 0;  // Вагонное оборудование
    input_signals[MFDU_PZD_MINI_LEFT] = 0;          // ПЖД
    input_signals[MFDU_PZD_MINI_RIGHT] = 0;         // ПЖД
    input_signals[MFDU_BRAKES_LEFT] = 0;            // Тормоза
    input_signals[MFDU_BRAKES_RIGHT] = 0;           // Тормоза
    input_signals[MFDU_CAN_RIGHT] = 0;              // Отсутствие свзи с вагоном
    input_signals[MFDU_T_LEFT] = 0;                 //
    input_signals[MFDU_T_RIGHT] = 0;                //

    //mfduMainDisp_->updateData(input_signals);





    this->layout()->addWidget(background_);


    AbstractDisplay::init();

    mfduDispOff_->raise();
}



void MfduDisplay::slotUpdateTimer()
{
    labelCurTime_->setText(QTime::currentTime().toString());
    labelCurDate_->setText(QDate::currentDate().toString("dd.MM.yyyy"));

    //
    mfduMainDisp_->updateData(input_signals);

    //
    mfduDispOff_->setVisible(!static_cast<bool>(input_signals[MFDU_DISPLAY_ON]));
}






GET_DISPLAY(MfduDisplay);
