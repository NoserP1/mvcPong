#include "ponggame.h"

PongGame::PongGame(QWidget *parent)
    :QMainWindow(parent)
{

    _model = new PongModel();
    _view  = new PongView(_model,this);

    _controller = new PongController(_model,_view,this);

    _menuBar = new QMenuBar(this);
    QAction* start = _menuBar->addAction("&Start game");
    QAction* quit  = _menuBar->addAction("&Quit game");

    setCentralWidget(_view);
    setMenuBar(_menuBar);

    connect(start, SIGNAL(triggered()), this, SLOT(startGame()));
    connect(quit, SIGNAL(triggered()), this, SLOT(quitGame()));

    resize(QSize(800,450));
    setBaseSize(800,450);
}

PongGame::~PongGame()
{
    delete _model;
    delete _view;
    delete _controller;
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

