/*
 *   Example implementation of a QGLWidget with a separat rendering thread
 *   and GL picking capabilites.
 *
 *   This is the GL rendering thread interface.
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
#ifndef EXAMPLERENDERTHREAD_H
#define EXAMPLERENDERTHREAD_H

//custom includes
#include "../model/Model.TimeOperator.hpp"
#include "../model/Model.AnimationContainer.hpp"
#include "../controller/Controller.GameController.hpp"

//global includes
#include <vector>
#include <ctime>
#include <memory>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>

#include <qgl.h>
#include <QThread>
#include <QSize>
#include <QMutex>

//#include <GL/glut.h>
#include <GL/freeglut.h>

//forward declaration of the widget
namespace ui
{
    class GLWidget;
}

namespace controller
{
/** CPU time saving OpenGL rendering thread.
 * This thread only renders when its corresponding QGLWidget subclass
 * render() method is called (might be called from a different thread).
 * This class also provides a thread-safe example implementation of OpenGL object
 * picking capabilities (in the faceAtPosition() method).
 */
class RenderThread : public QThread
{
public:
    /** Init an OpenGl render thread for the _glwidget QGL */
    RenderThread(ui::GLWidget & _glw);
    /** main() function of the thread. */
    void run();
    /** Signal the thread to exit the next time it is woken up. */
    void stop();
    /** Request a resize of the GL viewport.
     * This is usually called from the QGLWidgets resizeEvent() method.
     */
    void resizeViewport(const QSize& _size);

    // example implementation
    /** Change settings for rendering. */
    void setRotation( GLfloat _x, GLfloat _y, GLfloat _z);
    /** Returns the color of a cube face.
     * This function can be called from different threads!
     */
    int faceAtPosition(const QPoint &pos);

    void selectField(const QPoint &pos);
    void hoverField(const QPoint &pos);

    void setSelectedField(int face);
    void setHoveredField(int face);

    void beginInitialAnimation();


    void calcAnimationTranslation(model::GameField *field, int i, int j, float dist, float *out_x, float *out_y, float *out_z, float *our_color, float *out_size);
    float quadraticNewBallFunction(float d, long t_millisec);
    float quadraticColorFunction(long t_millisec);
    void movementPositionFunction(long t_millisec, std::vector<model::FieldPosition> path, float *out_x, float *out_y);


protected:
    /** Init the GL environment. */
    void initializeGL();
    /** Handles resizes of the GL viewport. */
    void resizeGL(int width, int height);
    /** Does all the painting. */
    void paintGL();

private:
    /** Actually draws the example scene (cube). */
    void draw();

    void drawIdleSequence();
    void drawNormalField();
    void drawNormalFieldWithAnimation();
    void drawInitialAnimation();

    void qColorToQuadcolor(QColor c, float* result) const;

    /** The QGLWidget of the render thread.
     * This widget provides the GL rendering context.
     */
    ui::GLWidget& glw;
    /** Keep the thread running as long this flag is true. */
    volatile bool render_flag;
    /** Perform a resize when this flag is true. */
    volatile bool resize_flag;
    /** Current size of the viewport. */
    QSize viewport_size;

    QMutex selectedFieldsMutex;
    std::queue<QPoint> selectedFieldsQueue;
    QMutex hoveredFieldsMutex;
    std::queue<QPoint> hoveredFieldsQueue;


    // example implmentation members
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;

    int selectedField;
    int hoveredField;

    int framecount;
    float framerate;
    model::TimeOperator *timeOperator;
    timespec timestampAnimation;

    std::vector<model::AnimationContainer> acontainerGeneratedBalls;
    std::vector<model::AnimationContainer> acontainerRemovedBalls;
    std::vector<model::AnimationContainer> acontainerMovedBalls;

    bool initialAnimation;


};

}//namespace controller

#endif // EXAMPLERENDERTHREAD_H

