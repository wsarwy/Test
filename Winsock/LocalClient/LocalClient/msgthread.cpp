#include "msgthread.h"

MsgThread::MsgThread(SOCKET socket, QMainWindow *parent ): QThread(parent)
{
    this->mSocket = socket;
    this->isSend =false;

}

void MsgThread::run()
{
    char buf[1024] = {0};
    while(true)
    {
        if(isSend)
        {
            QString time0 = QDateTime::currentDateTime().toString("hh:mm:ss.zzz") + "intial";
            QString timeMsg = time0 + "\n" + msg;
            ::send(mSocket, timeMsg.toUtf8().data(), timeMsg.length()+ 1, 0);
            int errorCode = WSAGetLastError();
            if(errorCode == WSAECONNABORTED)
            {
                qDebug()<<"Software caused connection abort";
                return;
            }

            int ret = ::recv(mSocket, buf, 1024,0);
            if(ret == 0)
            {
                qDebug()<<"服务器端关闭";
                emit serverIsClosed();
                return;
            }

            QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
            QString msg1 = QString("%1 client receive message").arg(time) + "\n" + buf;
            emit updateMsg(msg1);
            this->isSend = false;
        }
    }

}

void MsgThread::dealSend(QString msg)
{
    this->isSend = true;
    this->msg = msg;
}
