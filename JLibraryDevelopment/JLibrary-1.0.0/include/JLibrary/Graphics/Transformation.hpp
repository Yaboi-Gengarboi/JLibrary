// JLibraryDevelopment
// Transformation.hpp
// Created on 2021-05-28 by Justyn Durnford
// Last modified on 2021-06-03 by Justyn Durnford
// Header file for the Transformation class.

#pragma once

#include <JLibrary/Math/Matrix.hpp>
#include <JLibrary/Math/Vector2.hpp>
#include <JLibrary/Graphics/Rectangle.hpp>

namespace jl
{
	class Transformation
	{
		Matrix<float, 4, 4> matrix_;

		public:

		// Default constructor.
		// Creates an identity transformation.
		Transformation();

		// 9-float constructor.
		// Constructs a Transformation from the Matrix given as:
		// {   a,   b,   0,   c   }
		// {   d,   e,   0,   f   }
		// {   0,   0,   1,   0   }
		// {   g,   h,   0,   i   }
		Transformation(float a, float b, float c, float d, float e, float f, float g, float h, float i);

		// Copy constructor.
		Transformation(const Transformation& other) = default;

		// Move constructor.
		Transformation(Transformation&& other) = default;

		// Copy assignment operator.
		Transformation& operator = (const Transformation& other) = default;

		// Move assignment operator.
		Transformation& operator = (Transformation && other) = default;

		// Destructor.
		~Transformation() = default;

		// Returns the Transformation Matrix.
		const Matrix<float, 4, 4>& matrix() const;

		// Returns the inverse of this Transformation.
		Transformation inverse() const;

		// Returns the transformation of the Point2_32f given as (X, Y).
		Point2_32f transformPoint(float X, float Y) const;

		// Returns the transformation of the given Point2_32f.
		Point2_32f transformPoint(const Point2_32f& P) const;

		// Returns the transformation of the Vector2_32f given as (X, Y).
		Vector2_32f transformVector(float X, float Y) const;

		// Returns the transformation of the given Vector2_32f.
		Vector2_32f transformVector(const Vector2_32f& V) const;

		// Returns the transformation of the Rectangle<float> given as Rectangle<float>(X, Y, Width, Height).
		Rectangle<float> transformRectangle(float X, float Y, float Width, float Height) const;

		// Returns the transformation of the given Rectangle<float>.
		Rectangle<float> transformRectangle(const Rectangle<float>& R) const;

		// 
		Transformation& combine(const Transformation& other);

		// 
		Transformation& translate(float offset_x, float offset_y);

		// 
		Transformation& translate(const Vector2_32f& offset);

		//
		Transformation& rotate(float angle);

		// 
		Transformation& rotate(float angle, float center_x, float center_y);

		// 
		Transformation& rotate(float angle, const Point2_32f& center);

		// 
		Transformation& scale(float scale_x, float scale_y);

		// 
		Transformation& scale(float scale_x, float scale_y, float center_x, float center_y);
	};
}

// Overload of binary operator *
jl::Transformation operator * (const jl::Transformation& A, const jl::Transformation& B);

// Overload of binary operator *=
jl::Transformation& operator *= (jl::Transformation& A, const jl::Transformation& B);

// Overload of binary operator *
jl::Point2_32f operator * (const jl::Transformation& T, const jl::Point2_32f& P);

// Overload of binary operator *
jl::Vector2_32f operator * (const jl::Transformation& T, const jl::Vector2_32f& V);

// Overload of binary operator ==
bool operator == (const jl::Transformation& A, const jl::Transformation& B);

// Overload of binary operator !=
bool operator != (const jl::Transformation& A, const jl::Transformation& B);