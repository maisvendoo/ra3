#ifndef     KRU091_H
#define     KRU091_H

#include    "brake-crane.h"
#include    "pneumo-reducer.h"
#include    "reservoir.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class KRU091 : public BrakeCrane
{
public:

    KRU091(QObject *parent = Q_NULLPTR);

    ~KRU091();

    void step(double t, double dt) override;

    void setPosition(int &position) override;

    QString getPositionName() override;

    float getHandlePosition() override;

    void init(double pTM, double pFL) override;

private:

    enum
    {
        POS_RELEASE = 0,
        POS_HOLD = 1,
        POS_BRAKE = 2
    };

    int handle_pos;

    int min_pos;

    int max_pos;

    double pos_delay;

    Timer *incTimer;

    Timer *decTimer;

    Reservoir *eq_res;

    /// Клапан зарядки РР
    double vr;

    /// Клапан разрядки РР
    double vb;

    /// Редуктор
    PneumoReducer *reducer;

    /// Утечка из РР
    double eq_res_leak;

    /// Условный объем тормозной магистрали
    double V_bp;

    /// Условная площадь уравнительного поршня РД
    double A;

    /// Атмосферный клапан РД
    double u1;

    /// Зарядный клапан РД
    double u2;

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
