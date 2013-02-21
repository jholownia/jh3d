/*
================================
 mainwindow.h

 Created on: 20 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include "renderarea.h"
#include "quad.h"

#include <QPainter>

#include <iostream>

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
    std::cout << "Painting" << std::endl;


    using namespace jh;

    Quad q1(Point(0, 0, 0), Point(0, 1, 0), Point(1, 1, 0), Point(1, 0, 0));
    Quad q2(Point(0, 0, 1), Point(0, 1, 1), Point(1, 1, 1), Point(1, 0, 1));
    Quad q3(Point(0, 0, 1), Point(0, 1, 1), Point(1, 1, 1), Point(1, 0, 1));
    Quad q4(Point(0, 0, 0), Point(1, 0, 0), Point(1, 0, 1), Point(0, 0, 1));
    Quad q5(Point(0, 0, 0), Point(0, 1, 0), Point(0, 1, 1), Point(0, 0, 1));
    Quad q6(Point(1, 0, 0), Point(1, 1, 0), Point(1, 1, 1), Point(1, 0, 1));

    Quad cube[6] = {q1, q2, q3, q4, q5, q6};

    // static const QPoint points[4] =
    // {
//        QPoint(10, 80),
 //        QPoint(20, 10),
 //        QPoint(80, 30),
 //       QPoint(90, 70)
//    };

    QPainter painter(this);
    painter.setPen(pen_);
    painter.setBrush(brush_);

    if (antialiased_)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }

    Matrix perspectiveMatrix, translationMatrix, scaleMatrix;

    perspectiveMatrix.CreatePerspective(3.0f);
    translationMatrix.CreateTranslattion(20, 10, 10);
    scaleMatrix.CreateScale(150.0f, 150.0f, 150.0f);

    static QPoint points[4];

    for (int i = 0; i < 6; ++i)
    {
        cube[i].transform(scaleMatrix);
        // cube[i].transform(translationMatrix);
        cube[i].transform(perspectiveMatrix);

    }


    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            points[j] = cube[i].getPoint(j).toQPoint();
            std::cout << "Quad[" << i << "], " << "Point[" << j << "]:" << cube[i].getPoint(j).x() << ", " << cube[i].getPoint(j).y() << ", " << cube[i].getPoint(j).z() << std::endl;
        }

        painter.drawPolygon(points, 4);
    }
}
