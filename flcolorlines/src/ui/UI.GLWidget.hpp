/*
 *   Example implementation of a QGLWidget with a separat rendering thread
 *   and GL picking capabilites.
 *
 *   This is the QGLWidget subclass interface.
 *
 *   Copyright (C) 2005 by
 *   Michael Hanke        michael.hanke@gmail.com
 *
 *   This example combines two other examples on using Qt for OpenGL
 *   - QGLWidget example (single threaded, GL picking)
 *     from the book 'C++  GUI Programming with Qt 3' by
 *     Jasmin Blanchette and Mark Summerfield
 *     The example code 'cube' available from here:
 *        ftp://ftp.trolltech.com/misc/qtbook-examples.zip
 *   - Qt Quarterly article 'Glimpsing the Third Dimension' on multithreaded
 *     OpenGL with Qt (see here: http://doc.trolltech.com/qq/qq06-glimpsing.html)
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#ifndef EXAMPLEGLWIDGET_H
#define EXAMPLEGLWIDGET_H

//custom includes
#include "../controller/Controller.RenderThread.hpp"
#include "../controller/Controller.GameController.hpp"
//#include "UI.MainWindow.hpp"

//global includes
#include <qgl.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <qcolordialog.h>

#include <QMouseEvent>

namespace ui
{

//forward declaration of the MainWindow
class MainWindow;

/**
 * QGLWidget subclass with a separate rendering thread and GL picking capabilities.
 */
class GLWidget : public QGLWidget
{
public:
    /**
     * Creates a new widget.
     *
     * @param parent The parent if any.
     */
    GLWidget(QWidget *parent = nullptr);

    virtual ~GLWidget();

    /**
     * Starts the rendering thread. This method is called in the contructor.
     */
    void initRendering();

    /**
     * Stops the rendering thread of the widget.
     */
    void finishRendering();

    /**
     * Call this method before doing any OpenGL rendering from a thread.
     * This method will aquire the GL rendering context for the calling thread.
     * Rendering will only be possible from this thread until unlockGLContext()
     * is called from the same thread.
     */
    void lockGLContext();

    /**
     * Call this method to release the rendering context again after calling lockGLContext().
     */
    void unlockGLContext();

    /**
     * Returns a reference to the render wait condition.
     * This is only for internal purpose (render thread communication)
     */
    QWaitCondition& renderCondition();

    /**
     * Returns a reference to the render context mutex.
     * This is only for internal purpose (render thread communication)
     */
    QMutex& renderMutex();

    /**
     * Returns the game controller.
     *
     * @return The game controller.
     */
    controller::GameController* getGameController();

    /**
     * Sets the game controller.
     *
     * @param ctrl The game controller.
     */
    void setGameController(controller::GameController *ctrl);

    /**
     * Sets the main window.
     *
     * @param mw The main window.
     */
    void setMainWindow(MainWindow *mw);

    /**
     * Starts a new game.
     *
     * @param dimx The x-dimension.
     * @param dimy The y-dimension.
     * @param amountColors The number of colors.
     * @param amountNewBalls The number of new ball on each turn.
     * @param amountLine The number of balls in a line required to fill it.
     */
    void startNewGame(int dimx, int dimy, int amountColors, int amountNewBalls, int amountLine);

    /**
     * Undoes the last action.
     *
     * @return True if further undo possible.
     */
    bool undoAction();

    /**
     * Redoes the last action.
     *
     * @return True if further redo possible.
     */
    bool redoAction();

    /**
     * Initializes the game over part.
     */
    void gameOver();

public slots:
    /**
     * Cause the rendering thread to render one frame of the OpenGL scene. This method is thread save.
     *
     * \warning If the rendering thread is currently rendering (not idle) when this method is called
     * NO additional new frame will be rendered afterwards!
     */
    void render();

protected:
    /**
     * Handles mouse press events on the QGLWidget.
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * Handles mouse move events on the QGLWidget.
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * Handles mouse double click events on the QGLWidget.
     */
    void mouseDoubleClickEvent(QMouseEvent *event);

    /**
     * Performs a save shutdown if the widget recieves a close event.
     */
    void closeEvent(QCloseEvent* _e);

    /**
     * Calls render() if the widget recieves a paint event.
     */
    void paintEvent(QPaintEvent*);

    /**
     * Requests a GL viewport resize from the rendering thread.
     */
    void resizeEvent(QResizeEvent* _e);

private:
    /**
     * The rendering thread.
     */
    controller::RenderThread glt;

    /**
     * Mutex for protecting the GL rendering context for multithreading.
     */
    QMutex render_mutex;

    /**
     * The rendering thread uses this wait condition to save CPU ressources.
     */
    QWaitCondition render_condition;

    /**
     * The last position.
     */
    QPoint lastPos;


    /**
     * A pointer to the game controller.
     */
    controller::GameController *gcontroller;

    /**
     * A pointer to the main window.
     */
    MainWindow *mainwindow;
};

}//namespace ui

#endif // EXAMPLEGLWIDGET_H
