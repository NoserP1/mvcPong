#ifndef PONGMEMBER_H
#define PONGMEMBER_H

#include <QRectF>
#include <QSizeF>
#include <QPointF>

class PongMember
{
public:

    PongMember(QSizeF size, QPointF resetPos);
    virtual ~PongMember();

    QSizeF  getSize() const;
    virtual QPointF getPos() const;

    QRectF operator* (float translation) const;

protected:
    const QSizeF  _size;
    const QPointF _resetPos;
};

#endif // PONGMEMBER_H
