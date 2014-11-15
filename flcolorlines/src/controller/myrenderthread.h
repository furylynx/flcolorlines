#ifndef MYRENDERTHREAD_H
#define MYRENDERTHREAD_H

#include <QThread>

#include "Controller.GameController.h"

class MyGLFrame;
class QSize;

class MyRenderThread : public QThread
{
    Q_OBJECT
public:
    explicit MyRenderThread(MyGLFrame *parent = 0);
    void resizeViewport(const QSize &size);
    void run(void);
    void stop(void);

    void setGameController(controller::GameController *gc);

    void gl_select(int x, int y);


protected:
    void GLInit(void);
    void GLResize(int width, int height);
    void paintGL(void);

private:
    bool doRendering, doResize;
    int w, h, FrameCounter;

    controller::GameController *gamecontroller;

    MyGLFrame *GLFrame;


signals:
public slots:
};

#endif // MYRENDERTHREAD_H
