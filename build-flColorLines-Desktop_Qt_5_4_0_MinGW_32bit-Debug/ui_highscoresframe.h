/********************************************************************************
** Form generated from reading UI file 'highscoresframe.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIGHSCORESFRAME_H
#define UI_HIGHSCORESFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HighscoresFrame
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonRestore;
    QPushButton *buttonClear;
    QSpacerItem *verticalSpacer;
    QPushButton *buttonClose;

    void setupUi(QFrame *HighscoresFrame)
    {
        if (HighscoresFrame->objectName().isEmpty())
            HighscoresFrame->setObjectName(QStringLiteral("HighscoresFrame"));
        HighscoresFrame->resize(515, 327);
        HighscoresFrame->setFrameShape(QFrame::StyledPanel);
        HighscoresFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(HighscoresFrame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView = new QTableView(HighscoresFrame);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEnabled(false);

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttonRestore = new QPushButton(HighscoresFrame);
        buttonRestore->setObjectName(QStringLiteral("buttonRestore"));

        verticalLayout->addWidget(buttonRestore);

        buttonClear = new QPushButton(HighscoresFrame);
        buttonClear->setObjectName(QStringLiteral("buttonClear"));

        verticalLayout->addWidget(buttonClear);

        verticalSpacer = new QSpacerItem(68, 277, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonClose = new QPushButton(HighscoresFrame);
        buttonClose->setObjectName(QStringLiteral("buttonClose"));

        verticalLayout->addWidget(buttonClose);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(HighscoresFrame);

        QMetaObject::connectSlotsByName(HighscoresFrame);
    } // setupUi

    void retranslateUi(QFrame *HighscoresFrame)
    {
        HighscoresFrame->setWindowTitle(QApplication::translate("HighscoresFrame", "Frame", 0));
        buttonRestore->setText(QApplication::translate("HighscoresFrame", "Restore Highscores", 0));
        buttonClear->setText(QApplication::translate("HighscoresFrame", "Clear Highscores", 0));
        buttonClose->setText(QApplication::translate("HighscoresFrame", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class HighscoresFrame: public Ui_HighscoresFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIGHSCORESFRAME_H
