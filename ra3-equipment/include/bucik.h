#ifndef     BUCIK_H
#define     BUCIK_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class BUCIK : public Device
{
public:

    BUCIK(QObject *parent = Q_NULLPTR);

    ~BUCIK();

    void step(double t, double dt) override;

    /// Загрузка станций из ЭК
    void loadStations(QString path);

    /// Задать индекс станции, отображаемой в маршрутоуказательном табло
    void setDestinationStationIndex(size_t idx);

    /// Индекс станции, отображаемой в маршрутоуказательном табло
    size_t getDestinationStationIndex();

    /// Текст в маршрутоуказательном табло
    QString getDestinationText() const;

private:

    enum
    {
        STATION_MAX_SYMBOLS = 15
    };

    bool old_key_state_plus;

    bool old_key_state_minus;

    size_t destination_idx = 0;

    /// База станций
    std::vector<QString> stations;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // BUCIK_H
