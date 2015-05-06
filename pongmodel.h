#ifndef PONGMODEL_H
#define PONGMODEL_H

#include "pongpart.h"
#include "pongtext.h"
#include <QRectF>

class PongModel
{
public:
    PongModel();
    ~PongModel();

    //get routines
    const PongMember & getBackground() const;
    const PongMember & getPaddleLeft() const;
    const PongMember & getPaddleRight() const;
    const PongMember & getBall() const;
    const PongMember & getScore() const;
    const QString    & getScoreText() const;
    const PongMember & getCountDown() const;
    const QString    & getCountDownText() const;
    const PongMember & getWon() const;
    const QString    & getWonText() const;


    //move routines
    void moveBall(float direction,float movement);
    void movePaddleRight(float direction,float movement);
    void movePaddleLeft(float direction,float movement);
    void resetAllParts();

    void setScore(const QString &text);
    void setCountDown(const QString &text);
    void setWon(const QString &text);


    //intersection routines
    PongPart::tTouches ballTouchesPaddleLeft();
    PongPart::tTouches ballTouchesPaddleRigth();
    PongPart::tTouches ballTouchesBack();

private:
    PongMember * _background;
    PongPart   * _paddleLeft;
    PongPart   * _paddleRight;
    PongPart   * _ball;
    PongText   * _score;
    PongText   * _countDown;
    PongText   * _won;
};

#endif // PONGMODEL_H
