#include <qgl.h>
#include <GL/glu.h>

#include "renderingthread.h"
#include "clglframe.h"


RenderingThread::RenderingThread(CLGLFrame *_GLFrame) :
    QThread(),
    GLFrame(_GLFrame)
{
    doRendering = true;
    doResize = false;
    FrameCounter=0;
}

void RenderingThread::resizeViewport(const QSize &size)
{
    w = size.width();
    h = size.height();
    doResize = true;
}

void RenderingThread::stop()
{
    doRendering = false;
}


void RenderingThread::run()
{
    GLFrame->makeCurrent();
    GLInit();

    while (doRendering)
        {
        if (doResize)
            {
            GLResize(w, h);
            doResize = false;
            }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        paintGL(); // render actual frame

        FrameCounter++;
        GLFrame->swapBuffers();

        msleep(16); // wait 16ms => about 60 FPS
        }
}


void RenderingThread::GLInit(void)
{
    glClearColor(0.05f, 0.05f, 0.1f, 0.0f);     // Background => dark blue
}


void RenderingThread::GLResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.,((GLfloat)width)/((GLfloat)height),0.1f,1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void RenderingThread::paintGL(void)
{
    glTranslatef(0.0f, 0.0f, -5.0f);            // move 5 units into the screen
    glRotatef(FrameCounter,0.0f,0.0f,1.0f);     // rotate z-axis
    glBegin(GL_QUADS);
        glColor3f(1.,1.,0.); glVertex3f(-1.0, -1.0,0.0);
        glColor3f(1.,1.,1.); glVertex3f(1.0, -1.0,0.0);
        glColor3f(1.,0.,1.); glVertex3f(1.0, 1.0,0.0);
        glColor3f(1.,0.,0.); glVertex3f(-1.0, 1.0,0.0);
    glEnd();

}
