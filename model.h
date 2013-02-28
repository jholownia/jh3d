/*
================================
 model.h

 Created on: 27 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#ifndef MODEL_H
#define MODEL_H

#include <string>

namespace jh
{

typedef int Index[3];

struct Vector3D;
struct Vertex;
class Triangle;

class Model
{
public:
    Model();
    virtual ~Model();

    bool init(std::string filename);

    // void render(device); ?

    Triangle* getMesh();
    int getIndexCount() const;


private:
    int vertexCount_;
    int indexCount_;
    Vertex* vertexBuffer_;
    Index* indexBuffer_;
    Triangle* mesh_;


    bool loadModel(std::string filename);
    void createMesh();

    void releaseBuffers();

};

} // namespace jh

#endif // MODEL_H
