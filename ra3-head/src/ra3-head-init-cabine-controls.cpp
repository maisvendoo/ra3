#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initCabineControls(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;

    // Реле активной кабины
    active_cab_relay = new Relay(2);
    active_cab_relay->read_config("mk", custom_cfg_dir);
    active_cab_relay->setInitContactState(0, false);
    active_cab_relay->setInitContactState(1, false);

    initTumblers("tumblers-config", custom_cfg_dir);

    // Контроллер машиниста
    km = new TracController();
    km->read_config("trac-controller", custom_cfg_dir);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initTumblers(const QString &config_name, const QString &custom_cfg_dir)
{
    CfgReader cfg;

    if (!cfg.load(custom_cfg_dir + QDir::separator() + config_name + ".xml"))
        return;


    QDomNode node = cfg.getFirstSection("Tumbler");

    while (!node.isNull())
    {
        int id = 0;
        bool state = false;

        if (cfg.getInt(node, "ID", id) && cfg.getBool(node, "State", state))
        {
            if (state)
                tumbler[id].set();
            else
                tumbler[id].reset();
        }

        node = cfg.getNextSection();
    }

    node = cfg.getFirstSection("KeyTumbler");

    while (!node.isNull())
    {
        int id = 0;
        bool state = false;

        if (cfg.getInt(node, "ID", id) && cfg.getBool(node, "State", state))
        {
            key_tumbler[id].setInitState(state);

            double timeout_on = 0.0;
            double timeout_off = 0.0;
            cfg.getDouble(node, "timeout_on", timeout_on);
            cfg.getDouble(node, "timeout_off", timeout_off);
            key_tumbler[id].setTimeoutOn(timeout_on);
            key_tumbler[id].setTimeoutOff(timeout_off);
        }

        node = cfg.getNextSection();
    }
}
