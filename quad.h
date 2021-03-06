/*
================================
 quad.h

 Created on: 04 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#ifndef QUAD_H
#define QUAD_H

#include "point.h"
#include "matrix.h"

namespace jh
{

/*
================================

 Quad

 Represents a polygon of four points.

================================
*/
class Quad
{
public:
    Quad(Point p1, Point p2, Point p3, Point p4);

    void transform(Matrix const& matrix);

    Point getPoint(int i);

private:
    Point data_[4];
};

} // namespace jh

#endif // QUAD_H
