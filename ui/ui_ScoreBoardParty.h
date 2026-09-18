/********************************************************************************
** Form generated from reading UI file 'ScoreBoardParty.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCOREBOARDPARTY_H
#define UI_SCOREBOARDPARTY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScoreBoardFlechettes
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QListWidget *listWidget;
    QTableView *eloTableView;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScoreBoardFlechettes)
    {
        if (ScoreBoardFlechettes->objectName().isEmpty())
            ScoreBoardFlechettes->setObjectName("ScoreBoardFlechettes");
        ScoreBoardFlechettes->resize(870, 740);
        centralwidget = new QWidget(ScoreBoardFlechettes);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 10, 851, 701));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(gridLayoutWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 419, 697));
        listWidget = new QListWidget(scrollAreaWidgetContents);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(-3, -2, 421, 701));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 1, 5, 1);

        eloTableView = new QTableView(gridLayoutWidget);
        eloTableView->setObjectName("eloTableView");

        gridLayout->addWidget(eloTableView, 4, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout_4->addWidget(pushButton);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_4->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        ScoreBoardFlechettes->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ScoreBoardFlechettes);
        statusbar->setObjectName("statusbar");
        ScoreBoardFlechettes->setStatusBar(statusbar);

        retranslateUi(ScoreBoardFlechettes);

        QMetaObject::connectSlotsByName(ScoreBoardFlechettes);
    } // setupUi

    void retranslateUi(QMainWindow *ScoreBoardFlechettes)
    {
        ScoreBoardFlechettes->setWindowTitle(QCoreApplication::translate("ScoreBoardFlechettes", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("ScoreBoardFlechettes", "Nouvelle partie", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ScoreBoardFlechettes", "Inscrire un nouveau joueur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScoreBoardFlechettes: public Ui_ScoreBoardFlechettes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCOREBOARDPARTY_H
