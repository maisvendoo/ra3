#ifndef SARCLIMIT_H
#define SARCLIMIT_H

#include <QLabel>



class SArcLimit : public QLabel
{
public:
    SArcLimit(QWidget* parent = Q_NULLPTR);

    void setVal(int limit);


private:
    QImage img_;

    QRectF rect_; ///< размер рисуемой плоскости

    double stepSpeedInDegrees_; ///< шаг скорости в градусах

    int cSL_;       ///< значение текущего ограничения
    double aCSL_;   ///< угол "nSL_"

    int sgp_maxSpeedScale_;
    int sgp_angleArcEnd_;

    /// Нарисовать дуги ограничений
    void draw_();

    int limit_old;
};

#endif // SARCLIMIT_H
