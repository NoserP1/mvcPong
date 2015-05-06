#include "pongview.h"
#include <QResizeEvent>
#include <QPainter>

PongView::PongView(const PongModel* pongModel, QWidget *parent)
    :QWidget(parent)
    ,_pongModel(pongModel)
    ,_normFactor(10)
{

}

PongView::~PongView()
{

}

void PongView::resizeEvent(QResizeEvent *e)
{
    _normFactor = e->size().width()/16;
    if(_normFactor > (e->size().height()/9))
    {
        _normFactor = e->size().height()/9;
    }
    update();
}


void PongView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QFont font=painter.font();

    painter.fillRect(_pongModel->getBackground()*_normFactor,Qt::black);
    painter.fillRect(_pongModel->getPaddleLeft()*_normFactor,Qt::white);
    painter.fillRect(_pongModel->getPaddleRight()*_normFactor,Qt::white);
    painter.fillRect(_pongModel->getBall()*_normFactor,Qt::white);

    //draw score
    font.setPixelSize((_pongModel->getScore()*_normFactor).height());
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(_pongModel->getScore()*_normFactor,Qt::AlignCenter,_pongModel->getScoreText());

    //draw won
    int getii = (_pongModel->getWon()*_normFactor).height();
    font.setPixelSize(getii);
    //font.setPixelSize((_pongModel->getWon()*_normFactor).height());
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(_pongModel->getWon()*_normFactor,Qt::AlignCenter,_pongModel->getWonText());

    //draw count down
    int get = (_pongModel->getCountDown()*_normFactor).height();
    font.setPixelSize(get);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(_pongModel->getCountDown()*_normFactor,Qt::AlignCenter,_pongModel->getCountDownText());

    QWidget::paintEvent(e);
    update();
}
