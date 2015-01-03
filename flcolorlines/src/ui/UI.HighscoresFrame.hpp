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
    explicit HighscoresFrame(QWidget *parent = 0);
    ~HighscoresFrame();
    
    void setHighscoreController(controller::HighscoreController *c);
    void show();

protected:
    void closeEvent(QCloseEvent *evt);

private:
    Ui::HighscoresFrame *ui;
    controller::HighscoreController *hictrl;

    void onShow();

private slots:
    void clickedClose();
    void clickedClear();
    void clickedRestore();

};

}//namespace ui

#endif // HIGHSCORESFRAME_H
