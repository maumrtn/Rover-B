#include "mainwindow.h"
#include <QApplication>
#include "sockettest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SocketTest cTest;
    cTest.Connect();

    return a.exec();
}
