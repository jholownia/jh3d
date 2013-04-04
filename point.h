/*
================================
 point.h

 Created on: 04 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/


#ifndef Point_H
#define Point_H

#include "matrix.h"
#include <QPoint>

#include <iostream>

namespace jh
{

/*
================================

 Point

 Represents a 3D point.

================================
*/
class Point
{
public:
    Point()
    {        
        data_[0] = 0.0f;
        data_[1] = 0.0f;
        data_[2] = 0.0f;
        data_[3] = 1.0f;
    }

    Point( float const& value )
    {
        data_[0] = value;
        data_[1] = value;
        data_[2] = value;
        data_[3] = 1.0f;
    }

    Point( Point const& other )
    {
        data_[0] = other.x();
        data_[1] = other.y();
        data_[2] = other.z();
        data_[3] = 1.0f;
    }

    Point( float x, float y, float z)
    {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
        data_[3] = 1.0f;
    }

    float& x(){ return data_[0]; }
    float x() const { return data_[0]; }
    float& y() { return data_[1]; }
    float y() const { return data_[1]; }
    float& z() { return data_[2]; }
    float z() const { return data_[2]; }

    void transform(Matrix const& matrix)
    {
        data_[0] = data_[0] * matrix(0,0) + data_[1] * matrix(1,0) + data_[2] * matrix(2,0) + data_[3] * matrix(3,0);
        data_[1] = data_[0] * matrix(0,1) + data_[1] * matrix(1,1) + data_[2] * matrix(2,1) + data_[3] * matrix(3,1);
        data_[2] = data_[0] * matrix(0,2) + data_[1] * matrix(1,2) + data_[2] * matrix(2,2) + data_[3] * matrix(3,2);
        data_[3] = data_[0] * matrix(0,3) + data_[1] * matrix(1,3) + data_[2] * matrix(2,3) + data_[3] * matrix(3,3);      
    }

    void rescale()
    {      
        data_[0] = data_[0] / data_[3];
        data_[1] = data_[1] / data_[3];
        data_[2] = data_[2] / data_[3];
        data_[3] = data_[3] / data_[3];       
    }

    // We need this method for Qt 2D drawing
    QPoint toQPoint() const
    {
        return QPoint(data_[0], data_[1]);
    }

private:
    float data_[4];
};

} // namespace jh

#endif // Point_H
