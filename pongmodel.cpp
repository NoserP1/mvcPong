#include "pongmodel.h"
#include <QtCore/qmath.h>

PongModel::PongModel()
{   
    _background  = new PongMember(QSizeF(16,9),QPointF(0,0));
    _paddleLeft  = new PongPart(QSizeF(0.2,2),QPointF(1,3.5));
    _paddleRight = new PongPart(QSizeF(0.2,2),QPointF(14.8,3.5));
    _ball        = new PongPart(QSizeF(0.1,0.1),QPointF(7.95,4.45));

    _score       = new PongText("0 : 0",QSizeF(2,0.5),QPointF(7,0.5));
    _countDown   = new PongText("",QSizeF(2,2),QPointF(7,3.5));
    _won         = new PongText("",QSizeF(8,1),QPointF(4,4));
}

PongModel::~PongModel()
{
    delete _background;
    delete _paddleLeft;
    delete _paddleRight;
    delete _ball;
    delete _score;
    delete _countDown;
    delete _won;
}

const PongMember & PongModel::getBackground() const
{
    return *_background;
}

const PongMember & PongModel::getPaddleLeft() const
{
    return *_paddleLeft;
}

const PongMember & PongModel::getPaddleRight() const
{
    return *_paddleRight;
}

const PongMember & PongModel::getBall() const
{
    return *_ball;
}

const PongMember & PongModel::getScore() const
{
    return *_score;
}

const QString    & PongModel::getScoreText() const
{
    return _score->getText();
}

const PongMember & PongModel::getCountDown() const
{
    return *_countDown;
}

const QString    & PongModel::getCountDownText() const
{
    return _countDown->getText();
}

const PongMember & PongModel::getWon() const
{
    return *_won;
}

const QString    & PongModel::getWonText() const
{
    return _won->getText();
}

//move routines
void PongModel::moveBall(float direction,float movement)
{
    _ball->moveInto(direction,movement);
}

void PongModel::movePaddleRight(float direction,float movement)
{
    _paddleRight->moveInto(direction,movement);
}

void PongModel::movePaddleLeft(float direction,float movement)
{
    _paddleLeft->moveInto(direction,movement);
}

void PongModel::resetAllParts()
{
    _paddleLeft->resetPos();
    _paddleRight->resetPos();
    _ball->resetPos();
}

void PongModel::setScore(const QString & text)
{
    _score->setText(text);
}

void PongModel::setCountDown(const QString & text)
{
    _countDown->setText(text);
}

void PongModel::setWon(const QString & text)
{
    _won->setText(text);
}


PongPart::tTouches PongModel::ballTouchesPaddleLeft()
{
    return _ball->touches(_paddleLeft);
}

PongPart::tTouches PongModel::ballTouchesPaddleRigth()
{
    return _ball->touches(_paddleRight);
}

PongPart::tTouches PongModel::ballTouchesBack()
{
    return _ball->touches(_background);
}
