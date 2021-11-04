#ifndef     BLOK_DISPLAY_H
#define     BLOK_DISPLAY_H

#include    "display.h"
#include    "blok-funcs.h"
#include    "structures-BLOK.h"

#include    <QTimer>
#include    <QLabel>

#include    "TopBlock.h"
#include    "blok-off-screen.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class BlokDisplay : public AbstractDisplay
{
public:

    BlokDisplay(QWidget *parent = Q_NULLPTR,
                Qt::WindowFlags f = Qt::WindowFlags());

    ~BlokDisplay();

    void init();

private:

    QTimer          *updateTimer;

    TopBlock        *topBlock;

    BlokOffScreen   *off_screen;

    structs_BLOK_t  structsBLOK;

    std::vector<QString>    stations;

    void initMainWindow();

    void initTopBlock();

    void loadStations();

private slots:

    void slotUpdateTimer();
};

#endif // BLOK_DISPLAY_H
