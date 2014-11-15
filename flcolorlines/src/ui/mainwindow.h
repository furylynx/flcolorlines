#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "exampleglwidget.h"
#include "Controller.GameController.h"
#include "optionsframe.h"
#include "highscoresframe.h"

//class ExampleGLWidget;

namespace Ui {
    class MainWindow;
}

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
    ExampleGLWidget GLFrame;
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

#endif // MAINWINDOW_H
