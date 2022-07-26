#include "socketthreadun.h"

SocketThreadUN::SocketThreadUN(SOCKET mListen, QMainWindow* parent) : QThread(parent)
{
    this->mListen = mListen;
    this->parent = parent;
}

SocketThreadUN::~SocketThreadUN()
{
    closesocket(mListen);
    emit isClose();
}


void SocketThreadUN::run()
{
    //新建客户端地址的参数，在连接时获取客户端的地址信息
    sockaddr_un mClientAddr;
    int size = sizeof(mClientAddr);

    //本线程没有被请求的情况下，该循环会一直执行
    //使用isinterruptionRequested请求中止线程
    while (!isInterruptionRequested()) {
        //将存储客户端ip的变量置零
        memset(&mClientAddr, 0, sizeof(mClientAddr));
        emit isMsg("socket start");
        //调用accpet函数将socket启用,将返回一个与客户端连接的connect socket
        SOCKET connectionSocket = ::accept(mListen, (sockaddr*)&mClientAddr, &size);
        if(connectionSocket != INVALID_SOCKET)
        {
            emit isMsg("connection socketUN is established");
        }else
        {
            emit isMsg("conection sokcet error");
        }


        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        QString msg = QString("%1  UN connect success").arg(time);
        emit isMsg(msg);

        //将与客户端连接的socket放置到子线程，由子线程进行信息交互
        MsgThreadUN* msgthreadUN = new MsgThreadUN(connectionSocket, mClientAddr, parent);
        msgthreadUN->start();

        connect(msgthreadUN, &MsgThreadUN::updateMsg, this, [=](QString msg)
        {
            emit isMsg(msg);
        });

        connect(this, &SocketThreadUN::isClose, this, [=](){
            msgthreadUN->terminate();
            msgthreadUN->quit();
            delete msgthreadUN;
        });

    }
}
