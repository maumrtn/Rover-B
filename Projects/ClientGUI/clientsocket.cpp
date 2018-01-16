#include "clientsocket.h"
#include "mainwindow.h"
clientSocket::clientSocket(QObject *parent) : QObject(parent)
{

}


void clientSocket::Test()
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    socket->connectToHost("192",8080);

    if(!socket->waitForConnected(3000))
    {
        //ui->console->append("Warning: Could not connect");
    }
}
void clientSocket::connected()
{
    //ui->console->append("Connected!");
    //socket->write(QByteArray(155,'@'));
    socket->write("Test");
    //socket->flush();
}
void clientSocket::disconnected()
{
    //ui->console->append("Disconnecting");
}
void clientSocket::bytesWritten(qint64 bytes)
{
   // ui->console->append("We wrote...");
    qWarning() << "We wrote: " << bytes;

}
void clientSocket::readyRead()
{
    socket->readAll();
    //ui->console->append("Reading...");
    //qWarning() << "Reading..";
}
