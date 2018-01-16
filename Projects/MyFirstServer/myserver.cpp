#include "myserver.h"

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any,1234))
    {
        qWarning() <<"Server could not start!";
    }
    else
    {
        qWarning() <<"Server started!";
    }
}

void MyServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
    socket->write("hello client");
    socket->flush();
}

void MyServer::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    //socket->waitForBytesWritten(300);
    QString a = socket->readAll();
    qWarning() << a;
    socket->close();
}
