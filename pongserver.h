#ifndef PONGSERVER
#define PONGSERVER

#include <QObject>
#include <memory>

class QTcpServer;
class QTcpSocket;
class QNetworkSession;
class PongController;
class PongModel;


class PongServer: public QObject
{
    Q_OBJECT

public:
    PongServer(std::shared_ptr<PongController> controller,std::shared_ptr<PongModel> model,QObject *parent = 0);
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
    std::shared_ptr<PongController>  _controller;
    std::shared_ptr<PongModel>  _model;
};

#endif // PONGSERVER

