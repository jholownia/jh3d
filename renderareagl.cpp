/*
================================
 renderareagl.cpp

 Created on: 21 Mar 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2013.
================================
*/

#include <QtGui>
#include <QtOpenGL>
#include <math.h>

#include "renderareagl.h"
#include "model.h"

#include <QDebug>

#include <iostream>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


/*
================
 RenderAreaGL::RenderAreaGL
================
*/
RenderAreaGL::RenderAreaGL(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    model_(NULL),
    rx_(0),
    ry_(0),
    rz_(0),
    lightX_(0.5),
    lightY_(5.0),
    lightZ_(7.0),
    scale_(0.5)
{
    green_ = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    black_ = QColor::fromRgbF(0.0, 0.0, 0.0, 1.0);
}

/*
================
 RenderAreaGL::~RenderAreaGL
================
*/
RenderAreaGL::~RenderAreaGL()
{

}

/*
================
 RenderAreaGL::minimumSizeHint

 Implements QWidget::minimumSizeHint for UI layout.
================
*/
QSize RenderAreaGL::minimumSizeHint() const
{
    return QSize(400, 400);
}

/*
================
 RenderAreaGL::sizeHint

 See above.
================
*/
QSize RenderAreaGL::sizeHint() const
{
    return QSize(400, 400);
}

/*
================
 RenderAreaGL::qNormalizeAngle
================
*/
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

/*
================
 RenderAreaGL::setXRotation
================
*/
void RenderAreaGL::setXRotation(int angle)
{
    qNormalizeAngle(angle);

    if (angle != rx_)
    {
        rx_ = angle;
        updateGL();
    }
}

/*
================
 RenderAreaGL::setYRotation
================
*/
void RenderAreaGL::setYRotation(int angle)
{
    qNormalizeAngle(angle);

    if (angle != ry_)
    {
        ry_ = angle;
        updateGL();
    }
}
/*
================
 RenderAreaGL::setZRotation
================
*/
void RenderAreaGL::setZRotation(int angle)
{
    qNormalizeAngle(angle);

    if (angle != rz_)
    {
        rz_ = angle;
        updateGL();
    }
}
/*
================
 RenderAreaGL::setModel
================
*/
void RenderAreaGL::setModel(jh::Model *model)
{
    model_ = model;
    model_->setColor(green_.dark());
    updateGL();
}
/*
================
 RenderAreaGL::updateView
================
*/
void RenderAreaGL::updateView(const ViewParams &viewParams)
{
    viewParams_ = viewParams;    
    updateGL();
}
/*
================
 RenderAreaGL::setSmooth

 Whether or not we're using smoothed normals.
================
*/
void RenderAreaGL::setSmooth(bool smooth)
{
    if (model_ != NULL)
    {
        model_->setSmooth(smooth);
        model_->setColor(green_.dark());
        updateGL();
    }
}
/*
================
 RenderAreaGL::setLightPosX
================
*/
void RenderAreaGL::setLightPosX(float x)
{
     lightX_ = x;
     updateLight();
     updateGL();
}
/*
================
 RenderAreaGL::setLightPosY
================
*/
void RenderAreaGL::setLightPosY(float y)
{
    lightY_ = y;
    updateLight();
    updateGL();
}
/*
================
 RenderAreaGL::setLightPosZ
================
*/
void RenderAreaGL::setLightPosZ(float z)
{
     lightZ_ = z;
     updateLight();
     updateGL();
}
/*
================
 RenderAreaGL::setScale
================
*/
void RenderAreaGL::setScale(float scale)
{
    scale_ = scale;
    updateGL();
}
/*
================
 RenderAreaGL::initializeGL

 Sets up OpenGL scene.
================
*/
void RenderAreaGL::initializeGL()
{
    qglClearColor(black_);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    updateLight();
}
/*
================
 RenderAreaGL::paintGL

 Renders the scene on the widget.
================
*/
void RenderAreaGL::paintGL()
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rx_, 1.0, 0.0, 0.0); // rotation x
    glRotatef(ry_, 0.0, 1.0, 0.0); // rotation y
    glRotatef(rz_, 0.0, 0.0, 1.0); // rotation z
    glScalef(scale_, scale_, scale_); // scale

    if (model_ != NULL)
    {
        model_->Render();
    }
}
/*
================
 RenderAreaGL::resizeGL

 Resizes the viewport.
================
*/
void RenderAreaGL::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}
/*
================
 RenderAreaGL::mousePressEvent
================
*/
void RenderAreaGL::mousePressEvent(QMouseEvent *event)
{
    lastPos_ = event->pos();
}
/*
================
 RenderAreaGL::mouseMoveEvent

 Handles mouse input so that moving the mouse
 while the button is pressed changes the rotation of the object.
================
*/
void RenderAreaGL::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << "Mouse event";
    int dx = event->x() - lastPos_.x();
    int dy = event->y() - lastPos_.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(rx_ + 8 * dy);
        setYRotation(ry_ + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(rx_ + 8 * dy);
        setZRotation(ry_ + 8 * dx);
    }

    lastPos_ = event->pos();
}
/*
================
 RenderAreaGL::updateLight
================
*/
void RenderAreaGL::updateLight()
{
    GLfloat lightPosition[4] = { lightX_, lightY_, lightZ_, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}
