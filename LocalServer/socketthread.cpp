#include "socketthread.h"

SocketThread::SocketThread(SOCKET mListen, QMainWindow* parent) : QThread(parent)
{
    this->mListen = mListen;
    this->parent = parent;
}


SocketThread::~SocketThread()
{
    closesocket(mListen);
    emit isClose();
}

void SocketThread::run()
{
    //新建客户端地址的参数，在连接时获取客户端的地址信息
    sockaddr_in mClientAddr;
    int size = sizeof(mClientAddr);

    //本线程没有被请求的情况下，该循环会一直执行
    //使用isinterruptionRequested请求中止线程
    while (!isInterruptionRequested()) {
        //将存储客户端ip的变量置零
        memset(&mClientAddr, 0, sizeof(mClientAddr));

        //调用accpet函数将socket启用,将返回一个与客户端连接的connect socket
        SOCKET connectionSocket = ::accept(mListen, (sockaddr*)&mClientAddr, &size);

        //读取客户端的IP信息
        char clientIP[17];
        inet_ntop(AF_INET, (const void*)&mClientAddr.sin_addr, clientIP, 17);

        //读取客户段的端口信息
        int clientPort = ntohs(mClientAddr.sin_port);

        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        QString msg = QString("%1 [%2:%3] connect success").arg(time).arg(clientIP).arg(clientPort);
        emit isMSg(msg);

        //将与客户端连接的socket放置到子线程，由子线程进行信息交互
        MsgThread* msgthread = new MsgThread(connectionSocket, mClientAddr, parent);
        msgthread->start();

        connect(this, &SocketThread::isClose, this, [=](){
            msgthread->terminate();
            msgthread->quit();
            delete msgthread;
        });



    }

}
