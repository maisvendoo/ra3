#include    "ra3-sme-connector.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3SME::RA3SME(QObject *parent) : Device(parent)
  , is_ref_state_command(false)
{
    name = QString("RA3SME");

    input_signals.resize(NUM_RA3_SME_SIGNALS);
    output_signals.resize(NUM_RA3_SME_SIGNALS);

    std::fill(input_signals.begin(), input_signals.end(), 0.0);
    std::fill(output_signals.begin(), output_signals.end(), 0.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RA3SME::~RA3SME()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3SME::connect()
{
    output_signals[SME_OUTPUT_REF_STATE] = 1.0;
    is_ref_state_command = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3SME::disconnect()
{
    output_signals[SME_OUTPUT_REF_STATE] = -1.0;
    is_ref_state_command = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool RA3SME::isConnected() const
{
    return is_linked && (input_signals[SME_INPUT_IS_CONNECTED] == 1.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3SME::setSignal(size_t idx, double value)
{
    if (idx < output_signals.size())
        output_signals[idx] = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double RA3SME::getSignal(size_t idx) const
{
    if ((is_linked) && (idx < input_signals.size()))
        return input_signals[idx];
    else
        return 0.0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3SME::step(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Проверяем, вызывались ли методы управления рукавами на данном шаге
    if (is_ref_state_command)
    {
        // Сбрасываем флаг, чтобы обнулить управляющий сигнал на следующем шаге
        is_ref_state_command = false;
    }
    else
    {
        // Если не вызывались, обнуляем управляющий сигнал
        output_signals[SME_OUTPUT_REF_STATE] = 0.0f;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3SME::ode_system(const state_vector_t &Y,
                           state_vector_t &dYdt,
                           double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
}
