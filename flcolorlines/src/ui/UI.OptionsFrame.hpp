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
    explicit OptionsFrame(QWidget *parent = 0);
    ~OptionsFrame();

    void setMainWindow(MainWindow *mw);
    
protected:
    void closeEvent(QCloseEvent *evt);

private:
    Ui::OptionsFrame *ui;
    void reset();
    MainWindow *mainWindow;

private slots:
    void clickedCancel();
    void clickedNewGame();
    void changedValue();
};

}//namespace ui

#endif // OPTIONSFRAME_H
