#ifndef     TRIGGER_LABEL_H
#define     TRIGGER_LABEL_H

#include    <QLabel>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class TriggerLabel : public QLabel
{
public:

    TriggerLabel(QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());

    TriggerLabel(const QString &text,
                 QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());

    ~TriggerLabel();

    void setText(const QString &text);

private:

    QString text_old;
};

#endif // TRIGGER_LABEL_H
