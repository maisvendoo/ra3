#ifndef     JOINT_RA3_SME_H
#define     JOINT_RA3_SME_H

#include    "device-joint.h"

#include    "ra3-sme-signals.h"

enum
{
    NUM_CONNECTORS = 2,
    FWD = 0,
    BWD = 1
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class JointRA3sme : public Joint
{
public:

    /// Конструктор
    JointRA3sme();

    /// Деструктор
    ~JointRA3sme();

    /// Шаг симуляции
    virtual void step(double t, double dt);

private:

    /// Состояние соединения рукавов
    bool is_connected;

    /// Загрузка параметров из конфига
    virtual void load_config(CfgReader &cfg);
};

#endif // JOINT_RA3_SME_H
