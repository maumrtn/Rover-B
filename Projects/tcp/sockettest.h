#ifndef SOCKETEST_H
#define SOCKETEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QObject *parent = nullptr);

    void Connect();
signals:

public slots:

private:
    QTcpSocket *socket;
};

#endif // SOCKETEST_H
