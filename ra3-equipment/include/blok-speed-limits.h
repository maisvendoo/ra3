#ifndef     BLOK_SPEED_LIMITS_H
#define     BLOK_SPEED_LIMITS_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct speed_limit_t
{
    double coord;
    double value;

    speed_limit_t()
        : coord(10000000.0)
        , value(0.0)
    {

    }
};

#endif // BLOK_SPEED_LIMITS_H
