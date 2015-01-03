//custom includes
#include "ui/UI.MainWindow.hpp"
#include "controller/Controller.GameController.hpp"
#include "controller/Controller.HighscoreController.hpp"

//global includes
#include <iostream>
#include <cstdlib>

#include <QApplication>

#include <GL/glut.h>

#ifdef Q_OS_UNIX
    //include the xlib for linux
    #include <X11/Xlib.h>
#endif


//the main method

int main(int argc, char *argv[])
{

    srand(time(0));

    glutInit(&argc, argv);

    #ifdef Q_OS_UNIX
    //initialize the x threads for linux
    XInitThreads();
    #endif

    controller::GameController* controller = new controller::GameController();

    controller::HighscoreController* hictrl = new controller::HighscoreController();
    hictrl->setStandardPath("crypt.sav");
    hictrl->readFromFile();

    QApplication a(argc, argv);
    ui::MainWindow w;
    w.setGameController(controller);
    w.setHighscoreController(hictrl);

    //w.window
    w.show();

    int result = a.exec();

    delete controller;
    controller = nullptr;

    delete hictrl;
    hictrl = nullptr;
    
    return result;
}
