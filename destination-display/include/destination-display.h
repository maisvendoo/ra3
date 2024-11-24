#ifndef     DESTINATION_DISPLAY_H
#define     DESTINATION_DISPLAY_H

#include    <QTimer>
#include    <QLabel>
#include    "display.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class DestinationDisplay : public AbstractDisplay
{
public:

    DestinationDisplay(QWidget *parent = Q_NULLPTR,
                       Qt::WindowFlags f = Qt::WindowFlags());

    ~DestinationDisplay();

    void init();

private:

    QTimer  *updateTimer = nullptr;

    QLabel  *background = nullptr;

    QLabel  *destination_text = nullptr;

    QString prev_text = "";

private slots:

    void slotUpdateTimer();
};

#endif // DESTINATION_DISPLAY_H
