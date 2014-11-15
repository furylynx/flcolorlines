#include <qgl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "myrenderthread.h"
#include "myglframe.h"
#include "mainwindow.h"


MyRenderThread::MyRenderThread(MyGLFrame *_GLFrame) :
    QThread(),
    GLFrame(_GLFrame)
{
    doRendering = true;
    doResize = false;
    FrameCounter=0;

    //todo remove
    gamecontroller = new controller::GameController();
    gamecontroller->setOptions(9,9,5,3,5);

}

void MyRenderThread::resizeViewport(const QSize &size)
{
    w = size.width();
    h = size.height();
    doResize = true;
}

void MyRenderThread::stop()
{
    doRendering = false;
}


void MyRenderThread::run()
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


void MyRenderThread::GLInit(void)
{
    glClearColor(0.20f,0.20f,0.20f,0);     // Background => dark blue

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Somewhere in the initialization part of your program
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Create light components
    GLfloat ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat position[] = { -2.0f, -2.0f, -1.0f, 1.0f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);


//    int id = glutCreateWindow("test");

//    glClearColor(0.0, 0.0, 0.0, 1.0);
//        glViewport(0, 0, w, h);

//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();

//        gluPerspective(60.0, 1.0, 0.0001, 1000.0);

//        glMatrixMode(GL_MODELVIEW);
}


