// JLibraryDevelopment
// Transformation.hpp
// Created on 2021-05-28 by Justyn Durnford
// Last modified on 2021-07-12 by Justyn Durnford
// Header file for the Transformation class.

#pragma once

#include <JLibrary/Math/Matrix.hpp>
#include <JLibrary/Math/Vector2.hpp>
#include <JLibrary/Math/Rectangle.hpp>

namespace jlib
{
	class Transformation
	{
		Matrix<float, 4, 4> matrix_;

		public:

		// The identity Transformation (does nothing).
		static const Transformation Identity;

		// Default constructor.
		// Creates an identity transformation.
		Transformation();

		// 9-float constructor.
		// Constructs a Transformation from the Matrix given as:
		// {   a,   b,   0,   c   }
		// {   d,   e,   0,   f   }
		// {   0,   0,   1,   0   }
		// {   g,   h,   0,   i   }
		Transformation(float a, float b, float c, 
					   float d, float e, float f, 
					   float g, float h, float i);

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
		Point2f transformPoint(float X, float Y) const;

		// Returns the transformation of the given Point2_32f.
		Point2f transformPoint(const Point2f& P) const;

		// Returns the transformation of the Vector2_32f given as (X, Y).
		Vector2f transformVector(float X, float Y) const;

		// Returns the transformation of the given Vector2_32f.
		Vector2f transformVector(const Vector2f& V) const;

		// Returns the transformation of the Rectangle<float> given as Rectangle<float>(X, Y, Width, Height).
		Rectangle<float> transformRectangle(float X, float Y, float Width, float Height) const;

		// Returns the transformation of the given Rectangle<float>.
		Rectangle<float> transformRectangle(const Rectangle<float>& R) const;

		// 
		Transformation& combine(const Transformation& other);

		// 
		Transformation& translate(float offset_x, float offset_y);

		// 
		Transformation& translate(const Vector2f& offset);

		//
		Transformation& rotate(Angle angle);

		// 
		Transformation& rotate(Angle angle, float center_x, float center_y);

		// 
		Transformation& rotate(Angle angle, const Point2f& center);

		// 
		Transformation& scale(float scale_x, float scale_y);

		// 
		Transformation& scale(float scale_x, float scale_y, float center_x, float center_y);
	};
}

// Overload of binary operator *
jlib::Transformation operator * (const jlib::Transformation& A, const jlib::Transformation& B);

// Overload of binary operator *=
jlib::Transformation& operator *= (jlib::Transformation& A, const jlib::Transformation& B);

// Overload of binary operator *
jlib::Point2f operator * (const jlib::Transformation& T, const jlib::Point2f& P);

// Overload of binary operator *
jlib::Vector2f operator * (const jlib::Transformation& T, const jlib::Vector2f& V);

// Overload of binary operator ==
bool operator == (const jlib::Transformation& A, const jlib::Transformation& B);

// Overload of binary operator !=
bool operator != (const jlib::Transformation& A, const jlib::Transformation& B);