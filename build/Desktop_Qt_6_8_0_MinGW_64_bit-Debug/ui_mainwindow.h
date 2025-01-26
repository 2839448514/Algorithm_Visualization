/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_main;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *displayArea;
    QSplitter *splitter_log;
    QTextEdit *logArea;
    QGroupBox *variableGroup;
    QVBoxLayout *variableLayout;
    QTableWidget *variableTable;
    QWidget *rightWidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_right;
    QGroupBox *controlGroup;
    QTextBrowser *codeArea;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_E;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(727, 532);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        splitter_main = new QSplitter(centralwidget);
        splitter_main->setObjectName("splitter_main");
        splitter_main->setOrientation(Qt::Orientation::Horizontal);
        leftWidget = new QWidget(splitter_main);
        leftWidget->setObjectName("leftWidget");
        verticalLayout_2 = new QVBoxLayout(leftWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        displayArea = new QGraphicsView(leftWidget);
        displayArea->setObjectName("displayArea");

        verticalLayout_2->addWidget(displayArea);

        splitter_log = new QSplitter(leftWidget);
        splitter_log->setObjectName("splitter_log");
        splitter_log->setOrientation(Qt::Orientation::Horizontal);
        logArea = new QTextEdit(splitter_log);
        logArea->setObjectName("logArea");
        splitter_log->addWidget(logArea);
        variableGroup = new QGroupBox(splitter_log);
        variableGroup->setObjectName("variableGroup");
        variableLayout = new QVBoxLayout(variableGroup);
        variableLayout->setObjectName("variableLayout");
        variableTable = new QTableWidget(variableGroup);
        variableTable->setObjectName("variableTable");

        variableLayout->addWidget(variableTable);

        splitter_log->addWidget(variableGroup);

        verticalLayout_2->addWidget(splitter_log);

        splitter_main->addWidget(leftWidget);
        rightWidget = new QWidget(splitter_main);
        rightWidget->setObjectName("rightWidget");
        verticalLayout_3 = new QVBoxLayout(rightWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        splitter_right = new QSplitter(rightWidget);
        splitter_right->setObjectName("splitter_right");
        splitter_right->setOrientation(Qt::Orientation::Vertical);
        controlGroup = new QGroupBox(splitter_right);
        controlGroup->setObjectName("controlGroup");
        splitter_right->addWidget(controlGroup);
        codeArea = new QTextBrowser(splitter_right);
        codeArea->setObjectName("codeArea");
        splitter_right->addWidget(codeArea);

        verticalLayout_3->addWidget(splitter_right);

        splitter_main->addWidget(rightWidget);

        verticalLayout->addWidget(splitter_main);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 727, 18));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName("menu_F");
        menu_E = new QMenu(menubar);
        menu_E->setObjectName("menu_E");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_E->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        variableGroup->setTitle(QCoreApplication::translate("MainWindow", "\345\217\230\351\207\217\347\233\221\350\247\206", nullptr));
        controlGroup->setTitle(QCoreApplication::translate("MainWindow", "\346\216\247\345\210\266\351\235\242\346\235\277", nullptr));
        menu_F->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_E->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
