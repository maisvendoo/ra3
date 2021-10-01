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

    int nSL_;       ///< значение следующего ограничения
    int cSL_;       ///< значение текущего ограничения
    double aCSL_;   ///< угол "nSL_"
    double aNSL_;   ///< угол "cSL_"

    // --- cfg параметры --- //
    int     widthArc_;      ///< ширина линии дуги
    QString curArc_color_;  ///< цвет
    QString nextArc_color_; ///< цвет
    // --------------------- //

    int sgp_maxSpeedScale_;
    int sgp_angleArcEnd_;

    /// Нарисовать дуги ограничений
    void draw_();


};

#endif // SARCLIMIT_H
