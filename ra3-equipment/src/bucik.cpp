#include    "bucik.h"

#include    <QTextStream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BUCIK::BUCIK(QObject *parent) : Device(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BUCIK::~BUCIK()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BUCIK::step(double t, double dt)
{
    stepKeysControl(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BUCIK::loadStations(QString path)
{
    QFile stations_file(path);

    if (!stations_file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QTextStream stream(&stations_file);

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList tokens = line.split('\t');

        QString station = tokens[0];
        if (station.size() > STATION_MAX_SYMBOLS)
            station.resize(STATION_MAX_SYMBOLS);
        stations.push_back(station);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BUCIK::setDestinationStationIndex(size_t idx)
{
    if (idx < stations.size())
        destination_idx = idx;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
size_t BUCIK::getDestinationStationIndex()
{
    return destination_idx;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString BUCIK::getDestinationText() const
{
    if (stations.empty())
        return QString("");

    return stations[destination_idx];
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BUCIK::ode_system(const state_vector_t &Y,
                      state_vector_t &dYdt,
                      double t)
{
    (void) Y;
    (void) dYdt;
    (void) t;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BUCIK::load_config(CfgReader &cfg)
{
    (void) cfg;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void BUCIK::stepKeysControl(double t, double dt)
{
    (void) t;
    (void) dt;

    if (stations.empty())
        return;

    if (getKeyState(KEY_Equals))
    {
        if (!old_key_state_plus)
        {
            if (destination_idx < stations.size() - 1)
                ++destination_idx;
            else
                destination_idx = 0;
        }

        old_key_state_plus = true;
    }
    else
    {
        old_key_state_plus = false;
    }

    if (getKeyState(KEY_Minus))
    {
        if (!old_key_state_minus)
        {
            if (destination_idx > 0)
                --destination_idx;
            else
                destination_idx = stations.size() - 1;
        }

        old_key_state_minus = true;
    }
    else
    {
        old_key_state_minus = false;
    }
}
