#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WSAStartup(MAKEWORD(2,2), &mWsaData);
    ui->address->setText("127.0.0.1:8888");

    this->m_method = CommunicationMethod::UnixMethod;

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index)
    {
        if(index == 0){m_method = CommunicationMethod::UnixMethod;}
        else if(index == 1){m_method = CommunicationMethod::InetMethod;}
        else {return;}
    });

    connect(ui->connectServer, &QPushButton::clicked, this, [=](){
        if(m_method == CommunicationMethod::UnixMethod){
            this->slot_connectUnixServer();
        }
        else if(m_method == CommunicationMethod::InetMethod)
        {
            this->slot_connectInetServer();
        }
        else{
            return;
        }
    });

    connect(ui->send, &QPushButton::clicked, this, &MainWindow::slot_send);
    connect(ui->clear, &QPushButton::clicked, this, &MainWindow::slot_clear);


}

MainWindow::~MainWindow()
{
    if(m_method == CommunicationMethod::UnixMethod)
    {
         _unlink("D:/GitLab/Winsock/tmp./local");
    }

    closesocket(mSocket);
    WSACleanup();
    if(mMsgThread != nullptr)
    {
        mMsgThread->quit();
    }
    delete ui;
}

void MainWindow::slot_connectUnixServer()
{
    qDebug()<<"start connect unix server";
    mSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    if(mSocket == INVALID_SOCKET)
    {
        qDebug()<<" socket created fail";
        return;
    }

    sockaddr_un sockAddr;
    sockAddr.sun_family = AF_UNIX;
    strcpy_s(sockAddr.sun_path, "D:/GitLab/Winsock/tmp./local");

    int ret = ::connect(mSocket, (sockaddr*)&sockAddr, sizeof(sockAddr));
    if(ret == SOCKET_ERROR)
    {
        int error = WSAGetLastError();
        qDebug()<<"connect server error: "<< error;
        return;
    }

    qDebug()<<"client connect server sucess";

    mMsgThread = new MsgThread(mSocket);
    mMsgThread->start();

    connect(mMsgThread, &MsgThread::updateMsg, this, &MainWindow::updateMsg);
    connect(this, &MainWindow::updateMsg, this, [=](QString msg){
        ui->listWidget->addItem(msg);
    });

}

void MainWindow::slot_connectInetServer()
{
    qDebug()<<"start connect inet server";
    mSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(mSocket == INVALID_SOCKET)
    {
        qDebug()<<" socket created fail";
        return;
    }

    mAddrStr = ui->address->text();
    char ip[1024] = {0};
    int port = 0;
    sscanf(mAddrStr.toUtf8().data(),"%[^:]:%d",ip,&port);

    qDebug()<<ip<<"  "<<port;

    sockaddr_in sockAddr;
    inet_pton(AF_INET, ip, (void*)&sockAddr.sin_addr);
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons((u_short)port);

    int ret = ::connect(mSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
    if(ret == SOCKET_ERROR)
    {
        int error = WSAGetLastError();
        qDebug()<<"connect server error: "<< error;
        return;
    }

    qDebug()<<"client connect server sucess";

    mMsgThread = new MsgThread(mSocket);
    mMsgThread->start();

    connect(mMsgThread, &MsgThread::updateMsg, this, &MainWindow::updateMsg);
    connect(this, &MainWindow::updateMsg, this, [=](QString msg){
        ui->listWidget->addItem(msg);
    });



}

void MainWindow::slot_send()
{
    QString str = ui->txt_send->text();
    mMsgThread->dealSend(str);
}

void MainWindow::slot_clear()
{
    if(m_method == CommunicationMethod::UnixMethod)
    {
         _unlink("D:/GitLab/Winsock/tmp./local");
    }

    ui->listWidget->clear();
}

