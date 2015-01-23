/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Game;
    QAction *actionExit;
    QAction *actionExit_2;
    QAction *actionInfo;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionHighscore;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuNew;
    QMenu *menuActions;
    QMenu *menuHighscore;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(517, 291);
        actionNew_Game = new QAction(MainWindow);
        actionNew_Game->setObjectName(QStringLiteral("actionNew_Game"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit_2 = new QAction(MainWindow);
        actionExit_2->setObjectName(QStringLiteral("actionExit_2"));
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionHighscore = new QAction(MainWindow);
        actionHighscore->setObjectName(QStringLiteral("actionHighscore"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 517, 25));
        menuNew = new QMenu(menuBar);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        menuActions = new QMenu(menuBar);
        menuActions->setObjectName(QStringLiteral("menuActions"));
        menuHighscore = new QMenu(menuBar);
        menuHighscore->setObjectName(QStringLiteral("menuHighscore"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuNew->menuAction());
        menuBar->addAction(menuActions->menuAction());
        menuBar->addAction(menuHighscore->menuAction());
        menuNew->addAction(actionNew_Game);
        menuNew->addSeparator();
        menuNew->addAction(actionExit_2);
        menuActions->addAction(actionUndo);
        menuActions->addAction(actionRedo);
        menuHighscore->addAction(actionHighscore);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ColorLines", 0));
        actionNew_Game->setText(QApplication::translate("MainWindow", "New Game", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionExit_2->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionInfo->setText(QApplication::translate("MainWindow", "Info", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0));
        actionHighscore->setText(QApplication::translate("MainWindow", "Highscores", 0));
        menuNew->setTitle(QApplication::translate("MainWindow", "Game", 0));
        menuActions->setTitle(QApplication::translate("MainWindow", "Actions", 0));
        menuHighscore->setTitle(QApplication::translate("MainWindow", "Highscores", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
