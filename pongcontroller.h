#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include <QWidget>
#include <QTimer>
#include "pongview.h"
#include "pongmodel.h"

class PongController : public QWidget
{
    Q_OBJECT
public:
    PongController(PongModel * model, PongView * view, QWidget *parent = 0);
    ~PongController();

    void startGame();

public slots:
    void gameEvent();

protected:
    void keyPressEvent(QKeyEvent * e);

private:
    int checkBallOnTouches(int actualBallDirection);
    int getRandomBallDirection(bool left, bool rigth);

    enum GAME_STATE{
        IDLE,
        INIT,
        COUNT_DOWN,
        PLAYING,
        WON
    };

    GAME_STATE _state;
    int _scoreLeft;
    int _scoreRigth;
    int _ballDirection;
    int _countDown;

    QTimer    * _gameTimer;

    PongModel * _model;
    PongView  * _view;
};

#endif // PONGCONTROLLER_H
