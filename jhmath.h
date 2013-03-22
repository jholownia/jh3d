/*
================================
 jhmath.cpp

 Created on: 22 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2013.
================================
*/

#ifndef MATH_H
#define MATH_H

namespace jh
{

const float PI  =  float(3.14159265358979323846264338327950288419716939937510);
const float HALF_PI = PI * 0.5f;
const float TWO_PI = PI * 2.0f;

inline float deg2Rad(int deg)
{
    return deg * PI / 180.0f;
}

}

#endif // MATH_H
