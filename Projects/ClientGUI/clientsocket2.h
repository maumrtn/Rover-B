#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false,QString command="",  QObject *parent = Q_NULLPTR);
    QString sensorVal;

Q_SIGNALS:
    void closed();
    void messageReceived();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnection();
    void sendMsgTCP(QString);


private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    QString command;

};

#endif // ECHOCLIENT_H
