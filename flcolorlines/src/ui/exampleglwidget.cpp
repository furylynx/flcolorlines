/*
 *   Example implementation of a QGLWidget with a separat rendering thread
 *   and GL picking capabilites.
 *
 *   This is the QGLWidget subclass implementation.
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
#include <qcolordialog.h>
#include <QMouseEvent>

#include "exampleglwidget.h"
#include "examplerenderthread.h"

#include "mainwindow.h"

ExampleGLWidget::ExampleGLWidget(QWidget *parent)
    : QGLWidget(parent),
    glt(*this)

{
    gcontroller = 0;
    mainwindow = 0;

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    // Buffer swap is handled in the rendering thread
    setAutoBufferSwap(false);

    // start the rendering thread
    initRendering();

    //track the mouse always (not only after mouse pressed event)
    setMouseTracking(true);
}


void ExampleGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
        lastPos = event->pos();
    else{
        int face = glt.faceAtPosition(event->pos());

        glt.setSelectedField(face);
        render();
    }

}

void ExampleGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
    {
        GLfloat dx = (GLfloat)(event->x() - lastPos.x()) / width();
        GLfloat dy = (GLfloat)(event->y() - lastPos.y()) / height();

        if (event->buttons() & Qt::RightButton)
        {
            glt.setRotation(180 * dy, 0.0 , 180 * dx); //glt.setRotation(180 * dy,0.0,180 * dx); //
            render();
        }
        lastPos = event->pos();

    }
    else{

        int face = glt.faceAtPosition(event->pos());
        glt.setHoveredField(face);
        render();
    }
}

void ExampleGLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    // get the name of the clicked surface
    int face = glt.faceAtPosition(event->pos());
    if (face != -1)
    {
//        QColor color = QColorDialog::getColor(glt.faceColors[face],
//                                              this);
//        if (color.isValid())
//        {
//            glt.faceColors[face] = color;
//        }
    }
}

void ExampleGLWidget::initRendering( )
{
    // start the rendering thread
    glt.start();
    // wake the waiting render thread
    renderCondition().wakeAll();
}

void ExampleGLWidget::finishRendering( )
{
    // request stopping
    glt.stop();
    // wake up render thread to actually perform stopping
    renderCondition().wakeAll();
    // wait till the thread has exited
    glt.wait();
}

void ExampleGLWidget::closeEvent( QCloseEvent * _e )
{
    // request stopping
    finishRendering();
    // close the widget (base class)
    QGLWidget::closeEvent(_e);
}

void ExampleGLWidget::paintEvent( QPaintEvent * )
{
    render();
}

void ExampleGLWidget::resizeEvent( QResizeEvent * _e )
{
    // signal the rendering thread that a resize is needed
    glt.resizeViewport(_e->size());

    render();
}

void ExampleGLWidget::lockGLContext( )
{
    // lock the render mutex for the calling thread
    renderMutex().lock();
    // make the render context current for the calling thread
    makeCurrent();
}

void ExampleGLWidget::unlockGLContext( )
{
    // release the render context for the calling thread
    // to make it available for other threads
    doneCurrent();
    // unlock the render mutex for the calling thread
    renderMutex().unlock();
}

void ExampleGLWidget::render( )
{
    // let the wait condition wake up the waiting thread
    renderCondition().wakeAll();
}

QWaitCondition & ExampleGLWidget::renderCondition( )
{
    return(render_condition);
}

QMutex & ExampleGLWidget::renderMutex( )
{
    return(render_mutex);
}

controller::GameController* ExampleGLWidget::getGameController(){
    return gcontroller;
}

void ExampleGLWidget::setGameController(controller::GameController *ctrl){
    gcontroller = ctrl;
}

void ExampleGLWidget::setMainWindow(MainWindow *mw){
    this->mainwindow = mw;
}

void ExampleGLWidget::startNewGame(int dimx, int dimy, int amount_colors, int amount_newballs, int amount_line){
    if (gcontroller != 0){
        gcontroller->setOptions(dimx,dimy,amount_colors, amount_newballs, amount_line);
        gcontroller->startNewMatch();

        glt.beginInitialAnimation();
        render();
    }
}

bool ExampleGLWidget::undoAction(){
    bool furtherUndo = false;

    if (gcontroller != 0)
        furtherUndo = gcontroller->undoLastTurn();

    render();

    return furtherUndo;

}

bool ExampleGLWidget::redoAction(){
    bool furtherRedo = false;
    if (gcontroller != 0)
        furtherRedo = gcontroller->redoLastTurn();

    render();

    return furtherRedo;
}

void ExampleGLWidget::gameOver(){

    if (mainwindow != 0)
        mainwindow->gameOver();

}
