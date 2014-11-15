
#include <QStandardItemModel>
#include <QStandardItem>

#include <sstream>
#include <fstream>

#include "highscoresframe.h"
#include "ui_highscoresframe.h"

HighscoresFrame::HighscoresFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HighscoresFrame)
{
    ui->setupUi(this);

    hictrl = 0;

        QStandardItemModel *model = new QStandardItemModel(0,2,this);



        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Score")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Field")));

        ui->tableView->setModel(model);

        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

        ui->tableView->setEnabled(true);

        connect(ui->buttonClear, SIGNAL(clicked()),this,SLOT(clickedClear()));
        connect(ui->buttonClose, SIGNAL(clicked()),this,SLOT(clickedClose()));
        connect(ui->buttonRestore, SIGNAL(clicked()),this,SLOT(clickedRestore()));
}

HighscoresFrame::~HighscoresFrame()
{
    delete ui;
}

void HighscoresFrame::closeEvent(QCloseEvent *evt){
    this->hide();
}


void HighscoresFrame::show(){
    onShow();
    QWidget::show();

//    ((QWidget*)this)->show();
}

void HighscoresFrame::setHighscoreController(controller::HighscoreController *c){
    this->hictrl = c;
}

void HighscoresFrame::onShow(){

    //laod highscores from controller
    if (hictrl != 0)
    {
        std::vector<model::HighscoreEntry> entries = hictrl->getEntries();

        ((QStandardItemModel*)ui->tableView->model())->removeRows(0,((QStandardItemModel*)ui->tableView->model())->rowCount());

        for (int i = 0; i<entries.size();i++){

            //convert int score to string
            std::ostringstream ostream;
            ostream << entries[i].score;
            std::string score(ostream.str());

            QStandardItem *firstRowA = new QStandardItem(QString(entries[i].name.c_str()));
            QStandardItem *firstRowB = new QStandardItem(QString(score.c_str()));
            QStandardItem *firstRowC = new QStandardItem(QString(entries[i].field.c_str()));

            ((QStandardItemModel*)ui->tableView->model())->appendRow(firstRowA);
            ((QStandardItemModel*)ui->tableView->model())->setItem(i,1,firstRowB);
            ((QStandardItemModel*)ui->tableView->model())->setItem(i,2,firstRowC);
        }
    }

    std::ostringstream ostream;
    ostream << hictrl->getStandardPath() << ".bak";
    std::string path(ostream.str());

    std::ifstream infile(path.c_str());
    ui->buttonRestore->setEnabled(infile);
    infile.close();

}

void HighscoresFrame::clickedClear(){
    if (hictrl != 0){

        std::ostringstream ostream;
        ostream << hictrl->getStandardPath() << ".bak";
        std::string path(ostream.str());

        hictrl->writeToFile(path);

        hictrl->clear();
        hictrl->writeToFile();

        this->onShow();
    }
}

void HighscoresFrame::clickedClose(){
    this->close();
}

void HighscoresFrame::clickedRestore(){

    if (hictrl != 0){
        std::ostringstream ostream;
        ostream << hictrl->getStandardPath() << ".bak";
        std::string path(ostream.str());

        std::ifstream infile(path.c_str());
        if (infile){

            infile.close();

            hictrl->readFromFile(path.c_str());

            std::remove(path.c_str());
        }

        this->onShow();
    }

}
