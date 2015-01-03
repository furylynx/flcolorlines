#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//custom includes
#include "UI.GLWidget.hpp"
#include "UI.OptionsFrame.hpp"
#include "UI.HighscoresFrame.hpp"

#include "../controller/Controller.GameController.hpp"


//global includes
#include <iostream>
#include <sstream>

#include <QInputDialog>
#include <QMainWindow>


//forward declaration of the generated class
namespace Ui
{
    class MainWindow;
}

namespace ui
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    controller::GameController* getGameController();
    void setGameController(controller::GameController* ctrl);
    void setHighscoreController(controller::HighscoreController* hc);

    void startNewGame(int dimx, int dimy, int amount_colors, int amount_newballs,int amount_line);
    void gameOver();

protected:
    void closeEvent(QCloseEvent *evt);

private:
    Ui::MainWindow *ui;
    GLWidget GLFrame;
    controller::GameController* controller;
    controller::HighscoreController* hictrl;

    OptionsFrame *optionsFrame;
    HighscoresFrame *highscoreFrame;

private slots:
    void clickedUndo();
    void clickedRedo();
    void clickedNewGame();
    void clickedExit();
    void clickedAbout();
    void clickedHighscore();

    void aboutToShowActions();
};

}//namespace ui

#endif // MAINWINDOW_H
