#ifndef MSGTHREADUN_H
#define MSGTHREADUN_H

#include <QThread>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <QDateTime>
#include <QDebug>
#include <QMainWindow>
#include <afunix.h>

class MsgThreadUN : public QThread
{
    Q_OBJECT
public:
    explicit MsgThreadUN(SOCKET mClient, sockaddr_un mAddr, QMainWindow* parent = nullptr);

    ~MsgThreadUN();

    void run() override;

private:

    SOCKET mClient;

    sockaddr_un mAddr;

    char resp[1024] = {0};//发送的消息


signals:
    void updateMsg(QString msg);
};

#endif // MSGTHREADUN_H
