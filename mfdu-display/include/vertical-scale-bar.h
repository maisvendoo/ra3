#ifndef VERTICALSCALEBAR_H
#define VERTICALSCALEBAR_H

#include <QLabel>



class VerticalScaleBar : public QLabel
{
public:
    VerticalScaleBar(QSize _size, QWidget* parent = Q_NULLPTR);

    void setVal(int val);

private:
    QImage img_;

    int h_2;

    QLabel* labTraction_;
    QLabel* labBrakingForce_;

    int val_old;

    void draw_(int val);
};

#endif // VERTICALSCALEBAR_H
