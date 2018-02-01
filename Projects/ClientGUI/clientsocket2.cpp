#include "clientsocket2.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

//! [constructor]
EchoClient::EchoClient(const QUrl &url, bool debug,QString command,  QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug),
    sensorVal(""),
    command(command)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl(url));
}
//! [constructor]

//! [onConnected]
void EchoClient::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &EchoClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(command);
}
//! [onConnected]

//! [onTextMessageReceived]
void EchoClient::onTextMessageReceived(QString message)
{
    //if (m_debug)
    sensorVal = message;
    emit messageReceived();

        qWarning() << "Message received:" << message;
}
//! [onTextMessageReceived]

void EchoClient::onDisconnection()
{
     m_webSocket.close();
}

void EchoClient::sendMsgTCP(QString cmdString)
{
     m_webSocket.sendTextMessage(cmdString);
}
