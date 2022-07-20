#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <winsock2.h>
#include <winsock.h>
#include <socketthread.h>
#include <QDebug>
#include <QRegExpValidator>



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
    void on_startServer_clicked();

    void on_closeServer_clicked();

    void on_clearAll_clicked();

private:
    Ui::MainWindow *ui;
    WSADATA mWsaData;
    SOCKET mListen = INVALID_SOCKET;
    SocketThread* mSocketThread;
};
#endif // MAINWINDOW_H
