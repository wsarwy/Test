#include "msgthreadun.h"

MsgThreadUN::MsgThreadUN(SOCKET mClient, sockaddr_un mAddr, QMainWindow* parent )
    : QThread{parent}
{
    this->mClient = mClient;
    this->mAddr  = mAddr;
}

MsgThreadUN::~MsgThreadUN()
{
    qDebug() << "msgThreadUN 析构函数";
    int ret = closesocket(mClient);
    if( ret == 0 ){
        qDebug()<< "关闭成功";
    }else{
        qDebug()<< "关闭失败";
    }
}

void MsgThreadUN::run()
{

    while (true) {
        memset(resp, 0, 1024);
        char buf[1024] = {0};

        int ret = recv(mClient, buf, 1024,0);//等待客户端传输的消息
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        if(ret == 0){
            qDebug()<<"client UN not return effective data";
            break;
        }

        QString msg = QString("%1 server receive: ").arg(time) +"\n" +buf;
        emit updateMsg(msg);

        const char* log = " msg UN is dealed by server";

        QString retMsg = msg + log;

        strcpy(resp, retMsg.toUtf8().data());

        send(mClient, resp, strlen(resp) +1 ,0);

    }
}
