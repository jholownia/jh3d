/*
================================
 matrix.h

 Created on: 04 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/


#ifndef Matrix_H
#define Matrix_H


namespace jh
{


/*
================================

 Matrix

 A 4x4 matrix class.

================================
*/

class Matrix
{
public:
    Matrix();
    Matrix( float const& value );
    Matrix( Matrix const& other );
    Matrix( float m11, float m12, float m13, float m14,
             float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34,
             float m41, float m42, float m43, float m44);

    // Subscript operators
    float& operator() (unsigned int row, unsigned int col);
    float operator() (unsigned int row, unsigned int col) const;

    // Assignment operators
    Matrix& operator  = (Matrix const& other);
    Matrix& operator *= (Matrix const& other);
    Matrix& operator += (Matrix const& other);
    Matrix& operator -= (Matrix const& other);
    Matrix& operator *= (float value);
    Matrix& operator /= (float value);

    // Binary operators
    Matrix operator * (Matrix const& other) const;
    Matrix operator + (Matrix const& other) const;
    Matrix operator - (Matrix const& other) const;
    Matrix operator * (float other) const;
    Matrix operator / (float other) const;

    // Other initialization methods
    void createIdentity();
    void createRotationX( float rx );
    void createRotationY( float ry );
    void createRotationZ( float rz );
    void CreateTranslattion( float x, float y, float z );
    void CreateScale( float x, float y, float z );
    void CreatePerspective( float f );

private:
    float data_[16];
    
	void fill(float value);
};

} // namespace jh

#endif // Matrix_H
