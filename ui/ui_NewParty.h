/********************************************************************************
** Form generated from reading UI file 'NewParty.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPARTY_H
#define UI_NEWPARTY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewParty
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NewParty)
    {
        if (NewParty->objectName().isEmpty())
            NewParty->setObjectName("NewParty");
        NewParty->resize(432, 203);
        centralwidget = new QWidget(NewParty);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(10, 10, 408, 171));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(gridLayoutWidget_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(true);
        lineEdit->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget_2);
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(comboBox, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget_2);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_2->addWidget(pushButton_2, 3, 0, 1, 1);

        lineEdit_3 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(lineEdit_3, 2, 1, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget_2);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 3, 1, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(lineEdit_2, 1, 1, 1, 1);

        comboBox_3 = new QComboBox(gridLayoutWidget_2);
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(comboBox_3, 2, 0, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget_2);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(comboBox_2, 1, 0, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget_2);
        pushButton_3->setObjectName("pushButton_3");

        gridLayout_2->addWidget(pushButton_3, 4, 0, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget_2);
        pushButton_4->setObjectName("pushButton_4");

        gridLayout_2->addWidget(pushButton_4, 4, 1, 1, 1);

        NewParty->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(NewParty);
        statusbar->setObjectName("statusbar");
        NewParty->setStatusBar(statusbar);

        retranslateUi(NewParty);

        QMetaObject::connectSlotsByName(NewParty);
    } // setupUi

    void retranslateUi(QMainWindow *NewParty)
    {
        NewParty->setWindowTitle(QCoreApplication::translate("NewParty", "MainWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("NewParty", "Ajouter un joueur", nullptr));
        pushButton->setText(QCoreApplication::translate("NewParty", "Inscrire un nouveau joueur", nullptr));
        pushButton_3->setText(QCoreApplication::translate("NewParty", "Valider la partie", nullptr));
        pushButton_4->setText(QCoreApplication::translate("NewParty", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewParty: public Ui_NewParty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPARTY_H
