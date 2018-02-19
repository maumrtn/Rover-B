#include "mainwindow.h"
#include <QApplication>
#include <VLCQtCore/Common.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

    QApplication a(argc, argv);
    VlcCommon::setPluginPath(a.applicationDirPath() + "/plugins");
    MainWindow w;
    w.show();

    return a.exec();
}
