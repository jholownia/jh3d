/*
================================
 Matrix.cpp

 Created on: 04 Feb 2013
 Author: Jan Holownia

 Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2012.
================================
*/

#include "Matrix.h"
#include <math.h>


namespace jh
{

/*
================
 Matrix::Matrix
================
*/
Matrix::Matrix()
{
    fill(0.0f);
}

/*
================
 Matrix::Matrix
================
*/
Matrix::Matrix(const float &value)
{
	fill(value);
}

/*
================
 Matrix::Matrix
================
*/
Matrix::Matrix( Matrix const& other )
{
    this->data_[0] = other(0,0);
    this->data_[1] = other(0,1);
    this->data_[2] = other(0,2);
    this->data_[3] = other(0,3);

    this->data_[4] = other(1,0);
    this->data_[5] = other(1,1);
    this->data_[6] = other(1,2);
    this->data_[7] = other(1,3);

    this->data_[8] = other(2,0);
    this->data_[9] = other(2,1);
    this->data_[10] = other(2,2);
    this->data_[11] = other(2,3);

    this->data_[12] = other(3,0);
    this->data_[13] = other(3,1);
    this->data_[14] = other(3,2);
    this->data_[15] = other(3,3);
}

/*
================
 Matrix::Matrix
================
*/
Matrix::Matrix( float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44 )
{
	data_[0] = m11;
	data_[1] = m12;
	data_[2] = m13;
	data_[3] = m14;

	data_[4] = m21;
	data_[5] = m22;
	data_[6] = m23;
	data_[7] = m24;

	data_[8] = m31;
	data_[9] = m32;
	data_[10] = m33;
	data_[11] = m34;

	data_[12] = m41;
	data_[13] = m42;
	data_[14] = m43;
	data_[15] = m44;
}

/*
================
 Matrix::operator()
================
*/
float& Matrix::operator()( unsigned int row, unsigned int col )
{
    if (row >= 4 || col >= 4)        
    {
        //throw exception
    }

    return data_[4 * row + col];
}

/*
================
 Matrix::operator()
================
*/
float Matrix::operator()( unsigned int row, unsigned int col ) const
{
    if (row >= 4 || col >= 4)
    {
        //throw exception
        return 0.0f;
    }

    return data_[4 * row + col];
}

/*
================
 Matrix::operator=
================
*/
Matrix& Matrix::operator=( Matrix const& other )
{
    this->data_[0] = other(0,0);
    this->data_[1] = other(0,1);
    this->data_[2] = other(0,2);
    this->data_[3] = other(0,3);

    this->data_[4] = other(1,0);
    this->data_[5] = other(1,1);
    this->data_[6] = other(1,2);
    this->data_[7] = other(1,3);

    this->data_[8] = other(2,0);
    this->data_[9] = other(2,1);
    this->data_[10] = other(2,2);
    this->data_[11] = other(2,3);

    this->data_[12] = other(3,0);
    this->data_[13] = other(3,1);
    this->data_[14] = other(3,2);
    this->data_[15] = other(3,3);

    return *this;
}

/*
================
 Matrix::operator*=
================
*/
Matrix& Matrix::operator*=( Matrix const& other )
{
    Matrix result;

    result(0,0) = data_[0] * other(0,0) + data_[1] * other(1,0) + data_[2] * other(2,0) + data_[3] * other(3,0);
    result(0,1) = data_[0] * other(0,1) + data_[1] * other(1,1) + data_[2] * other(2,1) + data_[3] * other(3,1);
    result(0,2) = data_[0] * other(0,2) + data_[1] * other(1,2) + data_[2] * other(2,2) + data_[3] * other(3,2);
    result(0,3) = data_[0] * other(0,3) + data_[1] * other(1,3) + data_[2] * other(2,3) + data_[3] * other(3,3);

    result(0,0) = data_[4] * other(0,0) + data_[5] * other(1,0) + data_[6] * other(2,0) + data_[7] * other(3,0);
    result(0,1) = data_[4] * other(0,1) + data_[5] * other(1,1) + data_[6] * other(2,1) + data_[7] * other(3,1);
    result(0,2) = data_[4] * other(0,2) + data_[5] * other(1,2) + data_[6] * other(2,2) + data_[7] * other(3,2);
    result(0,3) = data_[4] * other(0,3) + data_[5] * other(1,3) + data_[6] * other(2,3) + data_[7] * other(3,3);

    result(0,0) = data_[8] * other(0,0) + data_[9] * other(1,0) + data_[10] * other(2,0) + data_[11] * other(3,0);
    result(0,1) = data_[8] * other(0,1) + data_[9] * other(1,1) + data_[10] * other(2,1) + data_[11] * other(3,1);
    result(0,2) = data_[8] * other(0,2) + data_[9] * other(1,2) + data_[10] * other(2,2) + data_[11] * other(3,2);
    result(0,3) = data_[8] * other(0,3) + data_[9] * other(1,3) + data_[10] * other(2,3) + data_[11] * other(3,3);

    result(0,0) = data_[12] * other(0,0) + data_[13] * other(1,0) + data_[14] * other(2,0) + data_[15] * other(3,0);
    result(0,1) = data_[12] * other(0,1) + data_[13] * other(1,1) + data_[14] * other(2,1) + data_[15] * other(3,1);
    result(0,2) = data_[12] * other(0,2) + data_[13] * other(1,2) + data_[14] * other(2,2) + data_[15] * other(3,2);
    result(0,3) = data_[12] * other(0,3) + data_[13] * other(1,3) + data_[14] * other(2,3) + data_[15] * other(3,3);

    return *this;
}

/*
================
 Matrix::operator*=
================
*/
Matrix& Matrix::operator*=( float value )
{
    Matrix result;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result(row, col) = data_[4 * row + col] * value;
        }
    }

    return *this;
}

