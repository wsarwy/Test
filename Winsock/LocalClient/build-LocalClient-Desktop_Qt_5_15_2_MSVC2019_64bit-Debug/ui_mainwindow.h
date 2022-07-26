/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *address;
    QPushButton *connectServer;
    QLineEdit *txt_send;
    QPushButton *send;
    QLabel *label;
    QPushButton *clear;
    QListWidget *listWidget;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        address = new QLineEdit(centralwidget);
        address->setObjectName(QString::fromUtf8("address"));
        address->setGeometry(QRect(140, 110, 271, 31));
        connectServer = new QPushButton(centralwidget);
        connectServer->setObjectName(QString::fromUtf8("connectServer"));
        connectServer->setGeometry(QRect(440, 110, 171, 29));
        txt_send = new QLineEdit(centralwidget);
        txt_send->setObjectName(QString::fromUtf8("txt_send"));
        txt_send->setGeometry(QRect(140, 190, 271, 31));
        send = new QPushButton(centralwidget);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(440, 190, 171, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 280, 69, 20));
        clear = new QPushButton(centralwidget);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(440, 270, 171, 31));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(30, 310, 741, 231));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(140, 40, 141, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        connectServer->setText(QCoreApplication::translate("MainWindow", "connectServer", nullptr));
        send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\346\217\220\347\244\272", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260\350\277\233\347\250\213\351\200\232\350\256\257", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260\347\275\221\347\273\234\351\200\232\350\256\257", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
