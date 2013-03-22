/*
================================
 renderareagl.h

 Created on: 21 Mar 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2013.
================================
*/

#ifndef RENDERAREAGL_H
#define RENDERAREAGL_H

#include <QGLWidget>
#include "model.h"
#include "viewparams.h"
#include "vertex.h"



class RenderAreaGL : public QGLWidget
{
    Q_OBJECT
public:
    RenderAreaGL(QWidget* parent = 0);
    ~RenderAreaGL();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void setModel(jh::Model* model);
    void updateView(ViewParams const& viewParams);

    void setSmooth(bool smooth);
    void setLightPosX(float x);
    void setLightPosY(float y);
    void setLightPosZ(float z);

    void setScale(float scale);
    
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    jh::Model* model_;
    ViewParams viewParams_;
    QPoint lastPos_;
    QColor green_;
    QColor black_;

    int rx_;
    int ry_;
    int rz_;
    float lightX_;
    float lightY_;
    float lightZ_;
    float scale_;

    void updateLight();
};

#endif // RENDERAREAGL_H