/*
================
 Matrix::operator+=
================
*/
Matrix& Matrix::operator+=( Matrix const& other )
{
    Matrix result;

    result(0,0) = data_[0] + other(0,0);
    result(0,1) = data_[1] + other(0,1);
    result(0,2) = data_[2] + other(0,2);
    result(0,3) = data_[3] + other(0,3);

    result(1,0) = data_[4] + other(1,0);
    result(1,1) = data_[5] + other(1,1);
    result(1,2) = data_[6] + other(1,2);
    result(1,3) = data_[7] + other(1,3);

    result(2,0) = data_[8] + other(2,0);
    result(2,1) = data_[9] + other(2,1);
    result(2,2) = data_[10] + other(2,2);
    result(2,3) = data_[11] + other(2,3);

    result(3,0) = data_[12] + other(3,0);
    result(3,1) = data_[13] + other(3,1);
    result(3,2) = data_[14] + other(3,2);
    result(3,3) = data_[15] + other(3,3);

    return *this;
}

/*
================
 Matrix::operator-=
================
*/
Matrix& Matrix::operator-=( Matrix const& other )
{
    Matrix result;

    result(0,0) = data_[0] - other(0,0);
    result(0,1) = data_[1] - other(0,1);
    result(0,2) = data_[2] - other(0,2);
    result(0,3) = data_[3] - other(0,3);

    result(1,0) = data_[4] - other(1,0);
    result(1,1) = data_[5] - other(1,1);
    result(1,2) = data_[6] - other(1,2);
    result(1,3) = data_[7] - other(1,3);

    result(2,0) = data_[8] - other(2,0);
    result(2,1) = data_[9] - other(2,1);
    result(2,2) = data_[10] - other(2,2);
    result(2,3) = data_[11] - other(2,3);

    result(3,0) = data_[12] - other(3,0);
    result(3,1) = data_[13] - other(3,1);
    result(3,2) = data_[14] - other(3,2);
    result(3,3) = data_[15] - other(3,3);

    return *this;
}

/*
================
 Matrix::operator/=
================
*/
Matrix& Matrix::operator/=( float value )
{
    Matrix result;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result(row, col) = data_[4 * row + col] / value;
        }
    }

    return *this;
}

