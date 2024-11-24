#ifndef     DESTINATION_DISPLAY_H
#define     DESTINATION_DISPLAY_H

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

    void update(double t, double dt);

private:

    QLabel  *background = nullptr;

    QLabel  *destination_text = nullptr;

    QString prev_text = "";

    short upd_count = 0;
};

#endif // DESTINATION_DISPLAY_H
