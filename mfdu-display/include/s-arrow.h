#ifndef SARROW_H
#define SARROW_H

#include <QLabel>



class SArrow : public QLabel
{
public:
    SArrow(int otstupSverhu, QWidget* parent = Q_NULLPTR);

    void setVal(float val);

private:
    double w_2_;
    double h_2_;

    double cpX_;
    double cpY_;

    QImage img_;

    double maxVal_;

    QLabel* labCenter_;

    int val_old;

    void draw_(double _val);

};

#endif // SARROW_H
