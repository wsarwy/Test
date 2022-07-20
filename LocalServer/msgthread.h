#ifndef MSGTHREAD_H
#define MSGTHREAD_H

#include <QThread>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <QDateTime>
#include <QDebug>
#include <QMainWindow>

class MsgThread : public QThread
{
    Q_OBJECT
public:
    explicit MsgThread(SOCKET mClient, sockaddr_in mAddr, QMainWindow* parent = nullptr);

    ~MsgThread();

    void run() override;
private:

    SOCKET mClient;

    sockaddr_in mAddr;

    char resp[1024] = {0};//发送的消息

signals:
    void updateMsg(QString msg);
};

#endif // MSGTHREAD_H
