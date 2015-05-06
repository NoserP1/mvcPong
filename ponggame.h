#ifndef PONGGAME_H
#define PONGGAME_H

#include <memory>

#include <QMainWindow>
#include "pongcontroller.h"
#include "pongview.h"
#include "pongmodel.h"
#include <QMenuBar>

class PongClient;

class PongGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit PongGame(QWidget *parent = 0);
    ~PongGame();

private:
    std::unique_ptr<PongController> _controller;
    std::shared_ptr<PongView>   _view;
    std::shared_ptr<PongModel>  _model;
    std::shared_ptr<PongClient> _client;

//menu bar
private:
    QMenuBar*        _menuBar;

public slots:
    void startGame();
    void quitGame();
    void showConnectMenu();
};

#endif // PONGGAME_H
