#ifndef SOCKETTHREADUN_H
#define SOCKETTHREADUN_H

#include <QThread>
#include <winsock2.h>
#include <QDateTime>
#include <QDebug>
#include <QMainWindow>
#include "msgthreadun.h"



class SocketThreadUN : public QThread
{
    Q_OBJECT

public:
    explicit SocketThreadUN(SOCKET mListen, QMainWindow* parent = nullptr);

    ~SocketThreadUN();

    void run() override;

private:
    SOCKET mListen;
    QMainWindow* parent;

signals:
    void isMsg(QString msg);
    void isClose();
};

#endif // SOCKETTHREADUN_H
