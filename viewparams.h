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


/*
================================

 ViewParams

 Represents a set view parameters for RenderArea
 which can be controlled through the UI.

 This is a little bit lazy and should probably be
 implemented with a set of signals and slots like it's
 done in RenderAreaGL.

================================
*/
struct ViewParams
{
    float focalLength;
    float scaleX, scaleY, scaleZ;
    float translationX, translationY, translationZ;
    float rotationX, rotationY, rotationZ;
};

#endif // VIEWPARAMS_H
