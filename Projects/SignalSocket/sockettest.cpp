#include "sockettest.h"
SocketTest::SocketTest(QObject *parent) : QObject(parent)
{

}


void SocketTest::Test()
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    //connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));

    qWarning() << "Connecting...";

    socket->connectToHost("127.0.0.1",1234);

    if(!socket->waitForConnected(1000))
    {
        qWarning() << "Error: " << socket->errorString();
    }
}
void SocketTest::connected()
{
    qWarning() << "Connected!";

    socket->write("Hello\r\n");
    socket->write("Test\r\n");
}
void SocketTest::disconnected()
{
    qWarning() << "Disconnecting!";
}
void SocketTest::bytesWritten(qint64 bytes)
{
    qWarning() << "We wrote: " << bytes;

}
void SocketTest::readyRead()
{
    qWarning() << "Reading..";
}
