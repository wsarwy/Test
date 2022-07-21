#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <winsock2.h>
#include <winsock.h>
#include <socketthread.h>
#include <QDebug>
#include <QRegExpValidator>

#pragma comment(lib,"ws2_32.lib")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_start();

    void slot_close();

    void slot_clearAll();

private:
    Ui::MainWindow *ui;
    WSADATA mWsaData;
    SOCKET mListen = INVALID_SOCKET;
    SocketThread* mSocketThread;
};
#endif // MAINWINDOW_H
