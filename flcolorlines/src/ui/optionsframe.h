#ifndef OPTIONSFRAME_H
#define OPTIONSFRAME_H

#include <QFrame>

class MainWindow;

namespace Ui {
class OptionsFrame;

}

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

#endif // OPTIONSFRAME_H
