/*
================================
 matrix.h

 Created on: 21 March 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#ifndef VIEWPARAMS_H
#define VIEWPARAMS_H

struct ViewParams
{
    float focalLength;
    float scaleX, scaleY, scaleZ;
    float translationX, translationY, translationZ;
    float rotationX, rotationY, rotationZ;
};

#endif // VIEWPARAMS_H
