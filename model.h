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
#include <QColor>
#include <QVector3D>


namespace jh
{

typedef int Index[3];

struct Vector3D;
struct Vertex;
class Triangle;
struct Geometry;

/*
================================

 Model

 This class represents a 3D model.

 It currently holds some redundant data (mesh_ and geometry_) which is used
 by 2D and OpenGL rendering respectively. This should be sorted by either using
 the same underlying data types or splitting the class in two.

================================
*/
class Model
{
public:
    Model();
    virtual ~Model();

    bool init(std::string filename);

    Triangle* getMesh();

    int getIndexCount() const;

    void Render() const;

    void setColor(QColor c);

    void createGeometry();

    void setSmooth(bool smooth);

    void translate(QVector3D t);

private:
    int vertexCount_;
    int indexCount_;
    Vertex* vertexBuffer_;
    Index* indexBuffer_;
    Triangle* mesh_;
    Geometry* geometry_;
    bool smooth_;


    bool loadModel(std::string filename);
    void createMesh();

    void releaseBuffers();
};

} // namespace jh

#endif // MODEL_H
