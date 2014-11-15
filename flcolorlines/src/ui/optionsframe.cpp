#include <iostream>

#include "optionsframe.h"
#include "ui_optionsframe.h"

#include "mainwindow.h"


OptionsFrame::OptionsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OptionsFrame)
{
    ui->setupUi(this);

    ui->label_c_max->setText( "<font color='gray'>"+ QString::number(ui->horizontalSlider_3->maximum())+"</font>");
    ui->label_c_min->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider_3->minimum()));
    ui->label_c_current->setText(QString::number(ui->horizontalSlider_3->value()));

    ui->label_hf_max->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider->maximum())+"</font>");
    ui->label_hf_min->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider->minimum())+"</font>");
    ui->label_hf_current->setText(QString::number(ui->horizontalSlider->value()));

    ui->label_vf_max->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider_2->maximum())+"</font>");
    ui->label_vf_min->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider_2->minimum())+"</font>");
    ui->label_vf_current->setText(QString::number(ui->horizontalSlider_2->value()));

    ui->label_n_max->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider_5->maximum())+"</font>");
    ui->label_n_min->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider_5->minimum())+"</font>");
    ui->label_n_current->setText(QString::number(ui->horizontalSlider_5->value()));

    ui->label_l_max->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider_4->maximum())+"</font>");
    ui->label_l_min->setText("<font color='gray'>"+ QString::number(ui->horizontalSlider_4->minimum())+"</font>");
    ui->label_l_current->setText(QString::number(ui->horizontalSlider_4->value()));

    ui->label_vf_current->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    ui->label_hf_current->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    ui->label_c_current->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    ui->label_l_current->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    ui->label_n_current->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    mainWindow = 0;

    //button events
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(clickedCancel()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(clickedNewGame()));

    //slider events
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(changedValue()));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(changedValue()));
    connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(changedValue()));
    connect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),this,SLOT(changedValue()));
    connect(ui->horizontalSlider_5,SIGNAL(valueChanged(int)),this,SLOT(changedValue()));
}

OptionsFrame::~OptionsFrame()
{
    delete ui;
}

void OptionsFrame::setMainWindow(MainWindow *mw){
    mainWindow = mw;
}

void OptionsFrame::closeEvent(QCloseEvent *evt)
{
    this->hide();
}

void OptionsFrame::reset(){

    ui->horizontalSlider->setValue(9);
    ui->horizontalSlider_2->setValue(9);
    ui->horizontalSlider_3->setValue(7);
    ui->horizontalSlider_4->setValue(5);
    ui->horizontalSlider_5->setValue(3);

    ui->label_vf_current->setText(QString::number(ui->horizontalSlider_2->value()));
    ui->label_hf_current->setText(QString::number(ui->horizontalSlider->value()));
    ui->label_c_current->setText(QString::number(ui->horizontalSlider_3->value()));
    ui->label_l_current->setText(QString::number(ui->horizontalSlider_4->value()));
    ui->label_n_current->setText(QString::number(ui->horizontalSlider_5->value()));
}

//slots
void OptionsFrame::clickedCancel(){
    this->hide();
    reset();
}

void OptionsFrame::clickedNewGame(){

    if(mainWindow != 0){
        mainWindow->startNewGame(ui->horizontalSlider->value(),ui->horizontalSlider_2->value(),ui->horizontalSlider_3->value(), ui->horizontalSlider_5->value(), ui->horizontalSlider_4->value());
    }

    this->hide();
    reset();

}

void OptionsFrame::changedValue(){
    ui->label_vf_current->setText(QString::number(ui->horizontalSlider_2->value()));
    ui->label_hf_current->setText(QString::number(ui->horizontalSlider->value()));
    ui->label_c_current->setText(QString::number(ui->horizontalSlider_3->value()));
    ui->label_l_current->setText(QString::number(ui->horizontalSlider_4->value()));
    ui->label_n_current->setText(QString::number(ui->horizontalSlider_5->value()));
}
