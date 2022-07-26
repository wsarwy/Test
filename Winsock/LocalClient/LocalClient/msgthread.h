#ifndef MSGTHREAD_H
#define MSGTHREAD_H

#include <QMainWindow>
#include <QThread>
#include <WinSock2.h>
#include <QDebug>
#include <QDateTime>


class MsgThread : public QThread
{
    Q_OBJECT
public:
    explicit MsgThread(SOCKET socket, QMainWindow *parent = nullptr);

    void run() override;

    void dealSend(QString msg);

private:
    SOCKET mSocket;
    QString msg;
    bool isSend;

signals:
    void serverIsClosed();
    void updateMsg(QString msg);
};

#endif // MSGTHREAD_H
