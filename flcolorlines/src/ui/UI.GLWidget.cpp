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
#include "UI.GLWidget.hpp"
#include "UI.MainWindow.hpp"

using namespace ui;


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent),
    glt(*this)
{
    gcontroller = 0;
    mainwindow = 0;

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    // Buffer swap is handled in the rendering thread
    setAutoBufferSwap(false);

    //TODO causes a crash since the window is not fully rendered; render before moving to thread...
    doneCurrent();
    context()->moveToThread(&glt);

    // start the rendering thread
    initRendering();

    //track the mouse always (not only after mouse pressed event)
    setMouseTracking(true);
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
    {
        lastPos = event->pos();
    }
    else
    {

        //handle rendering in thead
        glt.selectField(event->pos());

//        int face = glt.faceAtPosition(event->pos());
//        glt.setSelectedField(face);
        render();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
    {
        GLfloat dx = (GLfloat)(event->x() - lastPos.x()) / width();
        GLfloat dy = (GLfloat)(event->y() - lastPos.y()) / height();

        if (event->buttons() & Qt::RightButton)
        {
            glt.setRotation(180 * dy, 0.0 , 180 * dx);
            //glt.setRotation(180 * dy,0.0,180 * dx);

            render();
        }
        lastPos = event->pos();

    }
    else
    {
        glt.hoverField(event->pos());
//        int face = glt.faceAtPosition(event->pos());
//        glt.setHoveredField(face);

        render();
    }
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
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

void GLWidget::initRendering( )
{
    // start the rendering thread
    glt.start();
    // wake the waiting render thread
    renderCondition().wakeAll();
}

void GLWidget::finishRendering( )
{
    // request stopping
    glt.stop();
    // wake up render thread to actually perform stopping
    renderCondition().wakeAll();
    // wait till the thread has exited
    glt.wait();
}

void GLWidget::closeEvent( QCloseEvent * _e )
{
    // request stopping
    finishRendering();
    // close the widget (base class)
    QGLWidget::closeEvent(_e);
}

void GLWidget::paintEvent( QPaintEvent * )
{
    //handle rendering in thead
    doneCurrent();
    context()->moveToThread(&glt);

    render();
}

void GLWidget::resizeEvent( QResizeEvent * _e )
{
    // signal the rendering thread that a resize is needed
    glt.resizeViewport(_e->size());

    //handle rendering in thead
    doneCurrent();
    context()->moveToThread(&glt);

    render();
}

void GLWidget::lockGLContext( )
{
    // lock the render mutex for the calling thread
    renderMutex().lock();
    // make the render context current for the calling thread
    makeCurrent();
}

void GLWidget::unlockGLContext( )
{
    // release the render context for the calling thread
    // to make it available for other threads
    doneCurrent();
    // unlock the render mutex for the calling thread
    renderMutex().unlock();
}

void GLWidget::render( )
{
    // let the wait condition wake up the waiting thread
    renderCondition().wakeAll();
}

QWaitCondition & GLWidget::renderCondition( )
{
    return(render_condition);
}

QMutex & GLWidget::renderMutex( )
{
    return(render_mutex);
}

controller::GameController* GLWidget::getGameController()
{
    return gcontroller;
}

void GLWidget::setGameController(controller::GameController *ctrl)
{
    gcontroller = ctrl;
}

void GLWidget::setMainWindow(MainWindow *mw)
{
    this->mainwindow = mw;
}

void GLWidget::startNewGame(int dimx, int dimy, int amount_colors, int amount_newballs, int amount_line)
{
    if (gcontroller != nullptr)
    {
        gcontroller->setOptions(dimx,dimy,amount_colors, amount_newballs, amount_line);
        gcontroller->startNewMatch();

        glt.beginInitialAnimation();

        render();
    }
}

bool GLWidget::undoAction()
{
    bool furtherUndo = false;

    if (gcontroller != nullptr)
    {
        furtherUndo = gcontroller->undoLastTurn();
    }

    render();

    return furtherUndo;

}

bool GLWidget::redoAction()
{
    bool furtherRedo = false;
    if (gcontroller != nullptr)
    {
        furtherRedo = gcontroller->redoLastTurn();
    }

    render();

    return furtherRedo;
}

void GLWidget::gameOver()
{
    if (mainwindow != 0)
    {
        mainwindow->gameOver();
    }
}
