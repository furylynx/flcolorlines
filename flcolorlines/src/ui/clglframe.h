#ifndef CLGLFRAME_H
#define CLGLFRAME_H

#include <QGLWidget>
#include "renderingthread.h"

class CLGLFrame : public QGLWidget
{
    Q_OBJECT
public:
    explicit CLGLFrame(QWidget *parent = 0);
    ~CLGLFrame();
    void initRenderThread(void);
    void stopRenderThread(void);

signals:

public slots:

protected:
    void closeEvent(QCloseEvent *evt);
    void resizeEvent(QResizeEvent *evt);
    void paintEvent(QPaintEvent *);

    RenderingThread renderThread;

private:
};

#endif // CLGLFRAME_H
