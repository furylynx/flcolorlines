#ifndef MYGLFRAME_H
#define MYGLFRAME_H

#include <QGLWidget>
#include "myrenderthread.h"

class MyGLFrame : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLFrame(QWidget *parent = 0);
    ~MyGLFrame();
    void initRenderThread(void);
    void stopRenderThread(void);

signals:

public slots:

protected:
    void closeEvent(QCloseEvent *evt);
    void resizeEvent(QResizeEvent *evt);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);

    MyRenderThread RenderThread;

private:
};

#endif // MYGLFRAME_H
