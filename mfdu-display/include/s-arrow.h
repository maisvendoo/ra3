#ifndef SARROW_H
#define SARROW_H

#include <QLabel>

class SArrow : public QLabel
{
public:
    SArrow(QSize _size, int otstupSverhu, QWidget* parent = Q_NULLPTR);

    void setVal(float val);

private:
    double w_2_;
    double h_2_;

    double cpX_;
    double cpY_;

    QImage img_;

    double maxVal_;

    QLabel* labCenter_;



    void draw_(double _val);

};

#endif // SARROW_H
