#include "pongserver.h"
#include "pongcontroller.h"
#include <QtNetwork/QtNetwork>

PongServer::PongServer(PongController* controller, std::shared_ptr<PongModel> model, QObject *parent)
:QObject(parent)
,_tcpServer(nullptr)
,_networkSession(0)
, _socket(nullptr)
,_controller(controller)
,_model(model)
{
    QNetworkConfigurationManager manager;
    /*if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        _networkSession = new QNetworkSession(config, this);
        connect(_networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        _networkSession->open();

    } else {*/
        sessionOpened();
    //}

    connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(connected()));
}

PongServer::~PongServer()
{
    if(_socket != NULL)    _socket->disconnectFromHost();
    if(_tcpServer != NULL) _tcpServer->disconnect();
}


void PongServer::sessionOpened()
{
    // Save the used configuration
    if (_networkSession) {
        QNetworkConfiguration config = _networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = _networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    _tcpServer = new QTcpServer(this);
    if (!_tcpServer->listen(QHostAddress::Any,51100)) {
        qDebug() << tr("Unable to start the server: ").arg(_tcpServer->errorString());
        return;
    }
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            _ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (_ipAddress.isEmpty())
    {
        _ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    _ipAddress = _tcpServer->serverAddress().toString();
     _ipPort = tr( " port: %1").arg(_tcpServer->serverPort());
}

QString PongServer::getServerIp()
{
    return _ipAddress + _ipPort;
}

void PongServer::connected()
{
    _socket = _tcpServer->nextPendingConnection();
    connect(_socket, SIGNAL(disconnected()),
            _socket, SLOT(deleteLater()));

    connect(_socket, SIGNAL(readyRead()),this, SLOT(received()));
}

void PongServer::received()
{
    if(_socket != NULL)
    {
        uint direction;
        int add;
        QDataStream in (_socket);
        in.setVersion(QDataStream::Qt_5_3);
        in >> direction;
        in >> add;
        qDebug() << direction;
        qDebug() << add;
        _controller->moveGuestPaddle(direction);


        in << _model->getPaddleLeft().getPos();
        qDebug() << _model->getPaddleLeft().getPos();
        in << _model->getPaddleRight().getPos();
        qDebug() << _model->getPaddleRight().getPos();
        in << _model->getBall().getPos();
        qDebug() << _model->getBall().getPos();

    }
}
