// JLibraryDevelopment
// Transformation.cpp
// Created on 2021-05-29 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Source file for the Transformation class.

#include <JLibrary/Graphics/Transformation.hpp>
using namespace std;
using namespace jlib;

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

Point2_32f Transformation::transformPoint(float X, float Y) const
{
	return Point2_32f(matrix_(0) * X + matrix_(4) * Y + matrix_(12), matrix_(1) * X + matrix_(5) * Y + matrix_(13));
}

Point2_32f Transformation::transformPoint(const Point2_32f& P) const
{
	return transformPoint(P.x, P.y);
}

Vector2_32f Transformation::transformVector(float X, float Y) const
{
	return Vector2_32f(matrix_(0) * X + matrix_(4) * Y + matrix_(12), matrix_(1) * X + matrix_(5) * Y + matrix_(13));
}

Vector2_32f Transformation::transformVector(const Vector2_32f& V) const
{
	return transformVector(V.x, V.y);
}

Rectangle<float> Transformation::transformRectangle(float X, float Y, float Width, float Height) const
{
	Rectangle R(X, Y, Width, Height);

	Point2_32f A(transformPoint(R.topLeft()));
	Point2_32f B(transformPoint(R.topRight()));
	Point2_32f C(transformPoint(R.bottomLeft()));
	Point2_32f D(transformPoint(R.bottomRight()));

	float min_x = min({ A.x, B.x, C.x, D.x });
	float min_y = min({ A.y, B.y, C.y, D.y });
	float max_x = max({ A.x, B.x, C.x, D.x });
	float max_y = max({ A.y, B.y, C.y, D.y });

	return Rectangle<float>(min_x, min_y, max_x - min_x, max_y - min_y);
}

Rectangle<float> Transformation::transformRectangle(const Rectangle<float>& R) const
{
	Point2_32f A(transformPoint(R.topLeft()));
	Point2_32f B(transformPoint(R.topRight()));
	Point2_32f C(transformPoint(R.bottomLeft()));
	Point2_32f D(transformPoint(R.bottomRight()));

	float min_x = min({ A.x, B.x, C.x, D.x });
	float min_y = min({ A.y, B.y, C.y, D.y });
	float max_x = max({ A.x, B.x, C.x, D.x });
	float max_y = max({ A.y, B.y, C.y, D.y });

	return Rectangle<float>(min_x, min_y, max_x - min_x, max_y - min_y);
}

Transformation& Transformation::combine(const Transformation& other)
{
	for (size_t r(0u); r < matrix_.rowCount(); ++r)
	{
		for (size_t c(0u); c < matrix_.colCount(); ++c)
			matrix_(r, c) += other.matrix_(r, c);
	}

	return *this;
}

Transformation& Transformation::translate(float offset_x, float offset_y)
{
	return combine(Transformation(1.f, 0.f, offset_x, 0.f, 1.f, offset_y, 0.f, 0.f, 1.f));
}

Transformation& Transformation::translate(const Vector2_32f& offset)
{
	return translate(offset.x, offset.y);
}

Transformation& Transformation::rotate(float angle)
{
	float x = cos(angle * 3.141592654f / 180.f);
	float y = sin(angle * 3.141592654f / 180.f);

	return combine(Transformation(x, -y, 0.f, y, x, 0.f, 0.f, 0.f, 1.f));
}

Transformation& Transformation::rotate(float angle, float center_x, float center_y)
{
	float x = cos(angle * 3.141592654f / 180.f);
	float y = sin(angle * 3.141592654f / 180.f);

	return combine(Transformation(x, -y, center_x * (1.f - x) + center_y * y,
								  y, x, center_y * (1.f - x) - center_x * y,
								  0.f, 0.f, 1.f));
}

Transformation& Transformation::rotate(float angle, const Point2_32f& center)
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

Point2_32f operator * (const Transformation& T, const Point2_32f& P)
{
	return T.transformPoint(P);
}

Vector2_32f operator * (const Transformation& T, const Vector2_32f& V)
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