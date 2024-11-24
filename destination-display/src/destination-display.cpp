#include    "destination-display.h"
#include    "ra3-head-signals.h"

#include    <QVBoxLayout>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
DestinationDisplay::DestinationDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f)
{
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(900, 90);
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
DestinationDisplay::~DestinationDisplay()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DestinationDisplay::init()
{
    QPixmap pic;
    if (!pic.load(":/destination/background")) { return; }

    this->resize(pic.size());

    background = new QLabel(this);
    background->setFrameShape(QLabel::NoFrame);
    background->setFixedSize(pic.size());
    background->setPixmap(pic);

    int font_size = pic.size().height();
    QString font("Arial");
    QString color("#BFFF3F");
    destination_text = new QLabel(QString(""), this);
    destination_text->resize(pic.size());
    destination_text->move(0, 0);
    destination_text->setAlignment(Qt::AlignCenter);
    destination_text->setFont(QFont(font, font_size));
    destination_text->setStyleSheet("color: " + color + ";" +
                                    "font-weight: bold;");

    updateTimer = new QTimer;
    connect(updateTimer, &QTimer::timeout, this, &DestinationDisplay::slotUpdateTimer, Qt::QueuedConnection);
    updateTimer->setInterval(1000);
    updateTimer->start();

    input_signals[DESTINATION_SIZE] = 0.0f;
    for (size_t i = 0; i < 15; ++i)
    {
        input_signals[DESTINATION_SYMB1 + i] = static_cast<float>(QChar(' ').unicode());
    }

    AbstractDisplay::init();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DestinationDisplay::slotUpdateTimer()
{
    int size = static_cast<int>(input_signals[DESTINATION_SIZE]);
    if ((size <= 0) || (size > 15))
    {
        prev_text = "";
        destination_text->setText("");
        return;
    }

    QString text = "";
    for (size_t i = 0; i < size; ++i)
    {
        int c = static_cast<int>(input_signals[DESTINATION_SYMB1 + i]);
        text.push_back(((c > 0) && (c < 65536)) ? QChar(c) : QChar(' '));
    }

    if (prev_text != text)
    {
        prev_text = text;
        destination_text->setText(text);
    }
}

GET_DISPLAY(DestinationDisplay)
