#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <mainwindow.h>


class clientSocket : public QObject
{
    Q_OBJECT
public:
    explicit clientSocket(QObject *parent = nullptr);
    void Test();

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void bytesWritten(qint64 bytes);

private:
    QTcpSocket *socket;

};

#endif // CLIENTSOCKET_H