/*
================
 Matrix::operator*
================
*/
Matrix Matrix::operator*( Matrix const& other ) const
{
    Matrix result;

    result(0,0) = (data_[0] * other(0,0)) + (data_[1] * other(1,0)) + (data_[2] * other(2,0)) + (data_[3] * other(3,0));
    result(0,1) = data_[0] * other(0,1) + data_[1] * other(1,1) + data_[2] * other(2,1) + data_[3] * other(3,1);
    result(0,2) = data_[0] * other(0,2) + data_[1] * other(1,2) + data_[2] * other(2,2) + data_[3] * other(3,2);
    result(0,3) = data_[0] * other(0,3) + data_[1] * other(1,3) + data_[2] * other(2,3) + data_[3] * other(3,3);

    result(1,0) = data_[4] * other(0,0) + data_[5] * other(1,0) + data_[6] * other(2,0) + data_[7] * other(3,0);
    result(1,1) = data_[4] * other(0,1) + data_[5] * other(1,1) + data_[6] * other(2,1) + data_[7] * other(3,1);
    result(1,2) = data_[4] * other(0,2) + data_[5] * other(1,2) + data_[6] * other(2,2) + data_[7] * other(3,2);
    result(1,3) = data_[4] * other(0,3) + data_[5] * other(1,3) + data_[6] * other(2,3) + data_[7] * other(3,3);

    result(2,0) = data_[8] * other(0,0) + data_[9] * other(1,0) + data_[10] * other(2,0) + data_[11] * other(3,0);
    result(2,1) = data_[8] * other(0,1) + data_[9] * other(1,1) + data_[10] * other(2,1) + data_[11] * other(3,1);
    result(2,2) = data_[8] * other(0,2) + data_[9] * other(1,2) + data_[10] * other(2,2) + data_[11] * other(3,2);
    result(2,3) = data_[8] * other(0,3) + data_[9] * other(1,3) + data_[10] * other(2,3) + data_[11] * other(3,3);

    result(3,0) = data_[12] * other(0,0) + data_[13] * other(1,0) + data_[14] * other(2,0) + data_[15] * other(3,0);
    result(3,1) = data_[12] * other(0,1) + data_[13] * other(1,1) + data_[14] * other(2,1) + data_[15] * other(3,1);
    result(3,2) = data_[12] * other(0,2) + data_[13] * other(1,2) + data_[14] * other(2,2) + data_[15] * other(3,2);
    result(3,3) = data_[12] * other(0,3) + data_[13] * other(1,3) + data_[14] * other(2,3) + data_[15] * other(3,3);

    return result;
}

/*
================
 Matrix::operator*
================
*/
Matrix Matrix::operator*( float value ) const
{
    Matrix result;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result(row, col) = data_[4 * row + col] * value;
        }
    }

    return result;
}

/*
================
 Matrix::operator+
================
*/
Matrix Matrix::operator+( Matrix const& other ) const
{
    Matrix result;

    result(0,0) = data_[0] + other(0,0);
    result(0,1) = data_[1] + other(0,1);
    result(0,2) = data_[2] + other(0,2);
    result(0,3) = data_[3] + other(0,3);

    result(1,0) = data_[4] + other(1,0);
    result(1,1) = data_[5] + other(1,1);
    result(1,2) = data_[6] + other(1,2);
    result(1,3) = data_[7] + other(1,3);

    result(2,0) = data_[8] + other(2,0);
    result(2,1) = data_[9] + other(2,1);
    result(2,2) = data_[10] + other(2,2);
    result(2,3) = data_[11] + other(2,3);

    result(3,0) = data_[12] + other(3,0);
    result(3,1) = data_[13] + other(3,1);
    result(3,2) = data_[14] + other(3,2);
    result(3,3) = data_[15] + other(3,3);

    return result;
}

/*
================
 Matrix::operator-
================
*/
Matrix Matrix::operator-( Matrix const& other ) const
{
    Matrix result;

    result(0,0) = data_[0] - other(0,0);
    result(0,1) = data_[1] - other(0,1);
    result(0,2) = data_[2] - other(0,2);
    result(0,3) = data_[3] - other(0,3);

    result(1,0) = data_[4] - other(1,0);
    result(1,1) = data_[5] - other(1,1);
    result(1,2) = data_[6] - other(1,2);
    result(1,3) = data_[7] - other(1,3);

    result(2,0) = data_[8] - other(2,0);
    result(2,1) = data_[9] - other(2,1);
    result(2,2) = data_[10] - other(2,2);
    result(2,3) = data_[11] - other(2,3);

    result(3,0) = data_[12] - other(3,0);
    result(3,1) = data_[13] - other(3,1);
    result(3,2) = data_[14] - other(3,2);
    result(3,3) = data_[15] - other(3,3);

    return result;
}

/*
================
 Matrix::operator/
================
*/
Matrix Matrix::operator/( float value ) const
{
    Matrix result;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result(row, col) = data_[4 * row + col] / value;
        }
    }

    return result;
}

/*
================
 Matrix::createIdentity
================
*/
void Matrix::createIdentity()
{
	data_[0] = 1.0f;
	data_[1] = 0.0f;
	data_[2] = 0.0f;
	data_[3] = 0.0f;

	data_[4] = 0.0f;
	data_[5] = 1.0f;
	data_[6] = 0.0f;
	data_[7] = 0.0f;

	data_[8] = 0.0f;
	data_[9] = 0.0f;
	data_[10] = 1.0f;
	data_[11] = 0.0f;

	data_[12] = 0.0f;
	data_[13] = 0.0f;
	data_[14] = 0.0f;
	data_[15] = 1.0f;
}

