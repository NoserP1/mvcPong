#ifndef PONGTEXT_H
#define PONGTEXT_H

#include "pongmember.h"
#include <QString>

class PongText : public PongMember
{
public:
    PongText(const QString & text,QSizeF size, QPointF resetPos);

    const QString& getText() const;
    void setText(const QString & text);

private:
    QString _text;
};

#endif // PONGTEXT_H
