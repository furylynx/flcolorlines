#include <QResizeEvent>
#include <iostream>

#include "myglframe.h"

MyGLFrame::MyGLFrame(QWidget *parent) :
    QGLWidget(parent),
    RenderThread(this)
{
    setAutoBufferSwap(false);
}

MyGLFrame::~MyGLFrame()
{
}

void MyGLFrame::initRenderThread(void)
{
    doneCurrent();
    RenderThread.start();
}

void MyGLFrame::stopRenderThread(void)
{
    RenderThread.stop();
    RenderThread.wait();
}

void MyGLFrame::resizeEvent(QResizeEvent *evt)
{
    RenderThread.resizeViewport(evt->size());
}

void MyGLFrame::paintEvent(QPaintEvent *)
{
    // Do nothing. Let the thread do the work
}

void MyGLFrame::closeEvent(QCloseEvent *evt)
{
    stopRenderThread();
    QGLWidget::closeEvent(evt);
}

void MyGLFrame::mousePressEvent(QMouseEvent *event){
    std::cout << "mouse has been pressed: ("<< event->x() << ","<<event->y() << "); button: "<<event->button() <<"\n";//works

    if (event->button() == 1)
        RenderThread.gl_select(event->x(),event->y());
    //todo

}

