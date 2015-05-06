#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include <memory>
#include <QWidget>
#include <QTimer>
#include "pongview.h"
#include "pongmodel.h"

class PongClient;

class PongController : public QWidget
{
    Q_OBJECT
public:
  PongController(std::shared_ptr<PongModel> model, std::shared_ptr<PongView> view, std::shared_ptr<PongClient> client, QWidget *parent = 0);
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

    std::shared_ptr<PongModel> _model;
    std::shared_ptr<PongView> _view;
    std::shared_ptr<PongClient> _client;
};

#endif // PONGCONTROLLER_H
