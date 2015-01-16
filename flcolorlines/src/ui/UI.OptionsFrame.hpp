#ifndef OPTIONSFRAME_H
#define OPTIONSFRAME_H

//custom includes
//#include "UI.MainWindow.hpp"

//global includes
#include <QFrame>
#include <iostream>


//forward declaration of the generated class
namespace Ui
{
    class OptionsFrame;
}

namespace ui
{

//forward declaration of the MainWindow
class MainWindow;

class OptionsFrame : public QFrame
{
    Q_OBJECT
    
public:
    /**
     * Creates the options frame
     *
     * @param parent The parent if any.
     */
    explicit OptionsFrame(QWidget *parent = nullptr);
    virtual ~OptionsFrame();

    /**
     * Sets the main window.
     *
     * @param mw The main window.
     */
    virtual void setMainWindow(MainWindow *mw);
    
protected:

    /**
     * Handles the close event.
     *
     * @param evt The event args.
     */
    virtual void closeEvent(QCloseEvent *evt);

private:
    /**
     * The ui options frame.
     */
    Ui::OptionsFrame *ui;

    /**
     * A pointer to the main window.
     */
    MainWindow *mainWindow;

    /**
     * Resets the options.
     */
    void reset();

private slots:

    /**
     * Handles the cancel event.
     */
    void clickedCancel();

    /**
     * Handles the new game event.
     */
    void clickedNewGame();

    /**
     * Handles the changed value event.
     */
    void changedValue();
};

}//namespace ui

#endif // OPTIONSFRAME_H
