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
  std::async(std::launch::async, [this](){ waitForPositions(); });
}

void PongClient::sendMove(Move move)
{
  QDataStream out(_socket.get());
  out.setVersion(QDataStream::Qt_5_3);
  out << move;
}

void PongClient::waitForPositions()
{
  while (true)
  {
    if (_socket->bytesAvailable() >= 3 * sizeof(QPointF))
    {
      getPositions();
    }
  }
}

void PongClient::getPositions()
{
  QPointF leftPaddle;
  QPointF rightPaddle;
  QPointF ball;
  QDataStream in(_socket.get());
  in >> leftPaddle >> rightPaddle >> ball;
  _model->movePaddleLeft(leftPaddle.rx(), leftPaddle.ry());
  _model->movePaddleRight(rightPaddle.rx(), rightPaddle.ry());
  _model->moveBall(ball.rx(), ball.ry());
}
