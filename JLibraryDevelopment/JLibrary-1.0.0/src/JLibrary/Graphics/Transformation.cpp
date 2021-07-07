////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Transformation.cpp
// Created on 2021-05-29 by Justyn Durnford
// Last modified on 2021-07-06 by Justyn Durnford
// Source file for the Transformation class.

#include <JLibrary/Graphics/Transformation.hpp>
using namespace jlib;

// <algorithm>
using std::min;
using std::max;

// <cmath>
using std::cosf;
using std::sinf;

// <cstddef>
using std::size_t;

Transformation::Transformation()
{
	matrix_ =
	{
		{ 1.f, 0.f, 0.f, 0.f },
		{ 0.f, 1.f, 0.f, 0.f },
		{ 0.f, 0.f, 1.f, 0.f },
		{ 0.f, 0.f, 0.f, 1.f }
	};
}

Transformation::Transformation(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	matrix_ =
	{
		 {   a,   b, 0.f,   c },
		 {   d,   e, 0.f,   f },
		 { 0.f, 0.f, 1.f, 0.f },
		 {   g,   h, 0.f,   i }
	};
}

const Matrix<float, 4, 4>& Transformation::matrix() const
{
	return matrix_;
}

Transformation Transformation::inverse() const
{
	float det = determinant(matrix_);

	if (det == 0.f)
		return Transformation();

	return Transformation((matrix_(15) * matrix_(5) - matrix_(7) * matrix_(13)) / det,
						 -(matrix_(15) * matrix_(4) - matrix_(7) * matrix_(12)) / det,
						  (matrix_(13) * matrix_(4) - matrix_(5) * matrix_(12)) / det,
						 -(matrix_(15) * matrix_(1) - matrix_(3) * matrix_(13)) / det,
						  (matrix_(15) * matrix_(0) - matrix_(3) * matrix_(12)) / det,
						 -(matrix_(13) * matrix_(0) - matrix_(1) * matrix_(12)) / det,
						  (matrix_(7)  * matrix_(1) - matrix_(3) * matrix_(5))  / det,
						 -(matrix_(7)  * matrix_(0) - matrix_(3) * matrix_(4))  / det,
						  (matrix_(5)  * matrix_(0) - matrix_(1) * matrix_(4))  / det);
}

Point2f Transformation::transformPoint(float X, float Y) const
{
	return Point2f(matrix_(0) * X + matrix_(4) * Y + matrix_(12), matrix_(1) * X + matrix_(5) * Y + matrix_(13));
}

Point2f Transformation::transformPoint(const Point2f& P) const
{
	return transformPoint(P.x, P.y);
}

Vector2f Transformation::transformVector(float X, float Y) const
{
	return Vector2f(matrix_(0) * X + matrix_(4) * Y + matrix_(12), matrix_(1) * X + matrix_(5) * Y + matrix_(13));
}

Vector2f Transformation::transformVector(const Vector2f& V) const
{
	return transformVector(V.x, V.y);
}

Rectangle<float> Transformation::transformRectangle(float X, float Y, float Width, float Height) const
{
	Rectangle R(X, Y, Width, Height);

	Point2f A(transformPoint(R.topLeft()));
	Point2f B(transformPoint(R.topRight()));
	Point2f C(transformPoint(R.bottomLeft()));
	Point2f D(transformPoint(R.bottomRight()));

	float min_x = min({ A.x, B.x, C.x, D.x });
	float min_y = min({ A.y, B.y, C.y, D.y });
	float max_x = max({ A.x, B.x, C.x, D.x });
	float max_y = max({ A.y, B.y, C.y, D.y });

	return Rectangle<float>(min_x, min_y, max_x - min_x, max_y - min_y);
}

Rectangle<float> Transformation::transformRectangle(const Rectangle<float>& R) const
{
	Point2f A(transformPoint(R.topLeft()));
	Point2f B(transformPoint(R.topRight()));
	Point2f C(transformPoint(R.bottomLeft()));
	Point2f D(transformPoint(R.bottomRight()));

	float min_x = min({ A.x, B.x, C.x, D.x });
	float min_y = min({ A.y, B.y, C.y, D.y });
	float max_x = max({ A.x, B.x, C.x, D.x });
	float max_y = max({ A.y, B.y, C.y, D.y });

	return Rectangle<float>(min_x, min_y, max_x - min_x, max_y - min_y);
}

Transformation& Transformation::combine(const Transformation& other)
{
	for (size_t r(0); r < matrix_.rowCount(); ++r)
	{
		for (size_t c(0); c < matrix_.colCount(); ++c)
			matrix_(r, c) += other.matrix_(r, c);
	}

	return *this;
}

Transformation& Transformation::translate(float offset_x, float offset_y)
{
	return combine(Transformation(1.f, 0.f, offset_x, 0.f, 1.f, offset_y, 0.f, 0.f, 1.f));
}

Transformation& Transformation::translate(const Vector2f& offset)
{
	return translate(offset.x, offset.y);
}

Transformation& Transformation::rotate(Angle angle)
{
	float x = cosf(to_radians(angle.degree));
	float y = sinf(to_radians(angle.degree));

	return combine(Transformation(x, -y, 0.f, y, x, 0.f, 0.f, 0.f, 1.f));
}

Transformation& Transformation::rotate(Angle angle, float center_x, float center_y)
{
	float x = cosf(to_radians(angle.degree));
	float y = sinf(to_radians(angle.degree));

	return combine(Transformation(x, -y, center_x * (1.f - x) + center_y * y,
								  y, x, center_y * (1.f - x) - center_x * y,
								  0.f, 0.f, 1.f));
}

Transformation& Transformation::rotate(Angle angle, const Point2f& center)
{
	return rotate(angle, center.x, center.y);
}

Transformation& Transformation::scale(float scale_x, float scale_y)
{
	return combine(Transformation(scale_x, 0.f, 0.f, 0.f, scale_y, 0.f, 0.f, 0.f, 1.f));
}

Transformation& Transformation::scale(float scale_x, float scale_y, float center_x, float center_y)
{
	return combine(Transformation(scale_x, 0.f, center_x * (1.f - scale_x),
								  0.f, scale_y, center_y * (1.f - scale_y), 
								  0.f, 0.f, 1.f));
}

Transformation operator * (const Transformation& A, const Transformation& B)
{
	return Transformation(A).combine(B);
}

Transformation& operator *= (Transformation& A, const Transformation& B)
{
	return A.combine(B);
}

Point2f operator * (const Transformation& T, const Point2f& P)
{
	return T.transformPoint(P);
}

Vector2f operator * (const Transformation& T, const Vector2f& V)
{
	return T.transformVector(V);
}

bool operator == (const Transformation& A, const Transformation& B)
{
	return A.matrix() == B.matrix();
}

bool operator != (const Transformation& A, const Transformation& B)
{
	return A.matrix() != B.matrix();
}