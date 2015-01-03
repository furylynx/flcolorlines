/*
 *   Example implementation of a QGLWidget with a separat rendering thread
 *   and GL picking capabilites.
 *
 *   This is the GL rendering thread implementation.
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

#include "Controller.RenderThread.hpp"
#include "../ui/UI.GLWidget.hpp"

using namespace controller;

RenderThread::RenderThread( ui::GLWidget & _glw )
        : QThread(),
        glw(_glw),
        render_flag(true),
        resize_flag(false),
        viewport_size(_glw.size())
{
    //initialize rotations
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;

    //init field stuff
    selectedField = -1;
    hoveredField = -1;

    //init rendering stuff
    framecount = 0;
    framerate = 0;
    timeOperator = new model::TimeOperator();

    initialAnimation = false;
}

void RenderThread::resizeViewport( const QSize& _size )
{
    // set size and flag to request resizing
    viewport_size = _size;
    resize_flag = true;

}

void RenderThread::stop( )
{
    // set flag to request thread to exit
    // REMEMBER: The thread needs to be woken up once
    // after calling this method to actually exit!
    render_flag = false;
}

void RenderThread::run( )
{

    //TODO makeCurrent causes a crash with qt5
    while (!glw.isVisible())
    { }


    // lock the render mutex of the Gl widget
    // and makes the rendering context of the glwidget current in this thread
    glw.lockGLContext();

    // general GL init
    initializeGL();

    // do as long as the flag is true
    while( render_flag )
    {

        // resize the GL viewport if requested
        if (resize_flag)
        {
            resizeGL(viewport_size.width(), viewport_size.height());
            resize_flag = false;
        }


        //handle mouse clicks
        selectedFieldsMutex.lock();
        while(selectedFieldsQueue.size() > 0)
        {
            selectedFieldsQueue.back();
            setSelectedField(faceAtPosition(selectedFieldsQueue.back()));
            selectedFieldsQueue.pop();
        }
        selectedFieldsMutex.unlock();


        //handle mouse moves
        hoveredFieldsMutex.lock();
        while(hoveredFieldsQueue.size() > 0)
        {
            setHoveredField(faceAtPosition(hoveredFieldsQueue.back()));
            hoveredFieldsQueue.pop();
        }
        hoveredFieldsMutex.unlock();

        // render code goes here
        paintGL();

        // swap the buffers of the GL widget
        glw.swapBuffers();

        // release the GL render context to make picking work!
        glw.doneCurrent();


        // wait until the gl widget says that there is something to render
        // glwidget.lockGlContext() had to be called before (see top of the function)!
        // this will release the render mutex until the wait condition is met
        // and will lock the render mutex again before exiting
        // waiting this way instead of insane looping will not waste any CPU ressources
        glw.renderCondition().wait(&glw.renderMutex(),10);


        glw.makeCurrent(); // get the GL render context back


        // DEACTIVATED -- alternatively render a frame after a certain amount of time
        // prevent to much continous rendering activity
//        msleep(16); //sleep for 16 ms


    }
    // unlock the render mutex before exit
    glw.unlockGLContext();

    std::cout << "thread ended..." << std::endl;
}

void RenderThread::initializeGL()
{
    // typical OpenGL init
    // see OpenGL documentation for an explanation
    glw.qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    //light7
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Create light components
    GLfloat ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat position[] = { -0.0f, -0.0f, -0.0f, 1.0f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

}

void RenderThread::resizeGL(int width, int height)
{
    // nothing special
    // see OpenGL documentation for an explanation
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)width / height;
    glFrustum(-x, x, -1.0, 1.0, 2.5, 25.0);
    glMatrixMode(GL_MODELVIEW);


}

void RenderThread::paintGL()
{
    // clear all and draw the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void RenderThread::draw()
{
    // draws the content


    //calc frames
    timespec timestampNow;
    clock_gettime(1, &timestampNow);

    long millisdiff = timeOperator->getTimeSinceMark();//((timestampNow.tv_sec - timestamp.tv_sec) * 1000) + ((timestampNow.tv_nsec - timestamp.tv_nsec) / 1000000);

    if (millisdiff == 0)
        millisdiff = 1;

    framerate = framecount / ((float) millisdiff / 1000);

    if (millisdiff >= 1000){
        timeOperator->setMark();
        framecount = 0;
    }

    framecount ++;


    //initial setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5);



    //get the gamecontroller
    controller::GameController* controller = glw.getGameController();

    if(controller == 0){
        drawIdleSequence();
        return;
    }else
        if (!controller->areOptionsSet()){
            drawIdleSequence();
            return;
        }

    if (initialAnimation)
        drawInitialAnimation();
    else
        drawNormalFieldWithAnimation();
}

void RenderThread::drawNormalField()
{

    controller::GameController* controller = glw.getGameController();
    model::GameField* field = controller->getGameField();

    if (field == 0){
        drawIdleSequence();
        return;
    }



    //get path between selected and hovered field
    std::vector<model::FieldPosition> path;
    if (hoveredField != selectedField && selectedField != -1 && hoveredField != -1){

        model::FieldPosition pos1;
        pos1.posX = selectedField%field->getDimensionX();
        pos1.posY = selectedField / field->getDimensionX();

        model::FieldPosition pos2;
        pos2.posX = hoveredField % field->getDimensionX();
        pos2.posY = hoveredField / field->getDimensionX();

        path = field->getPath(pos1,pos2);

    }


    //translate into center
    int translationX = field->getDimensionX()/2;
    int translationY = field->getDimensionY()/2;

    GLfloat dist = -9;

    if (field->getDimensionX() >= field->getDimensionY())
        dist = field->getDimensionX()*(-1);
    else
        dist=field->getDimensionY()*(-1);

    //GLfloat dist = -9;

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glTranslatef(((rotationZ*dist*(-1))/90)*(-rotationX/70),(rotationX*dist)/90, (rotationX*dist)/90);

    //draw each field of the game
    for (int i = 0; i< field->getDimensionX(); i++){
        for (int j = 0; j< field->getDimensionY();j++){

            //encolor the field
            QColor c;
            if ((i % 2 == 0 && j % 2 == 0) || (i %2 == 1 && j % 2 == 1) ){
                c.setRedF(0.5f);
                c.setGreenF(0.5f);
                c.setBlueF(0.5f);
            }
            else
            {
                c.setRedF(0.3f);
                c.setGreenF(0.3f);
                c.setBlueF(0.3f);
            }

            int name = j*field->getDimensionX()+i;


            // highlight selected and hovered field
            if(name == selectedField)
                c = Qt::white;
            else
                if ((name == hoveredField && path.size() > 1) || (selectedField == -1 && hoveredField == name))
                    c=Qt::lightGray;
                else
                    if (name == hoveredField && path.size() <= 1)
                        c=Qt::magenta;
                    else
//                        if (!field->getBallAt(i,j).isNull && !field->getBallAt(i,j).outOfField){
//                            model::Ball b = field->getBallAt(i,j);
//                            c.setRed(b.color.getColorR());
//                            c.setGreen(b.color.getColorG());
//                            c.setBlue(b.color.getColorB());
//                            c.setAlpha(b.color.getColorA());
//                        }
//                        else
                            if (path.size() > 1)
                                for (unsigned int k = 0; k < path.size() ; k++)
                                    if (path[k].posX == i && path[k].posY == j){
                                        c = Qt::lightGray;
                                    }


            //name the field
            glLoadName(name);

            //begin actual drawing of the element
            glBegin(GL_QUADS);

            float quadcolor[4];
            qColorToQuadcolor(c, quadcolor);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
            glMateriali(GL_FRONT, GL_SHININESS, 96);

            //glw.qglColor(c);
            glVertex3f(0+i-translationX , 0+j-translationY,dist);
            glVertex3f(1+i-translationX, 0+j-translationY,dist);
            glVertex3f(1+i - translationX, 1+j-translationY,dist);
            glVertex3f(0+i-translationX, 1+j-translationY,dist);
            glEnd();//end drawing

            if (!field->getBallAt(i,j).isNull && !field->getBallAt(i,j).outOfField){

                model::Ball b = field->getBallAt(i,j);
                c.setRed(b.color.getColorR());
                c.setGreen(b.color.getColorG());
                c.setBlue(b.color.getColorB());
                c.setAlpha(b.color.getColorA());

                glTranslatef(0.5+i-translationX,0.5+j-translationY,dist+0.5);
                glRotatef(100,1.0,0,0);
                glBegin(GL_QUADS);
                //convert colors
                qColorToQuadcolor(c, quadcolor);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
                glMateriali(GL_FRONT, GL_SHININESS, 96);
                glutSolidSphere(0.5, 50, 50);
                glEnd();
                glRotatef(-100,1.0,0,0);
                glTranslatef(-0.5-i+translationX,-0.5-j+translationY,(-1)*(dist+0.5));

            }
        }
    }

    //draw the score
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(field->getDimensionX()-translationX+1, field->getDimensionY()-translationY-0.5,dist);

    std::ostringstream ostream;
    ostream << "Score: " << controller->getTheScore();
    std::string score(ostream.str());

    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(score.c_str()));

    if (controller->isGameOver())
    {
        glRasterPos3f(0, 0,-5);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>("Game Over!"));
    }

    //frames
    glColor3f(0.3f, 0.3f, 0.3f);
    glRasterPos3f(field->getDimensionX()-translationX+1, 0-translationY,dist);

    std::ostringstream ostream2;
    ostream2 << "Frames/s: " << framerate;
    std::string frames(ostream2.str());

    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(frames.c_str()));

    glEnable(GL_LIGHTING);
}

void RenderThread::drawNormalFieldWithAnimation(){

    controller::GameController* controller = glw.getGameController();
    model::GameField* field = controller->getGameField();

    if (field == 0){
        drawIdleSequence();
        return;
    }

    //now

    //get path between selected and hovered field
    std::vector<model::FieldPosition> path;
    if (hoveredField != selectedField && selectedField != -1 && hoveredField != -1){

        model::FieldPosition pos1;
        pos1.posX = selectedField%field->getDimensionX();
        pos1.posY = selectedField / field->getDimensionX();

        model::FieldPosition pos2;
        pos2.posX = hoveredField % field->getDimensionX();
        pos2.posY = hoveredField / field->getDimensionX();

        path = field->getPath(pos1,pos2);

    }


    //translate into center
    int translationX = field->getDimensionX()/2;
    int translationY = field->getDimensionY()/2;

    GLfloat dist = -9;

    if (field->getDimensionX() >= field->getDimensionY())
        dist = field->getDimensionX()*(-1);
    else
        dist=field->getDimensionY()*(-1);

    //GLfloat dist = -9;

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glTranslatef(((rotationZ*dist*(-1))/90)*(-rotationX/70),(rotationX*dist)/90, (rotationX*dist)/90);

    //draw each field of the game
    for (int i = 0; i< field->getDimensionX(); i++){
        for (int j = 0; j< field->getDimensionY();j++){

            GLfloat anima_x = 0;
            GLfloat anima_y = 0;
            GLfloat anima_z = 0;
            GLfloat anima_size = 1;
            GLfloat anima_color = 0;

            calcAnimationTranslation(field,i,j,dist, &anima_x,&anima_y, &anima_z, &anima_color, &anima_size);


            //encolor the field
            QColor c;
            if ((i % 2 == 0 && j % 2 == 0) || (i %2 == 1 && j % 2 == 1) )
                anima_color += 0.5;
            else
                anima_color += 0.3;

            c.setRedF(anima_color);
            c.setGreenF(anima_color);
            c.setBlueF(anima_color);

            int name = j*field->getDimensionX()+i;


            // highlight selected and hovered field
            if(name == selectedField)
                c = Qt::white;
            else
                if ((name == hoveredField && path.size() > 1) || (selectedField == -1 && hoveredField == name))
                    c=Qt::lightGray;
                else
                    if (name == hoveredField && path.size() <= 1)
                        c=Qt::magenta;
                    else
//                        if (!field->getBallAt(i,j).isNull && !field->getBallAt(i,j).outOfField){
//                            model::Ball b = field->getBallAt(i,j);
//                            c.setRed(b.color.getColorR());
//                            c.setGreen(b.color.getColorG());
//                            c.setBlue(b.color.getColorB());
//                            c.setAlpha(b.color.getColorA());
//                        }
//                        else
                            if (path.size() > 1)
                                for (unsigned int k = 0; k < path.size() ; k++)
                                    if (path[k].posX == i && path[k].posY == j){
                                        c = Qt::lightGray;
                                    }


            //name the field
            glLoadName(name);

            //begin actual drawing of the element
            glBegin(GL_QUADS);

            float quadcolor[4];
            qColorToQuadcolor(c, quadcolor);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
            glMateriali(GL_FRONT, GL_SHININESS, 96);

            //glw.qglColor(c);
            glVertex3f(0+i-translationX , 0+j-translationY,dist);
            glVertex3f(1+i-translationX, 0+j-translationY,dist);
            glVertex3f(1+i - translationX, 1+j-translationY,dist);
            glVertex3f(0+i-translationX, 1+j-translationY,dist);
            glEnd();//end drawing



            if ((!field->getBallAt(i,j).isNull && !field->getBallAt(i,j).outOfField) || (anima_size != 1 && field->getBallAt(i,j).isNull && !field->getBallAt(i,j).outOfField)){

//                GLfloat anima_z = 0;

//                std::vector<int> toRemove;
//                //check for animation pos
//                for(int k = 0; k< acontainerGeneratedBalls.size(); k++)
//                    for (int l = 0; l< acontainerGeneratedBalls[k].objects.size(); l++)
//                        if (acontainerGeneratedBalls[k].objects[l].posX == i && acontainerGeneratedBalls[k].objects[l].posY == j){
//                            long ms = timeOperator->getTimeDifference(acontainerGeneratedBalls[k].timestamp, now);

//                            if (ms < 2000)
//                                anima_z = quadraticNewBallFunction(dist,ms);//(float)(2000-ms)/2000*(-dist);
//                            else{
//                                toRemove.push_back(k);
//                                break;
//                            }
//                        }

//                for (int k = 0; k < toRemove.size();k++)
//                    acontainerGeneratedBalls.erase(acontainerGeneratedBalls.begin()+toRemove[k]);


                if (anima_size != 1){
                    float ball_color = 0.4;
                    c.setRedF(ball_color);
                    c.setGreenF(ball_color);
                    c.setBlueF(ball_color);
                    c.setAlphaF(1.0f);
                }else{
                    model::Ball b = field->getBallAt(i,j);
                    c.setRed(b.color.getColorR());
                    c.setGreen(b.color.getColorG());
                    c.setBlue(b.color.getColorB());
                    c.setAlpha(b.color.getColorA());
                }

                glTranslatef(anima_x, anima_y,anima_z);
                glTranslatef(0.5+i-translationX,0.5+j-translationY,dist+0.5);
                glRotatef(180,1.0,0,0);
                glBegin(GL_QUADS);

                //convert color
                qColorToQuadcolor(c, quadcolor);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
                glMateriali(GL_FRONT, GL_SHININESS, 96);
                glutSolidSphere(0.5*anima_size, 50, 50);

                glEnd();
                glRotatef(-180,1.0,0,0);
                glTranslatef(-0.5-i+translationX,-0.5-j+translationY,(-1)*(dist+0.5));
                glTranslatef(-anima_x,-anima_y,-anima_z);


            }
        }
    }

    //draw the score
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(field->getDimensionX()-translationX+1, field->getDimensionY()-translationY-0.5,dist);

    std::ostringstream ostream;
    ostream << "Score: " << controller->getTheScore();
    std::string score(ostream.str());

    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(score.c_str()));

    if (controller->isGameOver()){
        glRasterPos3f(0, 0,-5);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>("Game Over!"));
    }

    //frames
    glColor3f(0.3f, 0.3f, 0.3f);
    glRasterPos3f(field->getDimensionX()-translationX+1, 0-translationY,dist);

    std::ostringstream ostream2;
    ostream2 << "Frames/s: " << framerate;
    std::string frames(ostream2.str());

    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(frames.c_str()));

    glEnable(GL_LIGHTING);
}

void RenderThread::drawIdleSequence(){

    //begin actual drawing of the element

    long ms = timeOperator->getTimeSinceBegin();

    float quadcolor[4];
    qColorToQuadcolor(Qt::darkRed, quadcolor);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
    glMateriali(GL_FRONT, GL_SHININESS, 96);

    glTranslatef(1,1,-6);
    glRotatef(360*(float)ms/3000, 0.0, 0.0, 1.0);


    glLoadName(0);

    glBegin(GL_QUADS);
    glVertex3f(-0.5,-0.5,0);
    glVertex3f(0.5,-0.5,0);
    glVertex3f(0.5,0.5,0);
    glVertex3f(-0.5,0.5,0);

    glEnd();

    glRotatef((-1)*360*(float)ms/3000, 0.0, 0.0, 1.0);
    glTranslatef(-1,-1,6);



//    glRotatef(-25, 1.0, 1.0, 0.0);

    qColorToQuadcolor(Qt::darkBlue, quadcolor);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
    glMateriali(GL_FRONT, GL_SHININESS, 96);

    glTranslatef(3,2,-6);
    glRotatef(360*(float)ms/3000, 0.0, 0.0, 1.0);

    glLoadName(1);

    glBegin(GL_QUADS);
    glVertex3f(-0.5,-0.5,0);
    glVertex3f(0.5,-0.5,0);
    glVertex3f(0.5,0.5,0);
    glVertex3f(-0.5,0.5,0);

    glEnd();

    glRotatef((-1)*360*(float)ms/3000, 0.0, 0.0, 1.0);
    glTranslatef(-3,-2,6);

    qColorToQuadcolor(Qt::darkYellow, quadcolor);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
    glMateriali(GL_FRONT, GL_SHININESS, 96);


    glTranslatef(3.5,-1,-6);
    glRotatef(360*(float)ms/3000, 0.0, 0.0, 1.0);

    glLoadName(2);

    glBegin(GL_QUADS);

    glVertex3f(-0.5,-0.5,0);
    glVertex3f(0.5,-0.5,0);
    glVertex3f(0.5,0.5,0);
    glVertex3f(-0.5,0.5,0);

    glEnd();

    glRotatef((-1)*360*(float)ms/3000, 0.0, 0.0, 1.0);
    glTranslatef(-3.5,-2,6);




}

void RenderThread::drawInitialAnimation(){

    controller::GameController* controller = glw.getGameController();
    model::GameField* field = controller->getGameField();

    timespec now;
    clock_gettime(1, &now);
    long ms = timeOperator->getTimeDifference(timestampAnimation, now);

    if (ms > 3000){
        initialAnimation = false;

        model::AnimationContainer container;
        container.objects = controller->getLastGeneratedBalls();
        container.timestamp = now;

        acontainerGeneratedBalls.push_back(container);
    }

    //translate into center
    int translationX = field->getDimensionX()/2;
    int translationY = field->getDimensionY()/2;

    float dist = -9;

    if (field->getDimensionX() >= field->getDimensionY())
        dist = field->getDimensionX()*(-1);
    else
        dist=field->getDimensionY()*(-1);

    int count = 0;
    //draw each field of the game
    for (int i = 0; i< field->getDimensionX(); i++){
        for (int j = 0; j< field->getDimensionY();j++){

            //encolor the field
            QColor c;
            if ((i % 2 == 0 && j % 2 == 0) || (i %2 == 1 && j % 2 == 1) ){
                c.setRedF(0.5f);
                c.setGreenF(0.5f);
                c.setBlueF(0.5f);
            }
            else
            {
                c.setRedF(0.3f);
                c.setGreenF(0.3f);
                c.setBlueF(0.3f);
            }

            int name = j*field->getDimensionX()+i;

            if (i+j < (float)ms/1000 * (float)(field->getDimensionX()+field->getDimensionY())/2){

                count ++;
                //name the field
                glLoadName(name);

                //begin actual drawing of the element

                float quadcolor[4];
                qColorToQuadcolor(c, quadcolor);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
                glMateriali(GL_FRONT, GL_SHININESS, 96);

                glTranslatef(i+0.5-translationX,j+0.5-translationY, dist);

                float angle = (ms-(float)((i+j)*2000)/(field->getDimensionX()+field->getDimensionY()))*90/1000;

                if(angle > 90)
                    angle = 90;

                glRotatef(90-angle,1.0,-1.0,0);

                glBegin(GL_QUADS);
                glVertex3f(-0.5 , -0.5,0);
                glVertex3f(0.5, -0.5,0);
                glVertex3f(0.5, 0.5,0);
                glVertex3f(-0.5, 0.5,0);
                glEnd();//end drawing

                glRotatef(angle-90,1.0,-1.0,0);
                glTranslatef(-i-0.5+translationX,-j-0.5+translationY, -dist);


            }

        }
    }


//    glDisable(GL_LIGHTING);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    glRasterPos3f(-3, 3, -5);

//    std::ostringstream ostream;
//    ostream << "t: " << ms << " count:" << count;
//    std::string pr(ostream.str());

//    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(pr.c_str()));

//    glEnable(GL_LIGHTING);

}

void RenderThread::calcAnimationTranslation(model::GameField *field, int i, int j, float dist, float *out_x, float *out_y, float *out_z, float *out_color, float *out_size){
    timespec now;
    clock_gettime(1, &now);

    *out_x = 0;
    *out_y = 0;
    *out_z = 0;
    *out_color = 0;
    *out_size = 1;


    std::vector<int> toRemoveG;
    std::vector<int> toRemoveR;
    std::vector<int> toRemoveM;

    //check for new balls
    for(unsigned int k = 0; k< acontainerGeneratedBalls.size(); k++)
        for (unsigned int l = 0; l< acontainerGeneratedBalls[k].objects.size(); l++)
            if (!field->getBallAt(i,j).isNull && !field->getBallAt(i,j).outOfField){
                if (acontainerGeneratedBalls[k].objects[l].posX == i && acontainerGeneratedBalls[k].objects[l].posY == j){
                    long ms = timeOperator->getTimeDifference(acontainerGeneratedBalls[k].timestamp, now);

                    if (ms < 2000){
                        *out_z = quadraticNewBallFunction(dist,ms);
                        *out_color = quadraticColorFunction(ms);
                    }else{
                        toRemoveG.push_back(k);
                        break;
                    }
                }
            }


    //check deleted balls
    for(unsigned int k = 0; k< acontainerRemovedBalls.size(); k++)
        for (unsigned int l = 0; l< acontainerRemovedBalls[k].objects.size(); l++)
            if (field->getBallAt(i,j).isNull && !field->getBallAt(i,j).outOfField){
                if (acontainerRemovedBalls[k].objects[l].posX == i && acontainerRemovedBalls[k].objects[l].posY == j){
                    long ms = timeOperator->getTimeDifference(acontainerRemovedBalls[k].timestamp, now);

                    if (ms < 1000){
                        *out_size = 1- (float)ms/1000;
                    }else{
                        toRemoveR.push_back(k);
                        break;
                    }
                }
            }

    //check moved balls
    for(unsigned int k = 0; k< acontainerMovedBalls.size(); k++)
            if (/*!field->getBallAt(i,j).isNull &&*/ !field->getBallAt(i,j).outOfField){
                if (acontainerMovedBalls[k].objects.back().posX == i && acontainerMovedBalls[k].objects.back().posY == j){
                    long ms = timeOperator->getTimeDifference(acontainerMovedBalls[k].timestamp, now);

//                  Calculate the current position during movement
                    if (ms < ((long)acontainerMovedBalls[k].objects.size()-1)*50){
//                        *out_x = -4 + (float)ms*4/2000;//todo check
                           movementPositionFunction(ms, acontainerMovedBalls[k].objects, out_x, out_y);
                    }else{
                        toRemoveM.push_back(k);
                        break;
                    }
                }
            }

    for (unsigned int k = 0; k < toRemoveG.size();k++)
            acontainerGeneratedBalls.erase(acontainerGeneratedBalls.begin()+toRemoveG[k]);

    for (unsigned int k = 0; k < toRemoveR.size();k++)
            acontainerRemovedBalls.erase(acontainerRemovedBalls.begin()+toRemoveR[k]);

    for (unsigned int k = 0; k < toRemoveM.size();k++)
            acontainerMovedBalls.erase(acontainerMovedBalls.begin()+toRemoveM[k]);

}

