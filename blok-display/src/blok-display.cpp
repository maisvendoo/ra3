#include    "blok-display.h"
#include    "ra3-head-signals.h"

#include    "CfgReader.h"

#include    <QVBoxLayout>
#include    <QDir>
#include    <QTextStream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BlokDisplay::BlokDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f)
    , topBlock(Q_NULLPTR)

{
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(1024, 768);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));

    this->setLayout(new QVBoxLayout);
    this-> setFocusPolicy(Qt::FocusPolicy::NoFocus);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BlokDisplay::~BlokDisplay()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BlokDisplay::init()
{
    initMainWindow();

    initTopBlock();

    off_screen = new BlokOffScreen(this);

    AbstractDisplay::init();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BlokDisplay::initMainWindow()
{
    CfgReader cfg;

    int     sizeWindow_X = 1024;
    int     sizeWindow_Y = 768;
    bool    hideCursor = true;
    int     timeInterval = 1000;

    if (cfg.load(config_dir + getConfigPath("main.xml")))
    {
        QString sectionName = "Main";
        cfg.getInt(sectionName, "sizeWindow_X", sizeWindow_X);
        cfg.getInt(sectionName, "sizeWindow_Y", sizeWindow_Y);
        cfg.getBool(sectionName, "hideCursor", hideCursor);
        cfg.getInt(sectionName, "timeInterval", timeInterval);
    }

    this->setCursor( hideCursor ? Qt::BlankCursor : Qt::ArrowCursor);

    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(sizeWindow_X, sizeWindow_Y);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BlokDisplay::initTopBlock()
{
    int margX = 20;
    int margY = 20;

    QRect rect = QRect(margX + 10,
                       margY,
                       this->width() - margX * 2,
                       this->height() - margY * 2);

    topBlock = new TopBlock(rect, this, config_dir + getConfigPath(""));
    this->layout()->addWidget(topBlock);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BlokDisplay::update(double t, double dt)
{
    (void) t;

    // Интервал обновления
    upd_time += dt;
    if (upd_time < upd_interval)
        return;

    upd_time = 0.0;

    if (input_signals[BLOK_DISPLAY_ON] == 0.0f)
    {
        off_screen->setVisible(true);
        off_screen->raise();
        return;
    }

    off_screen->setVisible(false);

    // Обновляем блоки экрана по очереди
    upd_time += dt;

    // Обновляем блоки экрана по очереди
    ++upd_block;

    // Блок обновлений №1
    if (upd_block == 1)
    {
        structsBLOK.ip2_val.BC = static_cast<double>(input_signals[BLOK_BC_PRESS]);
        structsBLOK.ip2_val.TM = static_cast<double>(input_signals[BLOK_BP_PRESS]);
        structsBLOK.ip2_val.UR = static_cast<double>(input_signals[BLOK_FL_PRESS]);
        structsBLOK.ip2_val.revers = static_cast<int>(input_signals[BLOK_REVERS]);

        topBlock->set_ip2Val(&structsBLOK.ip2_val);
        return;
    }

    // Блок обновлений №2
    if (upd_block == 2)
    {
        int seconds = static_cast<int>(input_signals[BLOK_TIME]);
        QString text = QString("%1:%2:%3")
                           .arg(seconds / 3600, 2, 10, QChar('0'))
                           .arg(seconds / 60 % 60, 2, 10, QChar('0'))
                           .arg(seconds % 60, 2, 10, QChar('0'));
        strcpy(structsBLOK.ip_val.time, text.toStdString().c_str());

        seconds = static_cast<int>(input_signals[BLOK_SHEDULE_TIME]);
        text = QString("%1:%2:%3")
                   .arg(seconds / 3600, 2, 10, QChar('0'))
                   .arg(seconds / 60 % 60, 2, 10, QChar('0'))
                   .arg(seconds % 60, 2, 10, QChar('0'));
        strcpy(structsBLOK.ip_val.grafic, text.toStdString().c_str());


        structsBLOK.ip_val.coordinate = static_cast<double>(input_signals[BLOK_RAILWAY_COORD]);

        text = "";
        for (size_t i = 0; i < 8; ++i)
        {
            int c = static_cast<int>(input_signals[BLOK_STATION_SYMB1 + i]);
            text.push_back(((c > 0) && (c < 65536)) ? QChar(c) : QChar(' '));
        }
        strcpy(structsBLOK.ip_val.station, text.toStdString().c_str());

        structsBLOK.ip_val.acceleration = static_cast<double>(input_signals[BLOK_ACCELERATION]);
        structsBLOK.ip_val.distanceTarget = static_cast<int>(input_signals[BLOK_TARGET_DIST]);

        text = "";
        for (size_t i = 0; i < 16; ++i)
        {
            int c = static_cast<int>(input_signals[BLOK_STRING_SYMB1 + i]);
            text.push_back(((c > 0) && (c < 65536)) ? QChar(c) : QChar(' '));
        }
        strcpy(structsBLOK.ip_val.typeTarget, text.toStdString().c_str());

        text = "";
        for (size_t i = 16; i < 24; ++i)
        {
            int c = static_cast<int>(input_signals[BLOK_STRING_SYMB1 + i]);
            text.push_back(((c > 0) && (c < 65536)) ? QChar(c) : QChar(' '));
        }
        strcpy(structsBLOK.ip_val.nameTarget, text.toStdString().c_str());

        topBlock->set_ipVal(&structsBLOK.ip_val);
        return;
    }

    // Блок обновлений №3
    if (upd_block >= 3)
    {
        int vigilance_and_tskbm = static_cast<int>(input_signals[BLOK_VIGILANCE_TSKBM]);
        bool is_vigilance = static_cast<bool>(vigilance_and_tskbm % 10);
        //bool is_tskbm = static_cast<bool>(vigilance_and_tskbm / 10 % 10);
        bool is_vigilance_tskbm = static_cast<bool>(vigilance_and_tskbm / 100);
        structsBLOK.other_val.signalControlLookOut = is_vigilance;
        structsBLOK.other_val.signalTSKBM = is_vigilance_tskbm;

        structsBLOK.other_val.curSpeed = qRound(input_signals[BLOK_SPEED]);
        structsBLOK.other_val.curSpeedLimit = qRound(input_signals[BLOK_SPEED_CUR_LIMIT]);
        structsBLOK.other_val.nextSpeedLimit = qRound(input_signals[BLOK_SPEED_NEXT_LIMIT]);

        topBlock->setCurSpeed(structsBLOK.other_val.curSpeed);
        topBlock->setSpeedLimits(structsBLOK.other_val.curSpeedLimit, structsBLOK.other_val.nextSpeedLimit);
        topBlock->setTriangleYellow(structsBLOK.other_val.signalControlLookOut);

        // Сбрасываем счётчик
        upd_block = 0;
        return;
    }
}

GET_DISPLAY(BlokDisplay)
