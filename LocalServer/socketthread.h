#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <winsock2.h>
#include <QDateTime>
#include <QDebug>
#include <QMainWindow>
#include "msgthread.h"

class SocketThread : public QThread

{
    Q_OBJECT
public:
    explicit SocketThread(SOCKET mListen, QMainWindow* parent = nullptr);

    ~SocketThread();

    void run() override;

private:
    SOCKET mListen;
    QMainWindow* parent;

signals:
    void isMSg(QString msg);
    void isClose();


};

#endif // SOCKETTHREAD_H
