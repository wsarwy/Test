#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WSAStartup(MAKEWORD(2,2), &mWsaData);

    this->m_method = CommunicationMethod::UnixMethod;
    ui->lineEdit->setText("8888");

    connect(ui->start, &QPushButton::clicked, this, [=](){
        if(this->m_method == CommunicationMethod::UnixMethod)
        {
            slot_unixStart();
        }else if(this->m_method == CommunicationMethod::InetMethod)
        {
            slot_inetStart();
        }else
        {
            return;
        }
    });

    connect(ui->close, &QPushButton::clicked, this, &MainWindow::slot_close);
    connect(ui->clear, &QPushButton::clicked, this, &MainWindow::slot_clearAll);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index)
    {
        if(index == 0){
            this->m_method = CommunicationMethod::UnixMethod;
        }else if(index == 1)
        {
            this->m_method = CommunicationMethod::InetMethod;
        }else
        {
            return;
        }

    });

    connect(this, &MainWindow::updateMsg, this, [=](QString msg){
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        ui->listWidget->addItem(time + " : " +msg);
    });

}

MainWindow::~MainWindow()
{
    if(m_method == CommunicationMethod::UnixMethod)
    {
        _unlink( "D:/GitLab/Winsock/tmp./local");
    }

    closesocket(mListen);
    WSACleanup();
    delete ui;
}

void MainWindow::slot_unixStart()
{

    if(mListen != INVALID_SOCKET)
    {
        qDebug()<<"listen socketUN already is established";
        emit updateMsg("listen socketUN already is established");

        return;
    }

    mListen = socket(AF_UNIX, SOCK_STREAM, 0);
    int error;

    if(mListen == INVALID_SOCKET)
    {
        error = WSAGetLastError();
        qDebug()<< " socketUN error: "<<error;

        emit updateMsg(" socketUN error: "+ QString(error));
        return;
    }else
    {
        qDebug()<<"listen socketUN established";
        emit updateMsg("listen socketUN established");
    }

    //设置套接字的地址信息
    sockaddr_un addr_un;
    addr_un.sun_family = AF_UNIX;

    strcpy_s(addr_un.sun_path, "D:/GitLab/Winsock/tmp./local");

    //绑定套接字与地址信息
    int ret = bind(mListen, (sockaddr*)&addr_un, sizeof(addr_un));
    if(ret == SOCKET_ERROR)
    {
        error = WSAGetLastError();
        qDebug()<< "bind UN error: "<< error;
        emit updateMsg( "bind UN error: " + QString(error));
        return;
    }else
    {
        qDebug()<<"listen socketUN binded success";
        emit updateMsg("listen socketUN binded success");
    }

    //将监听socket设置为活动状态
    ret = ::listen(mListen, SOMAXCONN);
    if(ret == SOCKET_ERROR)
    {
        error = WSAGetLastError();
        qDebug()<<"listenUN error: "<< error;
        emit updateMsg("istenUN error: " + QString(error));
        return;
    }else
    {
        emit updateMsg("listenUN socket actived");
        qDebug()<<"listenUN socket actived";
    }

    ui->listWidget->addItem("unix local server startup success");
    qDebug()<<"unix local server startup success";

    //开启监听socket，使用accept函数，本线程将进入阻塞状态，
    //直到有客户端socket对该端口进行访问
    mSocketThreadUN = new SocketThreadUN(mListen);
    mSocketThreadUN->start();

    connect(mSocketThreadUN, &SocketThreadUN::isMsg, this, [=](QString msg){
        ui->listWidget->addItem(msg);
    });
}


void MainWindow::slot_inetStart()
{
    if(mListen != INVALID_SOCKET)
    {
        emit updateMsg("listen socket already is established");
        return;
    }

    //端口校验
    QString str = ui->lineEdit->text();
    QRegExp reg("[0-9]{1,5}");//0到65535
    QRegExpValidator validator(reg,this);
    int pos = 0;
    if( QValidator::Acceptable != validator.validate(str,pos)){
        emit updateMsg("port error");
        return;
    }
    int port = str.toInt();
    if( port < 0 || port > 65535){
        emit updateMsg("port error");
        return;
    }

    //建立监听socket
    mListen = socket(AF_INET, SOCK_STREAM, 0);
    int error;

    if(mListen == INVALID_SOCKET)
    {
        error = WSAGetLastError();
        qDebug()<< " socket error: "<<error;

        emit updateMsg(" socket error: "+ QString(error));
        return;
    }else
    {
        qDebug()<<"listen socket established";
        emit updateMsg("listen socket established");
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
        emit updateMsg( "bind error: " + QString(error));
        return;
    }else
    {
        emit updateMsg("listen socket binded success");
    }

    //将监听socket设置为活动状态
    ret = ::listen(mListen, SOMAXCONN);
    if(ret == SOCKET_ERROR)
    {
        error = WSAGetLastError();
        emit updateMsg("isten error: " + QString(error));
        return;
    }else
    {
        emit updateMsg("listen socket actived");
    }

    qDebug()<<"inet web server startup success";

    //开启监听socket，使用accept函数，本线程将进入阻塞状态，
    //直到有客户端socket对该端口进行访问
    mSocketThread = new SocketThread(mListen);
    mSocketThread->start();

    connect(mSocketThread, &SocketThread::isMSg, this, [=](QString msg){
        ui->listWidget->addItem(msg);
    });

}



void MainWindow::slot_close()
{
    if(mSocketThread != nullptr)
    {
        mListen =INVALID_SOCKET;
        _unlink("./local");

        mSocketThread->requestInterruption();
        mSocketThread->terminate();

        mSocketThread->quit();
        mSocketThread->wait();
        delete mSocketThread;
    }

    if(mSocketThreadUN != nullptr)
    {
        mListen =INVALID_SOCKET;
        _unlink("D:/GitLab/Winsock/tmp./local");

        mSocketThreadUN->requestInterruption();
        mSocketThreadUN->terminate();

        mSocketThreadUN->quit();
        mSocketThreadUN->wait();
        delete mSocketThreadUN;
    }

}


void MainWindow::slot_clearAll()
{
    ui->listWidget->clear();
}

