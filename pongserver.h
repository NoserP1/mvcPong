#ifndef PONGSERVER
#define PONGSERVER

#include <QObject>

class QTcpServer;
class QTcpSocket;
class QNetworkSession;

class PongServer: public QObject
{
    Q_OBJECT

public:
    explicit PongServer(QObject *parent = 0);
    ~PongServer();

    QString getServerIp();

public slots:
    void sessionOpened();
    void connected();
    void received();

private:
    QTcpServer *     _tcpServer;
    QNetworkSession* _networkSession;
    QTcpSocket*      _socket;
    QString          _ipAddress;
    QString          _ipPort;
};

#endif // PONGSERVER

