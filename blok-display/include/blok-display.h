#ifndef     BLOK_DISPLAY_H
#define     BLOK_DISPLAY_H

#include    "display.h"
#include    "blok-funcs.h"
#include    "structures-BLOK.h"

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

    void update(double t, double dt);

private:

    TopBlock        *topBlock;

    BlokOffScreen   *off_screen;

    structs_BLOK_t  structsBLOK;

    double upd_time = 0.0;
    double upd_interval = 0.2;
    int  upd_block = 0;

    void initMainWindow();

    void initTopBlock();
};

#endif // BLOK_DISPLAY_H
