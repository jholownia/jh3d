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


RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    model_(NULL)
{
    antialiased_ = false;
    depthSort_ = true;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    // default viewParams values
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}


void RenderArea::setPen(QPen const& pen)
{
    pen_ = pen;
    update();
}

void RenderArea::setBrush(QBrush const& brush)
{
    brush_ = brush;
    update();
}

void RenderArea::setAntialiased(bool aa)
{
    antialiased_ = aa;
    update();
}

void RenderArea::setModel(jh::Model* model)
{
    model_ = model;
}

void RenderArea::updateView(ViewParams viewParams)
{
    viewParams_ = viewParams;
    update();
}

void RenderArea::setDepthSort(bool sort)
{
    depthSort_ = sort;
    update();
}

void RenderArea::paintEvent(QPaintEvent* event)
{
    if (model_ == NULL)
    {
        return;
    }

    using namespace jh;

    QPainter painter(this);
    painter.setPen(pen_);
    painter.setBrush(brush_);

    if (antialiased_)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }

    Triangle* mesh = model_->getMesh();

    if (depthSort_)
    {
        std::sort(mesh, mesh + model_->getIndexCount());
    }

    Matrix perspectiveMatrix, rotationMatrixX, rotationMatrixY, rotationMatrixZ, translationMatrix, scaleMatrix;

    perspectiveMatrix.CreatePerspective(viewParams_.focalLength);
    rotationMatrixX.createRotationX(viewParams_.rotationX);
    rotationMatrixY.createRotationY(viewParams_.rotationY);
    rotationMatrixZ.createRotationZ(viewParams_.rotationZ);
    translationMatrix.CreateTranslattion(viewParams_.translationX, viewParams_.translationY, viewParams_.translationZ);
    scaleMatrix.CreateScale(viewParams_.scaleX, viewParams_.scaleY, viewParams_.scaleZ);

//    perspectiveMatrix.CreatePerspective(400.0f);
//    rotationMatrix.createRotationX(PI);
//    translationMatrix.CreateTranslattion(150.0f,150.0f,400.0f);
//    scaleMatrix.CreateScale(100.0f,100.0f,100.0f);

    Matrix worldMatrix = scaleMatrix * translationMatrix;
    Matrix rotationMatrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

    for (int i = 0; i < model_->getIndexCount(); ++i)
    {

        mesh[i].transform(rotationMatrix);
        mesh[i].transform(scaleMatrix);
        mesh[i].transform(translationMatrix);
        mesh[i].transform(perspectiveMatrix);
    }

    static QPoint points[4];

    for (int i = 0; i < model_->getIndexCount(); ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            points[j] = mesh[i].getPoint(j).toQPoint();            
        }

        painter.drawPolygon(points, 3);
    }

    delete mesh;
}
