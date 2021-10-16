#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initCabineControls()
{
    initTumblers("tumblers-config");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initTumblers(QString config_name)
{
    CfgReader cfg;

    if (!cfg.load(config_dir + QDir::separator() + config_name + ".xml"))
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
}
