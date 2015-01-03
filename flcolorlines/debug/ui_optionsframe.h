/********************************************************************************
** Form generated from reading UI file 'optionsframe.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSFRAME_H
#define UI_OPTIONSFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OptionsFrame
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_l_current;
    QLabel *label_n_current;
    QLabel *label_5;
    QLabel *label_vf_current;
    QSlider *horizontalSlider;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_vf_max;
    QLabel *label;
    QLabel *label_c_min;
    QLabel *label_vf_min;
    QSlider *horizontalSlider_2;
    QLabel *label_c_current;
    QLabel *label_hf_min;
    QLabel *label_hf_max;
    QLabel *label_c_max;
    QSlider *horizontalSlider_3;
    QLabel *label_hf_current;
    QSlider *horizontalSlider_4;
    QLabel *label_l_max;
    QLabel *label_l_min;
    QLabel *label_7;
    QLabel *label_n_min;
    QLabel *label_n_max;
    QSlider *horizontalSlider_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QFrame *OptionsFrame)
    {
        if (OptionsFrame->objectName().isEmpty())
            OptionsFrame->setObjectName(QStringLiteral("OptionsFrame"));
        OptionsFrame->resize(490, 251);
        OptionsFrame->setFrameShape(QFrame::StyledPanel);
        OptionsFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(OptionsFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_l_current = new QLabel(OptionsFrame);
        label_l_current->setObjectName(QStringLiteral("label_l_current"));

        gridLayout->addWidget(label_l_current, 10, 2, 1, 1);

        label_n_current = new QLabel(OptionsFrame);
        label_n_current->setObjectName(QStringLiteral("label_n_current"));

        gridLayout->addWidget(label_n_current, 12, 2, 1, 1);

        label_5 = new QLabel(OptionsFrame);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 11, 0, 1, 1);

        label_vf_current = new QLabel(OptionsFrame);
        label_vf_current->setObjectName(QStringLiteral("label_vf_current"));

        gridLayout->addWidget(label_vf_current, 4, 2, 1, 1);

        horizontalSlider = new QSlider(OptionsFrame);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(3);
        horizontalSlider->setMaximum(18);
        horizontalSlider->setValue(9);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 3, 2, 1, 1);

        label_2 = new QLabel(OptionsFrame);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 6, 0, 1, 1);

        label_3 = new QLabel(OptionsFrame);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 9, 0, 1, 1);

        label_vf_max = new QLabel(OptionsFrame);
        label_vf_max->setObjectName(QStringLiteral("label_vf_max"));
        label_vf_max->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label_vf_max, 6, 3, 1, 1);

        label = new QLabel(OptionsFrame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        label_c_min = new QLabel(OptionsFrame);
        label_c_min->setObjectName(QStringLiteral("label_c_min"));
        label_c_min->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label_c_min, 9, 1, 1, 1);

        label_vf_min = new QLabel(OptionsFrame);
        label_vf_min->setObjectName(QStringLiteral("label_vf_min"));
        label_vf_min->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label_vf_min, 6, 1, 1, 1);

        horizontalSlider_2 = new QSlider(OptionsFrame);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setMinimum(3);
        horizontalSlider_2->setMaximum(18);
        horizontalSlider_2->setValue(9);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_2, 6, 2, 1, 1);

        label_c_current = new QLabel(OptionsFrame);
        label_c_current->setObjectName(QStringLiteral("label_c_current"));

        gridLayout->addWidget(label_c_current, 7, 2, 1, 1);

        label_hf_min = new QLabel(OptionsFrame);
        label_hf_min->setObjectName(QStringLiteral("label_hf_min"));
        label_hf_min->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label_hf_min, 3, 1, 1, 1);

        label_hf_max = new QLabel(OptionsFrame);
        label_hf_max->setObjectName(QStringLiteral("label_hf_max"));
        label_hf_max->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label_hf_max, 3, 3, 1, 1);

        label_c_max = new QLabel(OptionsFrame);
        label_c_max->setObjectName(QStringLiteral("label_c_max"));
        label_c_max->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label_c_max, 9, 3, 1, 1);

        horizontalSlider_3 = new QSlider(OptionsFrame);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setAutoFillBackground(false);
        horizontalSlider_3->setMinimum(1);
        horizontalSlider_3->setMaximum(12);
        horizontalSlider_3->setValue(7);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_3, 9, 2, 1, 1);

        label_hf_current = new QLabel(OptionsFrame);
        label_hf_current->setObjectName(QStringLiteral("label_hf_current"));

        gridLayout->addWidget(label_hf_current, 2, 2, 1, 1);

        horizontalSlider_4 = new QSlider(OptionsFrame);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setMinimum(2);
        horizontalSlider_4->setMaximum(7);
        horizontalSlider_4->setValue(5);
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_4, 11, 2, 1, 1);

        label_l_max = new QLabel(OptionsFrame);
        label_l_max->setObjectName(QStringLiteral("label_l_max"));

        gridLayout->addWidget(label_l_max, 11, 3, 1, 1);

        label_l_min = new QLabel(OptionsFrame);
        label_l_min->setObjectName(QStringLiteral("label_l_min"));

        gridLayout->addWidget(label_l_min, 11, 1, 1, 1);

        label_7 = new QLabel(OptionsFrame);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 14, 0, 1, 1);

        label_n_min = new QLabel(OptionsFrame);
        label_n_min->setObjectName(QStringLiteral("label_n_min"));

        gridLayout->addWidget(label_n_min, 14, 1, 1, 1);

        label_n_max = new QLabel(OptionsFrame);
        label_n_max->setObjectName(QStringLiteral("label_n_max"));

        gridLayout->addWidget(label_n_max, 14, 3, 1, 1);

        horizontalSlider_5 = new QSlider(OptionsFrame);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setMinimum(1);
        horizontalSlider_5->setMaximum(5);
        horizontalSlider_5->setValue(3);
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_5, 14, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(OptionsFrame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(OptionsFrame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OptionsFrame);

        QMetaObject::connectSlotsByName(OptionsFrame);
    } // setupUi

    void retranslateUi(QFrame *OptionsFrame)
    {
        OptionsFrame->setWindowTitle(QApplication::translate("OptionsFrame", "New Game Settings", 0));
        label_l_current->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_n_current->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_5->setText(QApplication::translate("OptionsFrame", "Line length:", 0));
        label_vf_current->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_2->setText(QApplication::translate("OptionsFrame", "Vertical field size:", 0));
        label_3->setText(QApplication::translate("OptionsFrame", "Different colors:", 0));
        label_vf_max->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label->setText(QApplication::translate("OptionsFrame", "Horizontal field size:", 0));
        label_c_min->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_vf_min->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_c_current->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_hf_min->setText(QApplication::translate("OptionsFrame", "lbl", 0));
        label_hf_max->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_c_max->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_hf_current->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_l_max->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_l_min->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_7->setText(QApplication::translate("OptionsFrame", "Amount new balls:", 0));
        label_n_min->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        label_n_max->setText(QApplication::translate("OptionsFrame", "TextLabel", 0));
        pushButton_2->setText(QApplication::translate("OptionsFrame", "Cancel", 0));
        pushButton->setText(QApplication::translate("OptionsFrame", "Start Game", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsFrame: public Ui_OptionsFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSFRAME_H
