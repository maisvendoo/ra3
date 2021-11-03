#include    "trigger-label.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TriggerLabel::TriggerLabel(QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f)
  , text_old("")
{

}

TriggerLabel::TriggerLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
    setText(text);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TriggerLabel::~TriggerLabel()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TriggerLabel::setText(const QString &text)
{
    if (text == text_old)
        return;

    text_old = text;

    QLabel::setText(text);
}
