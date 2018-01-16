#include "sockettest.h"

SocketTest::SocketTest(QObject *parent) : QObject(parent)
{

}

void SocketTest::Connect()
{
    //connected
    socket = new QTcpSocket(this);

    socket->connectToHost("voidrealms.com",80);

    if(socket->waitForConnected((3000)))
    {
        qDebug() << "Connected!";

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
