#ifndef HIGHSCOREFRAME_H
#define HIGHSCOREFRAME_H

#include <QFrame>

#include "Controller.HighscoreController.h"

namespace Ui {
class HighscoreFrame;
}

class HighscoreFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit HighscoreFrame(QWidget *parent = 0);
    ~HighscoreFrame();

    void setHighscoreController(controller::HighscoreController *c);
//    void show();

protected:
    void closeEvent(QCloseEvent *evt);
    
private:
    Ui::HighscoreFrame *ui;
    controller::HighscoreController *hictrl = 0;

    void onShow();

private slots:    
    void clickedClose();
    void clickedClear();
    void clickedRestore();

};

#endif // HIGHSCOREFRAME_H
