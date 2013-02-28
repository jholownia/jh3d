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

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    antialiased_ = false;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
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

void RenderArea::paintEvent(QPaintEvent* event)
{    
    std::cout << "paintEvent" << std::endl;

    using namespace jh;

    /*
    Quad q1(Point(0, 0, 0), Point(0, 1, 0), Point(1, 1, 0), Point(1, 0, 0));
    Quad q2(Point(0, 0, 1), Point(0, 1, 1), Point(1, 1, 1), Point(1, 0, 1));
    Quad q3(Point(0, 0, 1), Point(0, 1, 1), Point(1, 1, 1), Point(1, 0, 1));
    Quad q4(Point(0, 0, 0), Point(1, 0, 0), Point(1, 0, 1), Point(0, 0, 1));
    Quad q5(Point(0, 0, 0), Point(0, 1, 0), Point(0, 1, 1), Point(0, 0, 1));
    Quad q6(Point(1, 0, 0), Point(1, 1, 0), Point(1, 1, 1), Point(1, 0, 1));

    Quad cube[6] = {q1, q2, q3, q4, q5, q6};
    */

    QPainter painter(this);
    painter.setPen(pen_);
    painter.setBrush(brush_);

    if (antialiased_)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }

    Model model;
    if (!model.init("C:/Users/root/Documents/Qt/jh3d/Cube.txt"))
        return;

    Triangle* mesh = model.getMesh();

    Matrix perspectiveMatrix, translationMatrix, scaleMatrix;

    perspectiveMatrix.CreatePerspective(400.0f);
    translationMatrix.CreateTranslattion(50, 50, 400);
    scaleMatrix.CreateScale(1.0f, 1.0f, 1.0f);

    Matrix worldMatrix = scaleMatrix * translationMatrix;


    for (int i = 0; i < model.getIndexCount(); ++i)
    {        
        // mesh[i].transform(scaleMatrix);
        // mesh[i].transform(translationMatrix);
        mesh[i].transform(perspectiveMatrix);

        // cube[i].transform(worldMatrix);
        // cube[i].transform(scaleMatrix);
        // cube[i].transform(translationMatrix);
        // cube[i].transform(perspectiveMatrix);

    }

    static QPoint points[3];

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            points[j] = mesh[i].getPoint(j).toQPoint();
            // std::cout << "Quad[" << i << "], " << "Point[" << j << "]:" << cube[i].getPoint(j).x() << ", " << cube[i].getPoint(j).y() << ", " << cube[i].getPoint(j).z() << std::endl;
        }

        painter.drawPolygon(points, 3);
    }
}
