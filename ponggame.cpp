#include "ponggame.h"

#include <QInputDialog>

#include "pongclient.h"

PongGame::PongGame(QWidget *parent)
    :QMainWindow(parent)
    , _controller()
    , _view()
    , _model(new PongModel)
    , _client(new PongClient(_model))
{
    _view.reset(new PongView(_model,this));

    _controller.reset(new PongController(_model,_view,_client,this));

    _menuBar = new QMenuBar(this);
    QAction* start = _menuBar->addAction("&Start game");
    QAction* connect = _menuBar->addAction("&Connect");
    QAction* quit  = _menuBar->addAction("&Quit game");

    setCentralWidget(_view.get());
    setMenuBar(_menuBar);

    QObject::connect(start, SIGNAL(triggered()), this, SLOT(startGame()));
    QObject::connect(connect, SIGNAL(triggered()), this, SLOT(showConnectMenu()));
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(quitGame()));

    resize(QSize(800,450));
    setBaseSize(800,450);
}

PongGame::~PongGame()
{
    delete _menuBar;
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

