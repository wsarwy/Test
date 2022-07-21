﻿#include "msgthread.h"

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
    //char* clientIP = inet_ntop(mAddr.sin_addr);
    char clientIP[17];
    inet_ntop(AF_INET, (const void*)&mAddr.sin_addr, clientIP, 17);

    int clientPort = ntohs(mAddr.sin_port);

    while (true) {
        memset(resp, 0, 1024);
        char buf[1024] = {0};
        int ret = recv(mClient, buf, 1024,0);//等待客户端传输的消息
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        if(ret == 0){
            qDebug()<<"client not return effective data";
            break;
        }

        QString msg = QString("%1 [%2:%3]:%4").arg(time).arg(clientIP).arg(clientPort).arg(buf);
        emit updateMsg(msg);

        const char* log = "msg is dealed by server";

        QString retMsg = msg + log;

        strcpy(resp, retMsg.toUtf8().data());

        send(mClient, resp, strlen(resp) +1 ,0);

    }


}


