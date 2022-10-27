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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *le_Host;
    QLabel *label_2;
    QLineEdit *le_User;
    QLabel *label_3;
    QLineEdit *le_Passwd;
    QPushButton *pb_Link;
    QPushButton *pb_close;
    QTextEdit *te_Msg;
    QPushButton *pb_Send;
    QLineEdit *le_SendText;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(713, 483);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        le_Host = new QLineEdit(centralWidget);
        le_Host->setObjectName(QString::fromUtf8("le_Host"));

        gridLayout->addWidget(le_Host, 0, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        le_User = new QLineEdit(centralWidget);
        le_User->setObjectName(QString::fromUtf8("le_User"));

        gridLayout->addWidget(le_User, 0, 3, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        le_Passwd = new QLineEdit(centralWidget);
        le_Passwd->setObjectName(QString::fromUtf8("le_Passwd"));

        gridLayout->addWidget(le_Passwd, 0, 5, 1, 1);

        pb_Link = new QPushButton(centralWidget);
        pb_Link->setObjectName(QString::fromUtf8("pb_Link"));

        gridLayout->addWidget(pb_Link, 0, 6, 1, 1);

        pb_close = new QPushButton(centralWidget);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));

        gridLayout->addWidget(pb_close, 0, 7, 1, 1);

        te_Msg = new QTextEdit(centralWidget);
        te_Msg->setObjectName(QString::fromUtf8("te_Msg"));

        gridLayout->addWidget(te_Msg, 1, 0, 1, 8);

        pb_Send = new QPushButton(centralWidget);
        pb_Send->setObjectName(QString::fromUtf8("pb_Send"));

        gridLayout->addWidget(pb_Send, 2, 7, 1, 1);

        le_SendText = new QLineEdit(centralWidget);
        le_SendText->setObjectName(QString::fromUtf8("le_SendText"));

        gridLayout->addWidget(le_SendText, 2, 0, 1, 7);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Telnet\345\256\242\346\210\267\347\253\257", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP\345\234\260\345\235\200\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        pb_Link->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        pb_close->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200", nullptr));
        pb_Send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
