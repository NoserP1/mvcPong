#include "pongclient.h"

#include <future>
#include <QPointF>
#include <QTcpSocket>
#include <QStringList>

#include "pongmodel.h"

PongClient::PongClient(std::shared_ptr<PongModel> model)
: _model(model)
{

}

PongClient::~PongClient()
{
}

void PongClient::connect(const QString& ipAddressAndPort)
{
  _socket.reset(new QTcpSocket(nullptr));
  QStringList address = ipAddressAndPort.split(':');
  _socket->connectToHost(address[0], address[1].toInt());
  QObject::connect(_socket.get(), &QTcpSocket::readyRead, [this](){ getPositions(); });
}

void PongClient::sendMove(Move move)
{
  static int i = 0;
  QDataStream out(_socket.get());
  out.setVersion(QDataStream::Qt_5_3);
  out << move << i++;
}

void PongClient::getPositions()
{
  QPointF leftPaddle;
  QPointF rightPaddle;
  QPointF ball;
  QDataStream in(_socket.get());
  in >> leftPaddle >> rightPaddle >> ball;
  qDebug() << "left: " << leftPaddle << "; right: " << rightPaddle << "; ball: " << ball;
  _model->setPaddleLeft(leftPaddle);
  _model->setPaddleRight(rightPaddle);
  _model->setBall(ball);
}
