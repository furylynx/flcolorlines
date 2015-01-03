#include "UI.MainWindow.hpp"
#include "ui_mainwindow.h"

using namespace ui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    GLFrame = new MyGLFrame();      // create our subclassed GLWidget
//    setCentralWidget(GLFrame);      // assign it to the central widget of the window
//    GLFrame->initRenderThread();    // start rendering

    // the example QGLWidget
    setCentralWidget(&GLFrame);
//    cube.setWindowTitle(QObject::tr("Cube"));
    // resize the widget
   GLFrame.resize(300, 300);
//    // and finally show it
//    cube.show();
   GLFrame.setMainWindow(this);

   controller = 0;
   hictrl = 0;


   optionsFrame = new OptionsFrame();
   optionsFrame->hide();
   optionsFrame->setMainWindow(this);

   highscoreFrame = new HighscoresFrame();
   highscoreFrame->hide();

    //connects
    connect(ui->actionExit_2, SIGNAL(triggered()), this, SLOT(clickedExit()));
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(clickedNewGame()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(clickedUndo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(clickedRedo()));
    connect(ui->actionHighscore, SIGNAL(triggered()), this,SLOT(clickedHighscore()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(clickedAbout()));
    connect(ui->menuActions, SIGNAL(aboutToShow()), this,SLOT(aboutToShowActions()));


}

MainWindow::~MainWindow()
{
    //delete GLFrame;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *evt)
{
    GLFrame.finishRendering();    // stop the thread before exiting

    if (hictrl != 0)
        hictrl->writeToFile();

    QMainWindow::closeEvent(evt);
}

controller::GameController* MainWindow::getGameController(){
    return controller;
}


void MainWindow::setGameController(controller::GameController *ctrl){
    controller = ctrl;
    GLFrame.setGameController(ctrl);
}

void MainWindow::setHighscoreController(controller::HighscoreController *c){
    hictrl = c;

    if (highscoreFrame != 0)
        highscoreFrame->setHighscoreController(c);
}

void MainWindow::startNewGame(int dimx, int dimy, int amount_colors, int amount_newballs, int amount_line){
    GLFrame.startNewGame(dimx,dimy,amount_colors,amount_newballs, amount_line);
}

void MainWindow::gameOver(){

    if (controller == 0 || hictrl == 0)
        return;

    int score = controller->getTheScore();

    //open dialog...
    bool ok;
    QString text2 = "unknown";
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                              tr("User name:"), QLineEdit::Normal,text2, &ok);

    std::ostringstream ostream;
    ostream << "Dim:" <<controller->getGameField()->getDimensionX()<< "x"<< controller->getGameField()->getDimensionY()<<"|Colors:"<<controller->getAmountColors()<< "|new:"<<controller->getAmountNewBalls() << "|line:"<<controller->getAmountLine();
    std::string field(ostream.str());

    if (ok && !text.isEmpty())
       hictrl->addEntry(score, text.toStdString(), field);

}

//slots
void MainWindow::clickedUndo(){
    GLFrame.undoAction();
}

void MainWindow::clickedRedo(){
    GLFrame.redoAction();
}


void MainWindow::clickedExit(){
    this->close();
}

void MainWindow::clickedAbout(){

}

void MainWindow::clickedNewGame(){
    optionsFrame->show();
}

void MainWindow::aboutToShowActions(){
    if (controller != 0){
        ui->actionUndo->setEnabled(controller->undoPossible());
        ui->actionRedo->setEnabled(controller->redoPossible());
    }
}

void MainWindow::clickedHighscore(){
    highscoreFrame->show();
}
