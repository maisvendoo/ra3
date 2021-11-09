#include    "ra3-head.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::initAutostart()
{
    if (!is_autostart)
        return;

    autostart_timer = new Timer(1.0, false);

    CfgReader cfg;

    QString path = config_dir +
            QDir::separator() +
            "start-program.xml";

    if (!cfg.load(path))
        return;

    QDomNode node = cfg.getFirstSection("Step");

    while (!node.isNull())
    {
        autostart_step_t step;

        cfg.getInt(node, "ID", step.id);
        cfg.getBool(node, "State", step.state);
        cfg.getDouble(node, "Timeout", step.timeout);
        cfg.getBool(node, "IsRelease", step.is_release);

        autostart_prog.push_back(step);

        node = cfg.getNextSection();
    }

    count_step = 0;

    connect(autostart_timer, &Timer::process, this, &RA3HeadMotor::slotAutostart);

    autostart_timer->start();
}
