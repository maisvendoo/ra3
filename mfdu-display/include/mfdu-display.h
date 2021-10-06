#ifndef     MFDU_DISPLAY_H
#define     MFDU_DISPLAY_H

#include    "display.h"

#include    <QLabel>
#include    <QTimer>

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

private:
    QLabel* background_;
    QPixmap pic_;


    // Текущая дата
    QLabel* labelCurDate_;
    // Текущее время
    QLabel* labelCurTime_;


    MfduMainDisp* mfduMainDisp_;


    QTimer* updateTimer_;


private slots:
    void slotUpdateTimer();


};

#endif // MFDU_DISPLAY_H
