#ifndef BLOK_STATIONS_H
#define BLOK_STATIONS_H

#include    <QString>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct station_t
{
    double begin_coord;
    double end_coord;
    QString name;

    station_t()
        : begin_coord(0)
        , end_coord(0)
        , name("")
    {

    }
};

#endif // BLOK_STATIONS_H
