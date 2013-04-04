/*
================================
 triangle.h

 Created on: 27 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "matrix.h"

namespace jh
{

/*
================================

 Triangle

 A polygon of three points.

================================
*/
class Triangle
{
public:
    Triangle();
    Triangle(Point p1, Point p2, Point p3);

    void transform(Matrix const& matrix);

    Point getPoint(int i);

    // Used for sorting
    float getAverageZ();
    bool operator <(Triangle rhs);

private:
    Point data_[3];
};

} // namespace jh

#endif // TRIANGLE_H
