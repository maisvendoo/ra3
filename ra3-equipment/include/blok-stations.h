#ifndef BLOK_STATIONS_H
#define BLOK_STATIONS_H

#include    <vec3.h>
#include    <QString>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct station_t
{
    dvec3 coord = {0.0, 0.0, 0.0};
    QString name = "";

    station_t()
    {

    }
};

#endif // BLOK_STATIONS_H
