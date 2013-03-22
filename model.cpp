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

#include <QGLWidget>

#include <QMatrix4x4>
#include <QVector3D>

#include <qmath.h>

namespace jh
{

struct Geometry
{
    Geometry();
    QVector<GLushort> faces;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    void appendSmooth(const QVector3D &a, const QVector3D &n, int from);
    void appendFaceted(const QVector3D &a, const QVector3D &n);
    void finalize();
    void loadArrays() const;
    void translate(const QVector3D &t);
    void rotate(qreal deg, QVector3D axis);
    void draw() const;

    QMatrix4x4 mat;
    GLfloat faceColor[4];
};

static inline void qSetColor(float colorVec[], QColor c)
{
    colorVec[0] = c.redF();
    colorVec[1] = c.greenF();
    colorVec[2] = c.blueF();
    colorVec[3] = c.alphaF();
}

static inline void qMultMatrix(const QMatrix4x4 &mat)
{
    if (sizeof(qreal) == sizeof(GLfloat))
        glMultMatrixf((GLfloat*)mat.constData());
#ifndef QT_OPENGL_ES
    else if (sizeof(qreal) == sizeof(GLdouble))
        glMultMatrixd((GLdouble*)mat.constData());
#endif
    else
    {
        GLfloat fmat[16];
        qreal const *r = mat.constData();
        for (int i = 0; i < 16; ++i)
            fmat[i] = r[i];
        glMultMatrixf(fmat);
    }
}

Geometry::Geometry()
{
    qSetColor(faceColor, QColor(Qt::darkGray));
}

void Geometry::loadArrays() const
{
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glNormalPointer(GL_FLOAT, 0, normals.constData());
}

void Geometry::finalize()
{
    // TODO: add vertex buffer uploading here

    // Finish smoothing normals by ensuring accumulated normals are returned
    // to length 1.0.
    for (int i = 0; i < normals.count(); ++i)
        normals[i].normalize();
}

void Geometry::appendSmooth(const QVector3D &a, const QVector3D &n, int from)
{
    // Smooth normals are acheived by averaging the normals for faces meeting
    // at a point.  First find the point in geometry already generated
    // (working backwards, since most often the points shared are between faces
    // recently added).
    int v = vertices.count() - 1;
    for ( ; v >= from; --v)
        if (qFuzzyCompare(vertices[v], a))
            break;
    if (v < from)
    {
        // The vert was not found so add it as a new one, and initialize
        // its corresponding normal
        v = vertices.count();
        vertices.append(a);
        normals.append(n);
    }
    else
    {
        // Vert found, accumulate normals into corresponding normal slot.
        // Must call finalize once finished accumulating normals
        normals[v] += n;
    }
    // In both cases (found or not) reference the vert via its index
    faces.append(v);
}

void Geometry::appendFaceted(const QVector3D &a, const QVector3D &n)
{
    // Faceted normals are achieved by duplicating the vert for every
    // normal, so that faces meeting at a vert get a sharp edge.
    int v = vertices.count();
    vertices.append(a);
    normals.append(n);
    faces.append(v);
}

void Geometry::rotate(qreal deg, QVector3D axis)
{
    mat.rotate(deg, axis);
}

void Geometry::translate(const QVector3D &t)
{
    mat.translate(t);
}

void Geometry::draw() const
{
    glPushMatrix();
    qMultMatrix(mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faceColor);

    const GLushort *indices = faces.constData();
    glDrawElements(GL_TRIANGLES, this->faces.count(), GL_UNSIGNED_SHORT, indices);
    glPopMatrix();
}

Model::Model() :
    vertexCount_  (0),
    indexCount_   (0),
    vertexBuffer_ (NULL),
    indexBuffer_  (NULL),
    geometry_     (NULL),
    smooth_       (false)
{

}

Model::~Model()
{
    releaseBuffers();
    delete geometry_;
}


bool Model::init(std::string filename)
{

    if (!loadModel(filename))
    {
        return false;
    }

    createMesh();
    createGeometry();

    return true;
}

Triangle *Model::getMesh()
{
    Triangle* mesh = new Triangle[indexCount_];

    for (int i = 0; i < indexCount_; ++i)
    {
        Point p1(vertexBuffer_[indexBuffer_[i][0]].position.x, vertexBuffer_[indexBuffer_[i][0]].position.y, vertexBuffer_[indexBuffer_[i][0]].position.z);
        Point p2(vertexBuffer_[indexBuffer_[i][1]].position.x, vertexBuffer_[indexBuffer_[i][1]].position.y, vertexBuffer_[indexBuffer_[i][1]].position.z);
        Point p3(vertexBuffer_[indexBuffer_[i][2]].position.x, vertexBuffer_[indexBuffer_[i][2]].position.y, vertexBuffer_[indexBuffer_[i][2]].position.z);

        Triangle t(p1, p2, p3);
        mesh[i] = t;
    }

    return mesh;
}

int Model::getIndexCount() const
{
    return indexCount_;
}

void Model::Render() const
{
    geometry_->loadArrays();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    geometry_->draw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Model::setColor(QColor c)
{
    qSetColor(geometry_->faceColor, c);
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

void Model::createGeometry()
{
    if (geometry_ == NULL)
    {
        geometry_ = new Geometry();
    }
    else
    {
        delete geometry_;
        geometry_ = new Geometry();
    }

    for (int i = 0; i < indexCount_; ++i)
    {
        QVector3D a(vertexBuffer_[indexBuffer_[i][0]].position.x, vertexBuffer_[indexBuffer_[i][0]].position.y, vertexBuffer_[indexBuffer_[i][0]].position.z);
        QVector3D b(vertexBuffer_[indexBuffer_[i][1]].position.x, vertexBuffer_[indexBuffer_[i][1]].position.y, vertexBuffer_[indexBuffer_[i][1]].position.z);
        QVector3D c(vertexBuffer_[indexBuffer_[i][2]].position.x, vertexBuffer_[indexBuffer_[i][2]].position.y, vertexBuffer_[indexBuffer_[i][2]].position.z);
        QVector3D norm = QVector3D::normal(a, b, c);

        if (smooth_)
        {
            geometry_->appendSmooth(a, norm, indexCount_);
            geometry_->appendSmooth(b, norm, indexCount_);
            geometry_->appendSmooth(c, norm, indexCount_);
        }
        else
        {
            geometry_->appendFaceted(a, norm);
            geometry_->appendFaceted(b, norm);
            geometry_->appendFaceted(c, norm);
        }
    }

    geometry_->finalize();
}

void Model::setSmooth(bool smooth)
{
    smooth_ = smooth;
    createGeometry();
}

void Model::translate(QVector3D t)
{
    geometry_->translate(t);
}

void Model::releaseBuffers()
{
    // delete[] mesh_;
    delete[] indexBuffer_;
    delete[] vertexBuffer_;
}




} // namespace jh
