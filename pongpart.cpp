#include "pongpart.h"
#include <QtCore/qmath.h>
#include <QRectF>

PongPart::PongPart(QSizeF size, QPointF resetPos)
    :PongMember(size,resetPos)
    ,_actualPos(resetPos)
{

}


QPointF PongPart::getPos() const
{
    return _actualPos;
}


void PongPart::resetPos()
{
    _actualPos = _resetPos;
}

void PongPart::moveTo(QPointF newPos)
{
    _actualPos = newPos;
}

void PongPart::moveInto(float direction, float movement)
{
    if((direction >= 0) && (direction <= 360))
    {
        _actualPos.setX(_actualPos.x() + (qCos(qDegreesToRadians(direction)) * movement));
        _actualPos.setY(_actualPos.y() - (qSin(qDegreesToRadians(direction)) * movement));
    }
}

PongPart::tTouches PongPart::touches(const PongMember * elementToTest) const
{
    PongPart::tTouches touches = {NONE,0};
    const float ITOL = 0.1f;
    QPointF theirPos  = elementToTest->getPos();
    QSizeF  theirSize = elementToTest->getSize();
    //                               x                          ,           y                            ,    width               , height
    QRectF theirsTop    = QRectF(theirPos.x()-ITOL                  ,theirPos.y()-ITOL                   ,theirSize.width()+2*ITOL,2*ITOL);
    QRectF theirsBottom = QRectF(theirPos.x()-ITOL                  ,theirPos.y()+theirSize.height()-ITOL,theirSize.width()+2*ITOL,2*ITOL);
    QRectF theirsLeft   = QRectF(theirPos.x()-ITOL                  ,theirPos.y()-ITOL                   ,2*ITOL                  ,theirSize.height()+2*ITOL);
    QRectF theirsRight  = QRectF(theirPos.x()+theirSize.width()-ITOL,theirPos.y()-ITOL                   ,2*ITOL                  ,theirSize.height()+2*ITOL);

    QRectF mine     = QRectF(_actualPos,_size);


    if(mine.intersects(theirsLeft))
    {
        touches.site = LEFT;
        touches.touchingPointInPercent = (theirSize.height()/2 - (mine.center().y() - theirPos.y())) * 100 / (theirSize.height()/2);
    }
    else if(mine.intersects(theirsRight))
    {
        touches.site = RIGHT;
        touches.touchingPointInPercent = (theirSize.height()/2 - (mine.center().y() - theirPos.y())) * 100 / (theirSize.height()/2);
    }
    else if(mine.intersects(theirsTop))
    {
        touches.site = TOP;

        touches.touchingPointInPercent = (theirSize.width()/2 - (mine.center().x() - theirPos.x())) * 100 / (theirSize.width()/2);
    }
    else if(mine.intersects(theirsBottom))
    {
        touches.site = BOTTOM;
        touches.touchingPointInPercent = (theirSize.width()/2 - (mine.center().x() - theirPos.x())) * 100 / (theirSize.width()/2);
    }
    return touches;
}
