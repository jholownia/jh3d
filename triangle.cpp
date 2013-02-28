/*
================================
 triangle.cpp

 Created on: 27 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include "triangle.h"

namespace jh
{

Triangle::Triangle()
{
    // bad
    data_[0] = 0;
    data_[1] = 0;
    data_[2] = 0;
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    data_[0] = p1;
    data_[1] = p2;
    data_[2] = p3;
}

void Triangle::transform(const Matrix &matrix)
{
    for (int i = 0; i < 3; ++i)
    {
        data_[i].transform(matrix);
        data_[i].rescale();
    }
}

Point Triangle::getPoint(int i)
{
    return data_[i];
}

} // namespace jh
