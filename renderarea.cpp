/*
================================
 renderarea.h

 Created on: 20 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include "renderarea.h"
#include "quad.h"

#include <QPainter>

#include <iostream>

#include "model.h"
#include "triangle.h"

#include "jhmath.h"
#include <vector>


/*
================
 RenderArea::RenderArea
================
*/
RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    model_(NULL)
{
    antialiased_ = false;
    depthSort_ = true;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

/*
================
 RenderArea::sizeHint

 This implements QWidget::sizeHint for UI layout.
================
*/
QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

/*
================
 RenderArea::minimumSizeHint

 As above.
================
*/
QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}

/*
================
 RenderArea::setPen
================
*/
void RenderArea::setPen(QPen const& pen)
{
    pen_ = pen;
    update();
}

/*
================
 RenderArea::setBrush
================
*/
void RenderArea::setBrush(QBrush const& brush)
{
    brush_ = brush;
    update();
}

/*
================
 RenderArea::setAntialiased
================
*/
void RenderArea::setAntialiased(bool aa)
{
    antialiased_ = aa;
    update();
}

/*
================
 RenderArea::setModel
================
*/
void RenderArea::setModel(jh::Model* model)
{
    model_ = model;
}

/*
================
 RenderArea::updateView
================
*/
void RenderArea::updateView(ViewParams viewParams)
{
    viewParams_ = viewParams;
    update();
}

/*
================
 RenderArea::setDepthSort
================
*/
void RenderArea::setDepthSort(bool sort)
{
    depthSort_ = sort;
    update();
}

/*
================
 RenderArea::paintEvent

 This implements QWidget::paintEvent, which is executed upon calling update().
 All 2D rendering happens here.
================
*/
void RenderArea::paintEvent(QPaintEvent* event)
{
    // If we have no model to render return
    if (model_ == NULL)
    {
        return;
    }

    // We'll be using data structures from jh namespace
    using namespace jh;

    // Create a painter
    QPainter painter(this);
    painter.setPen(pen_);
    painter.setBrush(brush_);

    if (antialiased_)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }

    // Get the mesh_ of the model as a list of triangles
    Triangle* mesh = model_->getMesh();

    // If we're using depth sort, sort the polygons based on their averaged Z value
    if (depthSort_)
    {
        std::sort(mesh, mesh + model_->getIndexCount());
    }

    // Create transformation matrices
    Matrix perspectiveMatrix, rotationMatrixX, rotationMatrixY, rotationMatrixZ, translationMatrix, scaleMatrix;
    perspectiveMatrix.CreatePerspective(viewParams_.focalLength);
    rotationMatrixX.createRotationX(viewParams_.rotationX);
    rotationMatrixY.createRotationY(viewParams_.rotationY);
    rotationMatrixZ.createRotationZ(viewParams_.rotationZ);
    translationMatrix.CreateTranslattion(viewParams_.translationX, viewParams_.translationY, viewParams_.translationZ);
    scaleMatrix.CreateScale(viewParams_.scaleX, viewParams_.scaleY, viewParams_.scaleZ);

    Matrix worldMatrix = scaleMatrix * translationMatrix;
    Matrix rotationMatrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

    // Transform the mesh usgin the matrices
    for (int i = 0; i < model_->getIndexCount(); ++i)
    {

        mesh[i].transform(rotationMatrix);
        mesh[i].transform(scaleMatrix);
        mesh[i].transform(translationMatrix);
        mesh[i].transform(perspectiveMatrix);
    }

    // Convert each point of the mesh to QPoint, so they can be used by QPainter
    static QPoint points[4];

    for (int i = 0; i < model_->getIndexCount(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            points[j] = mesh[i].getPoint(j).toQPoint();            
        }

        // Draw a triangle
        painter.drawPolygon(points, 3);
    }

    delete mesh;
}
