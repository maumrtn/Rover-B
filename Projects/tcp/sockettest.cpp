#include "sockettest.h"

SocketTest::SocketTest(QObject *parent) : QObject(parent)
{

}

void SocketTest::Connect()
{
    //connected
    socket = new QTcpSocket(this);

    socket->connectToHost("voidrealm.com",80);

    if(socket->waitForConnected((3000)))
    {
        qWarning() << "Connected!";

        socket->write("hello server\r\n\r\n\r\n");

        socket->waitForBytesWritten(1000);

        socket->waitForReadyRead(3000);

        qWarning() << "Reading:";

        qWarning() << socket->readAll();

        socket->close();
    }
    else
    {
        qDebug() << "Not Connected!";
    }
    // sent

    // got

    // closed
}
