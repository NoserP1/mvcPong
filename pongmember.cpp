#include "pongmember.h"


PongMember::PongMember(QSizeF size, QPointF resetPos)
    :_size(size)
    ,_resetPos(resetPos)
{

}

PongMember::~PongMember()
{

}


QSizeF  PongMember::getSize() const
{
    return _size;
}

QPointF PongMember::getPos() const
{
    return _resetPos;
}

QRectF PongMember::operator* (float translation) const
{
    return QRectF(this->getPos()*translation, this->getSize()*translation);
}

