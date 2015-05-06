#include "pongcontroller.h"
#include <QTime>
#include <QKeyEvent>
#include "pongclient.h"


PongController::PongController(std::shared_ptr<PongModel> model, std::shared_ptr<PongView> view, std::shared_ptr<PongClient> client, QWidget *parent)
    :QWidget(parent)
    ,_model(model)
    ,_view(view)
    , _client(client)
{
    setFocusPolicy(Qt::StrongFocus);

    _gameTimer = new QTimer(this);
    connect(_gameTimer, SIGNAL(timeout()), this, SLOT(gameEvent()));
    _gameTimer->start(10);

    _ballDirection = 0;
    _scoreLeft = 0;
    _scoreRigth = 0;
    _state = IDLE;
    _countDown = 3;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

PongController::~PongController()
{
    delete _gameTimer;
}

void PongController::startGame()
{
    _state = INIT;
}

void PongController::gameEvent()
{
    switch(_state)
    {
    case INIT:
        _model->resetAllParts();
        _ballDirection = getRandomBallDirection(false,false);
        _scoreLeft = 0;
        _scoreRigth = 0;
        _state = COUNT_DOWN;
        _gameTimer->start(10);
        _countDown = 3;
        _model->setCountDown("");
        _model->setWon("");
        _model->setScore(QString::number(_scoreLeft)+" : "+QString::number(_scoreRigth));
        break;
    case COUNT_DOWN:
        if(_countDown > 0)
        {
            _model->setCountDown(QString::number(_countDown));
            _countDown--;
            _gameTimer->start(1000);
        }
        else
        {
            _gameTimer->start(10);
            _model->setCountDown("");
            _state = PLAYING;
        }
        break;
    case PLAYING:

        if(_model->ballTouchesBack().site == PongPart::LEFT)
        {
            //goal for right
            _scoreRigth ++;
            if(_scoreRigth >= 10)
            {
                //right won
                _state = WON;
                _model->setWon("Right player wins!");
            }
            else
            {
                _model->resetAllParts();
                _ballDirection = getRandomBallDirection(false,true);
                _state = COUNT_DOWN;
                _countDown = 3;
            }
        }
        else if (_model->ballTouchesBack().site == PongPart::RIGHT)
        {
            //goal for left
            _scoreLeft ++;
            if(_scoreLeft >= 10)
            {
                //right won
                _state = WON;
                _model->setWon("Left player wins!");
            }
            else
            {
                _model->resetAllParts();
                _ballDirection = getRandomBallDirection(true,false);
                _state = COUNT_DOWN;
                _countDown = 3;
            }
        }
        else
        {
            _ballDirection = checkBallOnTouches( _ballDirection);
            _model->moveBall(_ballDirection,0.085f);
        }
        _gameTimer->start(10);
        break;

    case WON:
        break;
    case IDLE:
        break;
    default:
        _state = INIT;
        break;
    }

    _model->setScore(QString::number(_scoreLeft)+" : "+QString::number(_scoreRigth));
    //restart timer
    update();
}

int PongController::checkBallOnTouches(int actualBallDirection)
{
    int newBallDirection = actualBallDirection;
    PongPart::tTouches hittedBack        = _model->ballTouchesBack();
    PongPart::tTouches hittedPaddleLeft  = _model->ballTouchesPaddleLeft();
    PongPart::tTouches hittedPaddleRight = _model->ballTouchesPaddleRigth();

    //then check if collision with backGround
    if(hittedBack.site != PongPart::NONE)
    {
        switch(hittedBack.site)
        {
        case PongPart::TOP:
        case PongPart::BOTTOM:
            newBallDirection = 360 - actualBallDirection;
            break;
        case PongPart::LEFT:
            newBallDirection = 270+270 -actualBallDirection;
            break;
        case PongPart::RIGHT:
            newBallDirection = 270-(actualBallDirection-270);
            break;
        default:
            break;
        }
    }
    else if(hittedPaddleLeft.site != PongPart::NONE)
    {
        switch(hittedPaddleLeft.site)
        {
        case PongPart::TOP:
        case PongPart::BOTTOM:
            newBallDirection = 360 - actualBallDirection;
            break;
        case PongPart::LEFT:
            newBallDirection = 270-(actualBallDirection-270);
            break;
        case PongPart::RIGHT:
            newBallDirection = 360 + hittedPaddleLeft.touchingPointInPercent * 45 / 100;
             break;
        default:
            break;
        }
    }
    else if(hittedPaddleRight.site != PongPart::NONE)
    {
        switch(hittedPaddleRight.site)
        {
        case PongPart::TOP:
        case PongPart::BOTTOM:
            newBallDirection = 360 - actualBallDirection;
            break;
        case PongPart::LEFT:
            newBallDirection = 180 - hittedPaddleRight.touchingPointInPercent * 45 / 100;
            break;
        case PongPart::RIGHT:
            newBallDirection = 270+270 -actualBallDirection;
             break;
        default:
            break;
        }
    }

    if     (newBallDirection > 360)  newBallDirection -= 360;
    else if(newBallDirection < 0)    newBallDirection += 360;
    else if(newBallDirection == 360) newBallDirection = 0;

    return newBallDirection;
}


void PongController::keyPressEvent(QKeyEvent * e)
{
    float paddleTop = 0;
    float backTop   = 0;
    float paddleBottom = 0;
    float backBottom   = 0;


    switch(e->key())
    {
    case Qt::Key_Up:
        _client->sendMove(PongClient::Move_up);
/*        paddleTop = _model->getPaddleLeft().getPos().y();
        backTop   = _model->getBackground().getPos().y();

        if(paddleTop - 0.5 <= backTop)
        {
            _model->movePaddleLeft(90,paddleTop - backTop);
        }
        else
        {
            _model->movePaddleLeft(90,0.5);
        }
        //update();
*/
        break;

    case Qt::Key_Down:
        _client->sendMove(PongClient::Move_down);
/*        paddleBottom = _model->getPaddleLeft().getPos().y() + _model->getPaddleLeft().getSize().height();
        backBottom   = _model->getBackground().getPos().y() + _model->getBackground().getSize().height();

        if(paddleBottom + 0.5 >= backBottom)
        {
            _model->movePaddleLeft(270,backBottom - paddleBottom);
        }
        else
        {
            _model->movePaddleLeft(270,0.5);
        }
        update();
*/        break;
    default:
        break;
    }
}


int PongController::getRandomBallDirection(bool left, bool rigth)
{
    const int MAX_HIGH = 180 + 15;
    const int MAX_LOW  = 180 - 15;
    int randomDirection = 0;

    if(left == true && rigth == false)
    {
        randomDirection = qrand() % ((MAX_HIGH + 1) - MAX_LOW) + MAX_LOW;
    }
    else if(left == false && rigth == true)
    {
        randomDirection = qrand() % ((MAX_HIGH + 1) - MAX_LOW) + MAX_LOW;
        randomDirection -= 180;
        if(randomDirection < 0) randomDirection+=360;
    }
    else
    {
        randomDirection = qrand() % ((MAX_HIGH + 1) - MAX_LOW) + MAX_LOW;
        if(qrand() % ((100 + 1) - 0) + 0 > 50)
        {
            randomDirection -= 180;
            if(randomDirection < 0) randomDirection+=360;
        }
    }

    return randomDirection;
}


void PongController::moveGuestPaddle(uint direction)
{
    float paddleTop = 0;
    float backTop   = 0;
    float paddleBottom = 0;
    float backBottom   = 0;

    PongClient::Move move = static_cast<PongClient::Move>(direction);
    switch(move)
    {
    case PongClient::Move_up:
        _client->sendMove(PongClient::Move_up);
        paddleTop = _model->getPaddleRight().getPos().y();
        backTop   = _model->getBackground().getPos().y();

        if(paddleTop - 0.5 <= backTop)
        {
            _model->movePaddleRight(90,paddleTop - backTop);
        }
        else
        {
            _model->movePaddleRight(90,0.5);
        }
        //update();

        break;

    case PongClient::Move_down:
        _client->sendMove(PongClient::Move_down);
        paddleBottom = _model->getPaddleRight().getPos().y() + _model->getPaddleRight().getSize().height();
        backBottom   = _model->getBackground().getPos().y() + _model->getBackground().getSize().height();

        if(paddleBottom + 0.5 >= backBottom)
        {
            _model->movePaddleRight(270,backBottom - paddleBottom);
        }
        else
        {
            _model->movePaddleRight(270,0.5);
        }
        update();
        break;
    default:
        break;
    }
}
