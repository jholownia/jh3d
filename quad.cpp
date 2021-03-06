/*
================================
 quad.h

 Created on: 04 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include "quad.h"


namespace jh
{

/*
================
 Quad::Quad
================
*/
Quad::Quad(Point p1, Point p2, Point p3, Point p4)
{
    data_[0] = p1;
    data_[1] = p2;
    data_[2] = p3;
    data_[3] = p4;
}

/*
================
 Quad::transform
================
*/
void Quad::transform(const Matrix &matrix)
{
    for (int i = 0; i < 4; ++i)
    {
        data_[i].transform(matrix);
        data_[i].rescale();
    }
}

/*
================
 Quad::getPoint
================
*/
Point Quad::getPoint(int i)
{
    return data_[i];
}


} // namespace jh