float RenderThread::quadraticNewBallFunction(float d, long t_millisec){

    float t = (float)t_millisec/1000;
    d= -d;
    float a = pow((2+sqrt(2)),2)*d/4;

    if (t >= 0 && t <= (2 - sqrt(2)) ){
        float ret = -a*(pow(t,2))+d;
        return ret;

    }else
        if(t > (2 - sqrt(2)) && t < sqrt(2)){
            float ret = -a*(pow((t-1),2))+d/2;
            return ret;
        }else
            if( t > sqrt(2) && t <= 2){
                float ret =-a*(pow((t-1-1/sqrt(2)),2))+d/4;
                return ret;
            }

    return 0;
}

float RenderThread::quadraticColorFunction(long t_millisec){
    if (t_millisec <= 0 || t_millisec >= 1000)
        return 0;
    else{
        float t = (float)t_millisec/1000;

        float ret = -2*(pow(t-0.5,2))+0.5;

        if (ret > 0.5 || ret < 0)
            ret = 0;

        return ret;
    }
}

void RenderThread::movementPositionFunction(long t_millisec, std::vector<model::FieldPosition> path, float *out_x, float *out_y){

    unsigned int current = (int) (float)t_millisec/50;//get current processed path piece

    float t = (float)t_millisec/50 - (float)current;

    if(path.size() <= current+1)
        return;

    float x = (1-t)*((float) path[current].posX) + t*((float) path[current+1].posX);
    float y = (1-t)*((float) path[current].posY) + t*((float) path[current+1].posY);

    *out_x = x-(float)path.back().posX;
    *out_y = y-(float)path.back().posY;
}

