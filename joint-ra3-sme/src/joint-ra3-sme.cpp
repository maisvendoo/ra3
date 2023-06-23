#include    "joint-ra3-sme.h"

#include    "CfgReader.h"
#include    "physics.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
JointRA3sme::JointRA3sme() : Joint()
  , is_connected(false)
{
    devices.resize(NUM_CONNECTORS);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
JointRA3sme::~JointRA3sme()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void JointRA3sme::step(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Управление соединением СМЕ
    if (   (devices[FWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == 1.0)
        || (devices[BWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == 1.0) )
    {
        is_connected = true;
    }

    // Управление разъединением СМЕ
    if (   (devices[FWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == -1.0)
        || (devices[BWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == -1.0) )
    {
        is_connected = false;
    }

    if (is_connected)
    {
        devices[FWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 1.0);
        devices[BWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 1.0);

        for (size_t i = SME_TRAIN_CONFIG; i < NUM_RA3_SME_SIGNALS; ++i)
        {
            devices[FWD]->setInputSignal(i, devices[BWD]->getOutputSignal(i));
            devices[BWD]->setInputSignal(i, devices[FWD]->getOutputSignal(i));
        }

    }
    else
    {
        devices[FWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 0.0);
        devices[BWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 0.0);

        // Несоединённые контакты СМЕ
        for (size_t i = SME_TRAIN_CONFIG; i < NUM_RA3_SME_SIGNALS; ++i)
        {
            devices[FWD]->setInputSignal(i, 0.0);
            devices[BWD]->setInputSignal(i, 0.0);
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void JointRA3sme::load_config(CfgReader &cfg)
{
    QString secName = "Joint";
    cfg.getBool(secName, "initConnectionState", is_connected);
}

GET_JOINT(JointRA3sme)
