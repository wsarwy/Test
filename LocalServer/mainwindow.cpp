#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WSAStartup(MAKEWORD(2,2), &mWsaData);

    connect(ui->start, &QPushButton::clicked, this, &MainWindow::slot_start);
    connect(ui->close, &QPushButton::clicked, this, &MainWindow::slot_close);
    connect(ui->clear, &QPushButton::clicked, this, &MainWindow::slot_clearAll);

}

MainWindow::~MainWindow()
{
    closesocket(mListen);
    WSACleanup();
    delete ui;
}


void MainWindow::slot_start()
{
    if(mListen != INVALID_SOCKET)
    {
        qDebug()<<"listen socket already is established";
        return;
    }

    //端口校验
    QString str = ui->lineEdit->text();
    QRegExp reg("[0-9]{1,5}");//0到65535
    QRegExpValidator validator(reg,this);
    int pos = 0;
    if( QValidator::Acceptable != validator.validate(str,pos)){
        return;
    }
    int port = str.toInt();
    if( port < 0 || port > 65535){
        return;
    }

    //建立监听socket
    mListen = socket(AF_INET, SOCK_STREAM, 0);
    int error;

    if(mListen == INVALID_SOCKET)
    {
        error = WSAGetLastError();
        qDebug()<< " socket error: "<<error;
        return;
    }else
    {
        qDebug()<<"listen socket established";
    }

    //设置套接字的地址信息
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((ushort)port);
    addr.sin_addr.S_un.S_addr =inet_addr("127.0.0.1");

    //绑定套接字与地址信息
    int ret = bind(mListen, (sockaddr*)&addr, sizeof(addr));
    if(ret == SOCKET_ERROR)
    {
        error = WSAGetLastError();
        qDebug()<< "bind error: "<< error;
        return;
    }else
    {
        qDebug()<<"listen socket binded success";
    }

    //将监听socket设置为活动状态
    ret = ::listen(mListen, SOMAXCONN);
    if(ret == SOCKET_ERROR)
    {
        error = WSAGetLastError();
        qDebug()<<"listen error: "<< error;
        return;
    }else
    {
        qDebug()<<"listen socket actived";
    }

    qDebug()<<"server startup success";

    //开启监听socket，使用accept函数，本线程将进入阻塞状态，
    //直到有客户端socket对该端口进行访问
    mSocketThread = new SocketThread(mListen);
    mSocketThread->start();

    connect(mSocketThread, &SocketThread::isMSg, this, [=](QString msg){
        ui->textEdit->setText(msg);
    });

}


void MainWindow::slot_close()
{
    if(mSocketThread != nullptr)
    {
        mSocketThread->requestInterruption();
        mSocketThread->terminate();

        mSocketThread->quit();
        mSocketThread->wait();
        delete mSocketThread;
    }
}


void MainWindow::slot_clearAll()
{
    ui->textEdit->clear();
}

