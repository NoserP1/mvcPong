#ifndef PONGGAME_H
#define PONGGAME_H

#include <memory>

#include <QMainWindow>
#include "pongcontroller.h"
#include "pongview.h"
#include "pongmodel.h"
#include <QMenuBar>

class PongClient;
class PongServer;

class PongGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit PongGame(QWidget *parent = 0);
    ~PongGame();

private:
  std::shared_ptr<PongModel>  _model;
  std::shared_ptr<PongView>   _view;
  std::shared_ptr<PongClient> _client;
  PongController* _controller;
  std::shared_ptr<PongServer> _server;

//menu bar
private:
    QMenuBar*        _menuBar;

public slots:
    void startGame();
    void quitGame();
    void showConnectMenu();
    void showServerIp();
};

#endif // PONGGAME_H