void MyRenderThread::GLResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(90.,((GLfloat)width)/((GLfloat)height),0.1f,1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


 void MyRenderThread::gl_select(int posx, int posy)
 {
     std::cout << "gl_select \n";

     // we need to lock the rendering context
     //lockGLContext();

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
     gluPickMatrix((GLdouble)posx,
                   (GLdouble)(viewport[3] - posy),
                   5.0, 5.0, viewport);
     GLfloat x = (GLfloat)GLFrame->width() / GLFrame->height();
     glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     paintGL();

     glMatrixMode(GL_PROJECTION);
     glPopMatrix();


     // finally release the rendering context again
//     if (!glRenderMode(GL_RENDER))
//     {
//         std::cout << "rendermode !GL_RENDER \n";
//         //unlockGLContext();
//         return ;
//     }
     //unlockGLContext();

     // Each hit takes 4 items in the buffer.
     // The first item is the number of names on the name stack when the hit occured.
     // The second item is the minimum z value of all the verticies that intersected
     // the viewing area at the time of the hit. The third item is the maximum z value
     // of all the vertices that intersected the viewing area at the time of the hit
     // and the last item is the content of the name stack at the time of the hit
     // (name of the object). We are only interested in the object name
     // (number of the surface).

     // return the name of the clicked surface
     std::cout << sizeof(buffer)<< "face: " << buffer[3] <<"\n";
     return ;
 }


void MyRenderThread::paintGL(void)
{


    //gamecontroller = 0;



//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();

//        glTranslatef(0.0, 0.0, -5.0);

//        glColor3f(1.0, 0.0, 0.0);
//        glLoadName(7); /* Overwrite the first name in the buffer */
//        glPushMatrix();
//                glTranslatef(-0.3, 0, -2);
//                glutSolidCube(1.0);
//        glPopMatrix();

//        glColor3f(0.0, 1.0, 0.0);
//        glLoadName(14); /* Overwrite the first name in the buffer */
//        glPushMatrix();
//                glTranslatef(0, 0, -4);
//                glutSolidCube(1.0);
//            glPopMatrix();

//        glColor3f(0.0, 0.0, 1.0);
//        glLoadName(21); /* Overwrite the first name in the buffer */
//        glPushMatrix();
//                glTranslatef(0.3, 0, -6);
//                glutSolidCube(1.0);
//            glPopMatrix();

//        glutSwapBuffers();






    //return;//just testing




    if (gamecontroller != 0){


    glTranslatef(0.0f, 0.0f, -4.0f);
    glRotatef(-45,0.0f,0.0f,1.0f);
    //glRotatef(FrameCounter,1.0f,0.0f,0.0f);



        int translationX = gamecontroller->getGameField()->getDimensionX()/2;
        int translationY = gamecontroller->getGameField()->getDimensionY()/2;
        int k=0;

        //paint field
        for (int i = 0; i< gamecontroller->getGameField()->getDimensionX(); i++){
            for (int j = 0; j< gamecontroller->getGameField()->getDimensionY();j++){
                float quadcolor[4] ;
                if ((i % 2 == 0 && j % 2 == 0) || (i %2 == 1 && j % 2 == 1) ){
                    quadcolor[0] = 0.5f;
                    quadcolor[1]= 0.5f;
                    quadcolor[2]= 0.5f;
                    quadcolor[3] = 1.5f;
                }
                else
                {
                    quadcolor[0] = 0.3f;
                    quadcolor[1]= 0.3f;
                    quadcolor[2]= 0.3f;
                    quadcolor[3] = 1.5f;
                }
            k++;
           glLoadName(k);

           glBegin(GL_QUADS);
           glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
           glMateriali(GL_FRONT, GL_SHININESS, 96);

           glVertex3f(0+i-translationX , 0+j-translationY,-3.0);
           glVertex3f(1+i-translationX, 0+j-translationY,-3.0);
           glVertex3f(1+i - translationX, 1+j-translationY,-3.0);
           glVertex3f(0+i-translationX, 1+j-translationY,-3.0);
           glEnd();
        }
    }


    //glTranslatef(((float)FrameCounter)/100,0,0);

    //translation of objects
    //glTranslatef(0.0f, 0.0f, -27.0f);            // move 5 units into the screen
    //glRotatef(FrameCounter,1.0f,0.0f,1.0f);     // rotate z-axis
    //glRotatef(-70,1.0f,0.0f,0.0f);


//    glBegin(GL_QUADS);
//        float quadcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
//        glMateriali(GL_FRONT, GL_SHININESS, 96);
//        glVertex3f(-1.5, -1.5,-3.0);
//        glVertex3f(1.5, -1.5,-3.0);
//        glVertex3f(1.5, 1.5,-3.0);
//        glVertex3f(-1.5, 1.5,-3.0);

//        float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
//        glMateriali(GL_FRONT, GL_SHININESS, 96);
//        glutSolidSphere(1, 40, 40);

    //glTranslatef(-2.0f, 2.0f, -3.0f);
//        glColor3f(1.,1.,0.); glVertex3f(-1.0, -1.0,0.0);
//        glColor3f(1.,1.,1.); glVertex3f(1.0, -1.0,0.0);
//        glColor3f(1.,0.,1.); glVertex3f(1.0, 1.0,0.0);
//        glColor3f(1.,0.,0.); glVertex3f(-1.0, 1.0,0.0);
//        glColor3f(0.,0.,1.); glutSolidSphere(2, 20, 10);

//    GLfloat mat_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
//    GLfloat mat_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
//    GLfloat mat_specular[] = { 0.774597, 0.774597, 0.774597, 1.0 };
//    GLfloat mat_shine = 0.6;

//    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialf (GL_FRONT, GL_SHININESS, mat_shine * 128);

    //glPushMatrix();
    //glTranslatef(0,0,-5.0f);
//    glColor3f(0.,0.,1.);

//    glBegin(GL_QUADS);

    //glFlush();
    //glPopMatrix();


    }else{//no game controller yet initialized so do idle animation

        //idle sequence
        glTranslatef(0.0f, 0.0f, -5.0f);            // move 5 units into the screen
        glRotatef(FrameCounter,0.0f,0.0f,1.0f);     // rotate z-axis

        glBegin(GL_QUADS);
        float quadcolor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor);
        glMateriali(GL_FRONT, GL_SHININESS, 96);
        glVertex3f(-1.5, -1.5,-3.0);
        glVertex3f(1.5, -1.5,-3.0);
        glVertex3f(1.5, 1.5,-3.0);
        glVertex3f(-1.5, 1.5,-3.0);

        //gluBeginPolygon(0);
        glBegin(GL_QUADS);
        glTranslatef(2.0f,3.0f,0.0f);
        float quadcolor2[] = { 0.1f, 0.3f, 0.5f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, quadcolor2);
        glMateriali(GL_FRONT, GL_SHININESS, 96);

        glVertex3f(-1.5+1, -1.5,-1.0);
        glVertex3f(1.5+1, -1.5,-1.0);
        glVertex3f(1.5+1, 1.5,-1.0);
        glVertex3f(-1.5+1, 1.5,-1.0);

//        float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
//        glMateriali(GL_FRONT, GL_SHININESS, 96);
//        glutSolidSphere(1, 40, 40);

        glEnd();
    }
}
