#ifndef     MFDU_DISPLAY_H
#define     MFDU_DISPLAY_H

#include    "display.h"

#include    <QLabel>


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


    MfduMainDisp* mfduMainDisp_;




private slots:



};

#endif // MFDU_DISPLAY_H