void RenderThread::selectField(const QPoint &pos)
{
    selectedFieldsMutex.lock();
    selectedFieldsQueue.push(pos);
    selectedFieldsMutex.unlock();
}

void RenderThread::hoverField(const QPoint &pos)
{
    hoveredFieldsMutex.lock();
    hoveredFieldsQueue.push(pos);
    hoveredFieldsMutex.unlock();
}


int RenderThread::faceAtPosition(const QPoint &pos)
{

    // we need to lock the rendering context
        //TODO commented for internal use
    //glw.lockGLContext();

    // this is the same as in every OpenGL picking example
    const int MaxSize = 512; // see below for an explanation on the buffer content
    GLuint buffer[MaxSize];
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    // enter select mode
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix((GLdouble)pos.x(),
                  (GLdouble)(viewport[3] - pos.y()),
                  5.0, 5.0, viewport);
    GLfloat x = (GLfloat)viewport_size.width() / viewport_size.height();
    glFrustum(-x, x, -1.0, 1.0, 2.5, 25.0);
    draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();


    // finally release the rendering context again
    //TODO commented for internal use
    if (!glRenderMode(GL_RENDER))
    {
        //glw.unlockGLContext();
        return -1;
    }
//    glw.unlockGLContext();

    // Each hit takes 4 items in the buffer.
    // The first item is the number of names on the name stack when the hit occured.
    // The second item is the minimum z value of all the verticies that intersected
    // the viewing area at the time of the hit. The third item is the maximum z value
    // of all the vertices that intersected the viewing area at the time of the hit
    // and the last item is the content of the name stack at the time of the hit
    // (name of the object). We are only interested in the object name
    // (number of the surface).


    // return the id of the clicked surface
    return buffer[3];
}

