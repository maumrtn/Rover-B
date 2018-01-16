#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>

class sockettest : public QObject
{
    Q_OBJECT
public:
    explicit sockettest(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SOCKETTEST_H