/*
================================
 vertex.h

 Created on: 4 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2013.
================================
*/

#ifndef VERTEX_H
#define VERTEX_H

#include "vector3d.h"

namespace jh
{

/*
================================

 Vertex

 A simple directx-like vertex containing of 3D position.
 To implement lighting calculations we could add another
 Vector3D to it to hold a normal.

================================
*/

struct Vertex
{
    Vector3D position;
};

} // namespace jh

#endif // VERTEX_H
