#include <QCoreApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "DEBUG";
    qWarning() << "WARNING";


    return a.exec();
}
