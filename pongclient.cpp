#include "pongclient.h"

#include <QTcpSocket>
#include <QStringList>

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
}

void PongClient::sendMove(Move move)
{
  QDataStream out(_socket.get());
  out.setVersion(QDataStream::Qt_5_3);
  out << move;
}


void PongClient::getPositions()
{
  QPointF leftPaddle;
  QPointF rightPaddle;
  QPointF ball;
  QDataStream in(_socket.get());
  in >> leftPaddle >> rightPaddle >> ball;
}