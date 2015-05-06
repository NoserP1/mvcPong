#ifndef PONGPART_H
#define PONGPART_H

#include "pongmember.h"

class PongPart : public PongMember
{
public:

    enum tTouchingSite
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };
    struct tTouches
    {
        tTouchingSite site;
        int touchingPointInPercent;
    };

    PongPart(QSizeF size, QPointF resetPos);

    virtual QPointF getPos() const;

    void resetPos();

    void moveTo(QPointF newPos);
    void moveInto(float direction, float movement);

    tTouches touches(const PongMember * elementToTest) const;

private:
    QPointF _actualPos;
};

#endif // PONGPART_H
