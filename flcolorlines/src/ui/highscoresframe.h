#ifndef HIGHSCORESFRAME_H
#define HIGHSCORESFRAME_H

#include <QFrame>

#include "Controller.HighscoreController.h"

namespace Ui {
class HighscoresFrame;
}

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

#endif // HIGHSCORESFRAME_H
