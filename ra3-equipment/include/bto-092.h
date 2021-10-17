#ifndef     BTO_092_H
#define     BTO_092_H

#include    "airdistributor.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class BTO092 : public AirDistributor
{
public:

    BTO092(QObject *parent = Q_NULLPTR);

    ~BTO092();

    void setParkingBrakePressure(double p_pb) { this->p_pb = p_pb; }

    double getParkingBrakeAirFlow() const { return Q_pb; }

    void setParkingBrakeState(bool is_parking_braked)
    {
        this->is_parking_braked = is_parking_braked;
    }

private:

    /// Давление в магистрали стояночного тормоза
    double p_pb;

    /// Поток в магистраль стояночного тормоза
    double Q_pb;

    /// Состояние стояночного тормоза
    bool is_parking_braked;

    /// Уставка давления в цилиндрах стояночного тормоза (ЦСТ)
    double pPB_max;

    enum
    {
        NUM_COEFFS = 10
    };

    std::array<double, NUM_COEFFS> K;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // BTO092_H
