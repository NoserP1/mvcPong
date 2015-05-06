#ifndef PONGCLIENT_H
#define PONGCLIENT_H

#include <memory>
#include <QtGlobal>

class QTcpSocket;
class PongModel;

class PongClient
{
public:
  enum Move : quint32 { Move_up = 1u, Move_down = 2u};
  PongClient(std::shared_ptr<PongModel> model);
  ~PongClient();

  void connect(const QString& ipAddressAndPort);

  void sendMove(Move move);
  void getPositions();

private:
  qint32 id = -1;
  std::unique_ptr<QTcpSocket> _socket;
  std::shared_ptr<PongModel> _model;
};


#endif // PONGCLIENT_H