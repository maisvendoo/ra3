#ifndef     LINEAR_INTERPOLATION_H
#define     LINEAR_INTERPOLATION_H

#include    <QString>
#include    <vector>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class LinearInterpolation
{
public:

    LinearInterpolation();

    ~LinearInterpolation();

    void load(const std::string &path);

    double getValue(double I);

private:

    struct point_t
    {
        double  current;
        double  value;

        point_t()
            : current(0.0)
            , value(0.0)
        {

        }
    };

    std::vector<point_t> points;

    point_t findPoint(double I, point_t &next_point);

    double  interpolate(double I);
};

#endif // LINEAR_INTERPOLATION_H
