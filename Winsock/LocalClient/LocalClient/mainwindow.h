#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <QDebug>
#include "msgthread.h"
#include "afunix.h"


#pragma comment(lib,"ws2_32.lib")

enum CommunicationMethod
{
    UnixMethod =0,
    InetMethod
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

    void slot_connectInetServer();
    void slot_connectUnixServer();

    void slot_send();
    void slot_clear();

private:
    Ui::MainWindow *ui;
    MsgThread *mMsgThread;
    WSAData mWsaData;
    SOCKET mSocket;

    QString mAddrStr;

    CommunicationMethod m_method;


signals:
    void updateMsg(QString msg);
};
#endif // MAINWINDOW_H
