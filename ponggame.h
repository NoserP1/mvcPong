#ifndef PONGGAME_H
#define PONGGAME_H

#include <QMainWindow>
#include "pongcontroller.h"
#include "pongview.h"
#include "pongmodel.h"
#include <QMenuBar>

class PongGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit PongGame(QWidget *parent = 0);
    ~PongGame();

private:
    PongController * _controller;
    PongView*        _view;
    PongModel*       _model;

//menu bar
private:
    QMenuBar*        _menuBar;

public slots:
    void startGame();
    void quitGame();
};

#endif // PONGGAME_H
