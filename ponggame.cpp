#include "ponggame.h"

#include <QMessageBox>
#include <QInputDialog>

#include "pongclient.h"
#include "pongserver.h"

PongGame::PongGame(QWidget *parent)
    :QMainWindow(parent)
    , _model(new PongModel)
    , _view(new PongView(_model))
    , _client(new PongClient(_model))
    , _controller(new PongController(_model, _view, _client))
    , _server(new PongServer(_controller, _model))
    , _menuBar(new QMenuBar(this))
{
    QAction* start = _menuBar->addAction("&Start game");
    QAction* connect = _menuBar->addAction("&Connect");
    QAction* server = _menuBar->addAction("&Server");
    QAction* quit  = _menuBar->addAction("&Quit game");

    setCentralWidget(_view.get());
    setMenuBar(_menuBar);

    QObject::connect(start, SIGNAL(triggered()), this, SLOT(startGame()));
    QObject::connect(connect, SIGNAL(triggered()), this, SLOT(showConnectMenu()));
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(quitGame()));
    QObject::connect(server, SIGNAL(triggered()), this, SLOT(showServerIp()));

    resize(QSize(800,450));
    setBaseSize(800,450);
}

PongGame::~PongGame()
{
}

void PongGame::startGame()
{
    _controller->startGame();
}

void PongGame::quitGame()
{
    exit(0);
}

void PongGame::showConnectMenu()
{
  bool ok;
  QString text = QInputDialog::getText(this, tr("Connect to server"),
                                       tr("IP Address:"), QLineEdit::Normal, QString("10.0.0.64:51100"), &ok);
  if (ok && !text.isEmpty())
  {
    _client->connect(text);

  }
}


void PongGame::showServerIp()
{
    QMessageBox msgBox (this);
    msgBox.setWindowTitle("Server Ip");
msgBox.setText(_server->getServerIp());
msgBox.exec();
}
