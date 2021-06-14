// JLibraryDevelopment
// Angle.hpp
// Created on 2021-06-12 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Header file for the Angle class.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <cmath>
#include <compare>
#include <string>

namespace jlib
{
	// 
	class Angle
	{
		public:

		const static float PI;

		float degree;

		// Default constructor.
		Angle();

		// float constructor.
		// Sets the degree to the given float.
		Angle(float Degree);

		// Copy constructor.
		Angle(const Angle& other) = default;
		
		// Move constructor.
		Angle(Angle&& other) = default;

		// float assignment operator.
		// Sets the degree to the given float.
		Angle& operator = (float Degree);

		// Copy assignment operator.
		Angle& operator = (const Angle& other) = default;

		// Move assignment operator.
		Angle& operator = (Angle&& other) = default;

		// Destructor.
		~Angle() = default;

		// Returns a std::string representation of the Angle.
		std::string toString() const;

		// Returns a std::wstring representation of the Angle.
		std::wstring toWString() const;
	};

	// Returns the convertion from degrees to radians.
	float to_radians(float degree);

	// Returns the convertion from radians to degrees.
	float to_degrees(float radian);

	// Returns the sine of the Angle.
	float sine(const Angle& angle);

	// Returns the cosine of the Angle.
	float cosine(const Angle& angle);

	// Returns the tangent of the Angle.
	float tangent(const Angle& angle);

	// Returns the smallest of the two Angles.
	Angle& least(Angle& A, Angle& B);

	// Returns the largest of the two Angles.
	Angle& greatest(Angle& A, Angle& B);
}

// Overload of unary operator -
jlib::Angle operator - (const jlib::Angle& A);

// Overload of binary operator +
jlib::Angle operator + (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator +
jlib::Angle operator + (const jlib::Angle& A, float degree);

// Overload of binary operator -
jlib::Angle operator - (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator -
jlib::Angle operator - (const jlib::Angle& A, float degree);

// Overload of binary operator *
jlib::Angle operator * (const jlib::Angle& A, float scalar);

// Overload of binary operator /
jlib::Angle operator / (const jlib::Angle& A, float scalar);

// Overload of binary operator +=
jlib::Angle& operator += (jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator +=
jlib::Angle& operator += (jlib::Angle& A, float degree);

// Overload of binary operator -=
jlib::Angle& operator -= (jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator -=
jlib::Angle& operator -= (jlib::Angle& A, float degree);

// Overload of binary operator *=
jlib::Angle& operator *= (jlib::Angle& A, float scalar);

// Overload of binary operator /=
jlib::Angle& operator /= (jlib::Angle& A, float scalar);

// Overload of binary operator ==
bool operator == (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator ==
bool operator == (const jlib::Angle& A, float degree);

// Overload of binary operator !=
bool operator != (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator !=
bool operator != (const jlib::Angle& A, float degree);

// Overload of binary operator <
bool operator < (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator <
bool operator < (const jlib::Angle& A, float degree);

// Overload of binary operator <=
bool operator <= (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator <=
bool operator <= (const jlib::Angle& A, float degree);

// Overload of binary operator >
bool operator > (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator >
bool operator > (const jlib::Angle& A, float degree);

// Overload of binary operator >=
bool operator >= (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator >=
bool operator >= (const jlib::Angle& A, float degree);

// Overload of binary operator <=>
std::strong_ordering operator <=> (const jlib::Angle& A, const jlib::Angle& B);

// Overload of binary operator <=>
std::strong_ordering operator <=> (const jlib::Angle& A, float degree);