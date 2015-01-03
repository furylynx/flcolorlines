/********************************************************************************
** Form generated from reading UI file 'highscoreframe.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIGHSCOREFRAME_H
#define UI_HIGHSCOREFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HighscoreFrame
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonRestore;
    QPushButton *buttonClear;
    QSpacerItem *verticalSpacer;
    QPushButton *buttonClose;

    void setupUi(QWidget *HighscoreFrame)
    {
        if (HighscoreFrame->objectName().isEmpty())
            HighscoreFrame->setObjectName(QStringLiteral("HighscoreFrame"));
        HighscoreFrame->resize(526, 300);
        horizontalLayout = new QHBoxLayout(HighscoreFrame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(HighscoreFrame);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttonRestore = new QPushButton(HighscoreFrame);
        buttonRestore->setObjectName(QStringLiteral("buttonRestore"));

        verticalLayout->addWidget(buttonRestore);

        buttonClear = new QPushButton(HighscoreFrame);
        buttonClear->setObjectName(QStringLiteral("buttonClear"));

        verticalLayout->addWidget(buttonClear);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonClose = new QPushButton(HighscoreFrame);
        buttonClose->setObjectName(QStringLiteral("buttonClose"));

        verticalLayout->addWidget(buttonClose);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(HighscoreFrame);

        QMetaObject::connectSlotsByName(HighscoreFrame);
    } // setupUi

    void retranslateUi(QWidget *HighscoreFrame)
    {
        HighscoreFrame->setWindowTitle(QApplication::translate("HighscoreFrame", "Highscores", 0));
        buttonRestore->setText(QApplication::translate("HighscoreFrame", "Restore Highscores", 0));
        buttonClear->setText(QApplication::translate("HighscoreFrame", "Clear Highscores", 0));
        buttonClose->setText(QApplication::translate("HighscoreFrame", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class HighscoreFrame: public Ui_HighscoreFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIGHSCOREFRAME_H
