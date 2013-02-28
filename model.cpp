/*
================================
 model.cpp

 Created on: 27 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include "model.h"
#include "vertex.h"
#include "triangle.h"

#include <iostream>
#include <fstream>

namespace jh
{

Model::Model() :
    vertexCount_  (0),
    indexCount_   (0),
    vertexBuffer_ (NULL),
    indexBuffer_  (NULL),
    mesh_         (NULL)
{

}

Model::~Model()
{
    releaseBuffers();
}


bool Model::init(std::string filename)
{

    if (!loadModel(filename))
    {
        return false;
    }

    createMesh();

    return true;
}

Triangle *Model::getMesh()
{
    return mesh_;
}

int Model::getIndexCount() const
{
    return indexCount_;
}

bool Model::loadModel(std::string filename)
{
    std::ifstream ifs;

    ifs.open(filename.c_str());
    if (ifs.fail())
    {
        return false;
    }

    // Read vertex count
    ifs >> vertexCount_;

    // Create vertex buffer
    vertexBuffer_ = new Vertex[vertexCount_];

    // Read vertices
    for (int i = 0; i < vertexCount_; ++i)
    {
        ifs >> vertexBuffer_[i].position.x >> vertexBuffer_[i].position.y >> vertexBuffer_[i].position.z;
    }

    // Read index count
    ifs >> indexCount_;

    // Create index buffer
    indexBuffer_ = new Index[indexCount_];

    // Read indices
    int indices;
    for (int i = 0; i < indexCount_; ++i)
    {
        ifs >> indices >> indexBuffer_[i][0] >> indexBuffer_[i][1] >> indexBuffer_[i][2];
    }

    ifs.close();

    return true;
}

void Model::createMesh()
{
    mesh_ = new Triangle[indexCount_];

    for (int i = 0; i < indexCount_; ++i)
    {
        Point p1(vertexBuffer_[indexBuffer_[i][0]].position.x, vertexBuffer_[indexBuffer_[i][0]].position.y, vertexBuffer_[indexBuffer_[i][0]].position.z);
        Point p2(vertexBuffer_[indexBuffer_[i][1]].position.x, vertexBuffer_[indexBuffer_[i][1]].position.y, vertexBuffer_[indexBuffer_[i][1]].position.z);
        Point p3(vertexBuffer_[indexBuffer_[i][2]].position.x, vertexBuffer_[indexBuffer_[i][2]].position.y, vertexBuffer_[indexBuffer_[i][2]].position.z);

        Triangle t(p1, p2, p3);
        mesh_[i] = t;
    }
}

void Model::releaseBuffers()
{
    delete[] mesh_;
    delete[] indexBuffer_;
    delete[] vertexBuffer_;
}




} // namespace jh