void RenderThread::setRotation( GLfloat _x, GLfloat _y, GLfloat _z )
{
    if (initialAnimation)
        return;

    if (rotationX +_x >= -70 && rotationX +_x <= 0) //only x and z are used currently
        rotationX += _x;

    if (rotationY +_y >= -70 && rotationY +_y <= 0)
        rotationY += _y;

    if (rotationZ +_z > -45 && rotationZ +_z < 45)
        rotationZ += _z;
}

void RenderThread::setSelectedField(int face)
{

    controller::GameController* controller = glw.getGameController();

    if (controller == 0)
        return ;
    else
        if (controller->getGameField() == 0 || !controller->areOptionsSet())
            return ;

    model::GameField* field = controller->getGameField();

    if(selectedField == face)
    {
        selectedField = -1;
    }
    else
    {
        if (selectedField != -1)
        {
            //move ball
            model::FieldPosition pos1;
            pos1.posX = selectedField % field->getDimensionX();
            pos1.posY = selectedField / field->getDimensionX();
            model::FieldPosition pos2;
            pos2.posX = face % field->getDimensionX();
            pos2.posY = face / field->getDimensionX();

            std::vector<model::FieldPosition> path = controller->moveBall(pos1,pos2);

            if (controller->isGameOver())
                glw.gameOver();

            if (path.size() > 1){
                selectedField = -1;

                model::AnimationContainer container3;
                container3.objects = path;
                clock_gettime(1, &container3.timestamp);
                acontainerMovedBalls.push_back(container3);

                model::AnimationContainer container;
                container.objects = controller->getLastGeneratedBalls();
                clock_gettime(1, &container.timestamp);
                acontainerGeneratedBalls.push_back(container);

                model::AnimationContainer container2;
                container2.objects = controller->getLastRemovedBalls();
                clock_gettime(1, &container2.timestamp);
                acontainerRemovedBalls.push_back(container2);


            }else
                if (!field->getBallAt(pos2).isNull && !field->getBallAt(pos2).outOfField )
                    selectedField = face;

        }
        else
            if (!field->getBallAt(face%field->getDimensionX(), face / field->getDimensionX()).isNull && !field->getBallAt(face%field->getDimensionX(), face / field->getDimensionX()).outOfField )
                selectedField = face;
    }

}

void RenderThread::setHoveredField(int face)
{

    if (face == selectedField)
    {
        hoveredField = -1;
    }

    hoveredField = face;
}

void RenderThread::qColorToQuadcolor(QColor c, float* result) const
{
    result[0] = c.redF();
    result[1] = c.greenF();
    result[2] = c.blueF();
    result[3] = c.alphaF();
}

void RenderThread::beginInitialAnimation(){

    clock_gettime(1, &timestampAnimation);

    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;

    initialAnimation = true;
}
