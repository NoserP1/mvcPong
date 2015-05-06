#include "pongtext.h"

PongText::PongText(const QString &text, QSizeF size, QPointF resetPos)
    :PongMember(size,resetPos)
    ,_text(text)
{

}



const QString& PongText::getText() const
{
    return _text;
}

void PongText::setText(const QString & text)
{
    _text = text;
}
