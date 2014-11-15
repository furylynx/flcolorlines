#ifndef RENDERINGTHREAD_H
#define RENDERINGTHREAD_H

#include <QThread>

class CLGLFrame;
class QSize;

class RenderingThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderingThread(CLGLFrame *parent = 0);
    void resizeViewport(const QSize &size);
    void run(void);
    void stop(void);

protected:
    void GLInit(void);
    void GLResize(int width, int height);
    void paintGL(void);

private:
    bool doRendering, doResize;
    int w, h, FrameCounter;

    CLGLFrame *GLFrame;

signals:
public slots:
};

#endif // RENDERINGTHREAD_H
