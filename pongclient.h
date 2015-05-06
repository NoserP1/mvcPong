#ifndef PONGCLIENT_H
#define PONGCLIENT_H

#include <memory>
#include <QtGlobal>

class QTcpSocket;

class PongClient
{
public:
  enum Move { Move_up = 1, Move_down = 2};
  PongClient();
  ~PongClient();

  void connect(const QString& ipAddressAndPort);

  void sendMove(Move move);
  void getPositions();

private:
  qint32 id = -1;
  std::unique_ptr<QTcpSocket> _socket;
};


#endif // PONGCLIENT_H