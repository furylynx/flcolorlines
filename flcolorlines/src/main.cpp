#include <QApplication>
#include <iostream>
#include <cstdlib>

#include <GL/glut.h>

#include "mainwindow.h"

#ifdef Q_WS_X11
    #include <X11/Xlib.h> //include the xlib for linux
#endif

#include "Controller.GameController.h"
#include "Controller.HighscoreController.h"


int main(int argc, char *argv[])
 {

    srand(time(0));

    glutInit(&argc, argv);

    #ifdef Q_WS_X11
    XInitThreads();//initialize the x threads for linux
    #endif

    controller::GameController* controller = new controller::GameController();
//    controller->setOptions(9,9,7,3,5);//todo remove (no initial field)
//    controller->startNewMatch();

    controller::HighscoreController* hictrl = new controller::HighscoreController();
    hictrl->setStandardPath("crypt.sav");
    hictrl->readFromFile();

    QApplication a(argc, argv);
    MainWindow w;
    w.setGameController(controller);
    w.setHighscoreController(hictrl);

    //w.window
    w.show();


    
    return a.exec();
}
