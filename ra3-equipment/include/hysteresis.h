#ifndef     HYSTERESIS_H
#define     HYSTERESIS_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Hysteresis
{
public:

    Hysteresis();

    ~Hysteresis();

    void setRange(double x_min, double x_max);

    bool getState(double x);

private:

    double x_min;

    double x_max;

    bool state;
};

#endif // HYSTERESIS_H
