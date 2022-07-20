#include "msgthread.h"

MsgThread::MsgThread(SOCKET mClient, sockaddr_in mAddr, QMainWindow* parent) : QThread(parent)
{
    this->mClient = mClient;
    this->mAddr  = mAddr;
}

MsgThread::~MsgThread()
{
    qDebug() << "msgThread 析构函数";
    int ret = closesocket(mClient);
    if( ret == 0 ){
        qDebug()<< "关闭成功";
    }else{
        qDebug()<< "关闭失败";
    }

}

void MsgThread::run()
{
    char* clientIp = inet_ntoa(mAddr.sin_addr);
    int clientPort = ntohs(mAddr.sin_port);

    while (true) {
        memset(resp, 0, 1024);
        char buf[1024] = {0};
        int ret = recv(mClient, buf, 1024,0);//
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");



    }


}


