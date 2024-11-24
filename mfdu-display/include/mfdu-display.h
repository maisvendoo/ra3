#ifndef     MFDU_DISPLAY_H
#define     MFDU_DISPLAY_H

#include    "display.h"

#include    <QLabel>

class MfduDispOff;
class MfduMainDisp;



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MfduDisplay : public AbstractDisplay
{
public:

    MfduDisplay(QWidget *parent = Q_NULLPTR,
                Qt::WindowFlags f = Qt::WindowFlags());

    ~MfduDisplay();

    void init();

    void update(double t, double dt);

private:

    QLabel* background_;
    QPixmap pic_;

    // Текущая дата
    QLabel* labelCurDate_;
    // Текущее время
    QLabel* labelCurTime_;

    MfduDispOff*    mfduDispOff_;
    MfduMainDisp*   mfduMainDisp_;

    double upd_time = 0.0;
    double upd_interval = 0.2;
    int  upd_block = 0;
};

#endif // MFDU_DISPLAY_H
