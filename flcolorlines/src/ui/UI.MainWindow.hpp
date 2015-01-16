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
    /**
     * Creates a new main window.
     *
     * @param parent The parent if any.
     */
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    /**
     * Returns the game controller.
     *
     * @return The controller
     */
    virtual controller::GameController* getGameController() const;

    /**
     * Sets the game controller.
     *
     * @param ctrl The controller
     */
    virtual void setGameController(controller::GameController* ctrl);

    /**
     * Sets the highscore controller.
     *
     * @param hc The controller
     */
    virtual void setHighscoreController(controller::HighscoreController* hc);

    /**
     * Starts a new game with the given options.
     *
     * @param dimx The x-dimension of the field.
     * @param dimy The y-dimension of the field.
     * @param amountColors The number of colors.
     * @param amountNewBalls The number of new balls on each turn.
     * @param amountLine The number of balls required for a complete line.
     */
    virtual void startNewGame(int dimx, int dimy, int amountColors, int amountNewBalls,int amountLine);

    /**
     * Initializes the game over part.
     */
    virtual void gameOver();

protected:
    /**
     * Handles the close event.
     *
     * @param evt The event args.
     */
    virtual void closeEvent(QCloseEvent *evt);

private:
    Ui::MainWindow *ui;
    GLWidget GLFrame;
    controller::GameController* controller;
    controller::HighscoreController* hictrl;

    OptionsFrame *optionsFrame;
    HighscoresFrame *highscoreFrame;

private slots:
    /**
     * Handles the undo event.
     */
    void clickedUndo();

    /**
     * Handles the redo event.
     */
    void clickedRedo();

    /**
     * Handles the new game event.
     */
    void clickedNewGame();

    /**
     * Handles the exit event.
     */
    void clickedExit();

    /**
     * Handles the about event.
     */
    void clickedAbout();

    /**
     * Handles the highscore event.
     */
    void clickedHighscore();

    /**
     * Handles the about to show actions event.
     */
    void aboutToShowActions();
};

}//namespace ui

#endif // MAINWINDOW_H
