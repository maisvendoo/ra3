#ifndef     MPSU_H
#define     MPSU_H

#include    "device.h"

#include    "mpsu-data.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MPSU : public Device
{
public:

    MPSU(QObject *parent = Q_NULLPTR);

    ~MPSU();

    void step(double t, double dt) override;

    void setInputData(const mpsu_input_t &mpsu_input);

    mpsu_output_t getOutputData() const;

private:

    /// Признак сброса МПСУ
    bool is_reseted;

    /// Входные сигналы
    mpsu_input_t    mpsu_input;

    /// Выходные сигналы
    mpsu_output_t   mpsu_output;


    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);

    /// Сброс МПСУ
    void reset();

    /// Главный цикл управления
    void main_loop_step(double t, double dt);
};

#endif // MPSU_H
