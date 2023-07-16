#ifndef     KRU091_H
#define     KRU091_H

#include    "brake-crane.h"
#include    "pneumo-reducer.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class KRU091 : public BrakeCrane
{
public:

    KRU091(QObject *parent = Q_NULLPTR);

    ~KRU091();

    void step(double t, double dt) override;

    void setHandlePosition(int &position) override;

    QString getPositionName() const override;

    double getHandlePosition() const override;

    void init(double pBP, double pFL) override;

private:

    enum
    {
        POS_RELEASE = 0,
        POS_HOLD = 1,
        POS_BRAKE = 2
    };

    int handle_pos;

    QStringList positions_names;

    int min_pos;

    int max_pos;

    double pos_delay;

    Timer *incTimer;

    Timer *decTimer;

    /// Клапан зарядки РР
    double vr;

    /// Клапан разрядки РР
    double vb;

    /// Редуктор
    PneumoReducer *reducer;

    /// Утечка из РР
    double eq_res_leak;

    /// Условная площадь уравнительного поршня РД
    double A;

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

    void stepKeysControl(double t, double dt) override;

private slots:

    void inc_position();

    void dec_position();
};

#endif // KRU091_H
