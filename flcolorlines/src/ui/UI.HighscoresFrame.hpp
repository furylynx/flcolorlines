#ifndef HIGHSCORESFRAME_H
#define HIGHSCORESFRAME_H

//custom includes
#include "../controller/Controller.HighscoreController.hpp"
//#include "UI.MainWindow.hpp"

//global includes
#include <sstream>
#include <fstream>

#include <QFrame>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui
{
    class HighscoresFrame;
}

namespace ui
{

//forward declaration of the MainWindow
class MainWindow;

class HighscoresFrame : public QFrame
{
    Q_OBJECT
    
public:
    /**
     * Creates a new highscore window.
     *
     * @param parent The parent of this window.
     */
    explicit HighscoresFrame(QWidget *parent = nullptr);
    virtual ~HighscoresFrame();
    
    /**
     * Sets the highscore controller.
     *
     * @param c The controller.
     */
    virtual void setHighscoreController(controller::HighscoreController *c);

    /**
     * Shows this window.
     */
    virtual void show();

protected:
    /**
     * Handles the close event.
     *
     * @param evt The event arg.
     */
    virtual void closeEvent(QCloseEvent *evt);

private:
    /**
     * The ui highscore frame.
     */
    Ui::HighscoresFrame *ui;

    /**
     * A pointer to the highscore controller.
     */
    controller::HighscoreController *hictrl;

    /**
     * Handles the show event.
     */
    void onShow();

private slots:
    /**
     * Handles the close button event.
     */
    void clickedClose();

    /**
     * Handles the clear event.
     */
    void clickedClear();

    /**
     * Handles the restore event.
     */
    void clickedRestore();

};

}//namespace ui

#endif // HIGHSCORESFRAME_H