/*
================
 Matrix::createRotationX
================
*/
void Matrix::createRotationX( float rx )
{
	data_[0] = 1.0f;
	data_[1] = 0.0f;
	data_[2] = 0.0f;
	data_[3] = 0.0f;

	data_[4] = 0.0f;
	data_[5] = cosf(rx);
	data_[6] = sinf(rx);
	data_[7] = 0.0f;

	data_[8] = 0.0f;
	data_[9] = -sinf(rx);
	data_[10] = cosf(rx);
	data_[11] = 0.0f;

	data_[12] = 0.0f;
	data_[13] = 0.0f;
	data_[14] = 0.0f;
	data_[15] = 1.0f;
}

/*
================
 Matrix::createRotationY
================
*/
void Matrix::createRotationY( float ry )
{
	data_[0] = cosf(ry);
	data_[1] = 0.0f;
	data_[2] = -sinf(ry);
	data_[3] = 0.0f;

	data_[4] = 0.0f;
	data_[5] = 1.0f;
	data_[6] = 0.0f;
	data_[7] = 0.0f;

	data_[8] = sinf(ry);
	data_[9] = 0.0f;
	data_[10] = cosf(ry);
	data_[11] = 0.0f;

	data_[12] = 0.0f;
	data_[13] = 0.0f;
	data_[14] = 0.0f;
	data_[15] = 1.0f;
}

/*
================
 Matrix::createRotationZ
================
*/
void Matrix::createRotationZ( float rz )
{
	data_[0] = cosf(rz);
	data_[1] = sinf(rz);
	data_[2] = 0.0f;
	data_[3] = 0.0f;

	data_[4] = -sinf(rz);
	data_[5] = cosf(rz);
	data_[6] = 0.0f;
	data_[7] = 0.0f;

	data_[8] = 0.0f;
	data_[9] = 0.0f;
	data_[10] = 1.0f;
	data_[11] = 0.0f;

	data_[12] = 0.0f;
	data_[13] = 0.0f;
	data_[14] = 0.0f;
	data_[15] = 1.0f;
}

/*
================
 Matrix::CreateTranslation
================
*/
void Matrix::CreateTranslattion( float x, float y, float z )
{
	data_[0] = 1.0f;
	data_[1] = 0.0f;
	data_[2] = 0.0f;
	data_[3] = 0.0f;

	data_[4] = 0.0f;
	data_[5] = 1.0f;
	data_[6] = 0.0f;
	data_[7] = 0.0f;

	data_[8] = 0.0f;
	data_[9] = 0.0f;
	data_[10] = 1.0f;
	data_[11] = 0.0f;

	data_[12] = x;
	data_[13] = y;
	data_[14] = z;
	data_[15] = 1.0f;
}

/*
================
 Matrix::CreateScale
================
*/
void Matrix::CreateScale( float x, float y, float z )
{
	data_[0] = x;
	data_[1] = 0.0f;
	data_[2] = 0.0f;
	data_[3] = 0.0f;

	data_[4] = 0.0f;
	data_[5] = y;
	data_[6] = 0.0f;
	data_[7] = 0.0f;

	data_[8] = 0.0f;
	data_[9] = 0.0f;
	data_[10] = z;
	data_[11] = 0.0f;

	data_[12] = 0.0f;
	data_[13] = 0.0f;
	data_[14] = 0.0f;
	data_[15] = 1.0f;
}

/*
================
 Matrix::CreatePerspective
================
*/
void Matrix::CreatePerspective( float flength )
{
	data_[0] = 1.0f;
	data_[1] = 0.0f;
	data_[2] = 0.0f;
	data_[3] = 0.0f;

	data_[4] = 0.0f;
	data_[5] = 1.0f;
	data_[6] = 0.0f;
	data_[7] = 0.0f;

	data_[8] = 0.0f;
    data_[9] = 0.0f;
    data_[10] = 1.0f;
    data_[11] = 1.0f/flength;

	data_[12] = 0.0f;
	data_[13] = 0.0f;
    data_[14] = 0.0f;
    data_[15] = 0.0f;
}

/*
================
 Matrix::fill
================
*/
void Matrix::fill( float value )
{
	for (int i = 0; i < 16; ++i)
	{
		data_[i] = value;
	}
}

} // namespace jh
