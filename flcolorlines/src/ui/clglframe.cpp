#include <QResizeEvent>

#include "clglframe.h"

CLGLFrame::CLGLFrame(QWidget *parent) :
    QGLWidget(parent),
    renderThread(this)
{
    setAutoBufferSwap(false);
}

CLGLFrame::~CLGLFrame()
{
}

void CLGLFrame::initRenderThread(void)
{
    doneCurrent();
    renderThread.start();
}

void CLGLFrame::stopRenderThread(void)
{
    renderThread.stop();
    renderThread.wait();
}

void CLGLFrame::resizeEvent(QResizeEvent *evt)
{
    renderThread.resizeViewport(evt->size());
}

void CLGLFrame::paintEvent(QPaintEvent *)
{
    // Do nothing. Let the thread do the work
}

void CLGLFrame::closeEvent(QCloseEvent *evt)
{
    stopRenderThread();
    QGLWidget::closeEvent(evt);
}
