#ifndef PONGCLIENT_H
#define PONGCLIENT_H

#include <QtGlobal>

class PongClient
{
public:
  PongClient() = default;
  void connect(const QString& ipAddress);

  void sendMove();
  void getPositions();

private:
  qint32 id = -1;
};


#endif // PONGCLIENT_H