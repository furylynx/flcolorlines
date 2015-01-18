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
    /**
     * Init an OpenGl render thread for the _glwidget QGL
     *
     * @param _glw The gl widget to be handled.
     */
    RenderThread(ui::GLWidget & _glw);


    /**
     * The run method of the thread. Contains the thread loop.
     */
    virtual void run();

    /**
     * Signals the thread to exit the next time it is woken up.
     */
    virtual void stop();

    /**
     * Requests a resize of the GL viewport. This is usually called from the QGLWidgets resizeEvent() method.
     */
    virtual void resizeViewport(const QSize& _size);

    /**
     * Sets the rotation values for the display.
     *
     * @param _x The rotation on the x-axis.
     * @param _y The rotation on the y-axis.
     * @param _z The rotation on the z-axis.
     */
    virtual void setRotation( GLfloat x, GLfloat y, GLfloat z);


    /**
     * Returns the color of a cube face. This function can be called from different threads!
     *
     * @param pos The position where to check the face.
     * @return The color of a cube face.
     */
    virtual int faceAtPosition(const QPoint &pos);

    /**
     * Sets the selected field which will be processed the next time the thread wakes up.
     *
     * @param pos The position to be selected.
     */
    virtual void selectField(const QPoint &pos);

    /**
     * Sets the hovered field which will be processed the next time the thread wakes up.
     *
     * @param pos The position to be hovered.
     */
    virtual void hoverField(const QPoint &pos);

    /**
     * Sets the selected field by the field id.
     *
     * @param face The field id of the field to be selected.
     */
    virtual void setSelectedField(int face);

    /**
     * Sets the hovered field by the field id.
     *
     * @param face The field id of the field to be hovered.
     */
    virtual void setHoveredField(int face);

    /**
     * Begins the initial animation.
     */
    virtual void beginInitialAnimation();

    /**
     * Calculates the animation translation.
     *
     * @param field
     * @param i
     * @param j
     * @param dist
     * @param out_x
     * @param out_y
     * @param out_z
     * @param our_color
     * @param out_size
     */
    virtual void calcAnimationTranslation(model::GameField *field, int i, int j, float dist, float *out_x, float *out_y, float *out_z, float *our_color, float *out_size);

    /**
     * Calculates the new ball function value.
     *
     * @param d
     * @param t_millisec The timestamp.
     * @return The value
     */
    virtual float quadraticNewBallFunction(float d, long t_millisec);

    /**
     * Returns the value for the quadratic color function.
     *
     * @param t_millisec The timestamp.
     * @return The value.
     */
    virtual float quadraticColorFunction(long t_millisec);

    /**
     * Returns the ball position for a movement.
     *
     * @param t_millisec The timestamp.
     * @param path The movement path.
     * @param out_x The x-position.
     * @param out_y The y-position.
     */
    virtual void movementPositionFunction(long t_millisec, std::vector<model::FieldPosition> path, float *out_x, float *out_y);


protected:

    /**
     * Initializes the GL environment.
     */
    virtual void initializeGL();

    /**
     * Handles resizes of the GL viewport.
     */
    virtual void resizeGL(int width, int height);

    /**
     * Does all the painting.
     */
    virtual void paintGL();

private:
    /**
     *  Actually draws the example scene (cube).
     */
    void draw();

    /**
     *  Draws the idle sequence on the main site.
     */
    void drawIdleSequence();

    /**
     *  Draws the normal field.
     */
    void drawNormalField();

    /**
     *  Draws the normal field, but also uses animations.
     */
    void drawNormalFieldWithAnimation();

    /**
     *  Draws the initial animation when a new game is started.
     */
    void drawInitialAnimation();

    /**
     *  Converts the Qt Color to an array which can be handled by gl. The array must be of size 4.
     *
     * @param c The color to be converted
     * @param result The pointer to the float array of size 4.
     */
    void qColorToQuadcolor(QColor c, float* result) const;

    //***************
    // private vars
    //***************

    /**
     * The QGLWidget of the render thread. This widget provides the GL rendering context.
     */
    ui::GLWidget& glw;

    /**
     * Keep the thread running as long this flag is true.
     */
    volatile bool render_flag;

    /**
     * Perform a resize when this flag is true.
     */
    volatile bool resize_flag;

    /**
     * Current size of the viewport.
     */
    QSize viewport_size;

    /**
     * Mutex for the queue handling the selected fields.
     */
    QMutex selectedFieldsMutex;

    /**
     * The queue handling the selected fields. Temporary values to be handled in the thread loop.
     */
    std::queue<QPoint> selectedFieldsQueue;

    /**
     * The lastly hovered point. Temporary value to be handled in the thread loop.
     */
    QPoint hoveredPoint;


    /**
     * The rotation value on the x-axis.
     */
    GLfloat rotationX;

    /**
     * The rotation value on the y-axis.
     */
    GLfloat rotationY;

    /**
     * The rotation value on the z-axis.
     */
    GLfloat rotationZ;

    /**
     * The id of the currently selected field.
     */
    int selectedField;

    /**
     * The id of the currently hovered field.
     */
    int hoveredField;

    /**
     * The framecount.
     */
    int framecount;
    /**
     * The framerate evaluated from the framecount.
     */
    float framerate;

    /**
     * A pointer to the time operator.
     */
    model::TimeOperator *timeOperator;

    /**
     * Timestamp for the animation.
     */
    timespec timestampAnimation;

    /**
     * Animation containers for generated balls.
     */
    std::vector<model::AnimationContainer> acontainerGeneratedBalls;

    /**
     * Animation containers for removed balls.
     */
    std::vector<model::AnimationContainer> acontainerRemovedBalls;

    /**
     * Animation containers for moved balls.
     */
    std::vector<model::AnimationContainer> acontainerMovedBalls;

    /**
     * Flag for initial animation to be displayed or not.
     */
    bool initialAnimation;


};

}//namespace controller

#endif // EXAMPLERENDERTHREAD_H

