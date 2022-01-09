// JLibrary
// Angle.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file for the Angle class.

#pragma once

#include <array>
#include <compare>
#include <ostream>
#include <string>

namespace jlib
{
	// Returns the convertion from degrees to radians.
	constexpr float to_radians(float degree);

	// Returns the convertion from radians to degrees.
	constexpr float to_degrees(float radian);

	// Restricts the given angle to be between 0 and 360 degrees.
	void restrict_360(float& degree);

	// Returns the sine and cosine of the given degree.
	std::array<float, 2> sincos(float degree);

	class Angle
	{
		public:

		float degree;

		// Default constructor.
		Angle();

		// Float constructor.
		// Sets the Angle to the given degree.
		Angle(float new_degree);

		// Float assignment operator.
		// Sets the Angle to the given degree.
		Angle& operator = (float new_degree);

		// Returns a std::string representation of the Angle.
		std::string toString() const;

		// Returns a std::wstring representation of the Angle.
		std::wstring toWideString() const;
	};

	// Returns the sine of the Angle.
	float sine(Angle angle);

	// Returns the cosine of the Angle.
	float cosine(Angle angle);

	// Returns the tangent of the Angle.
	float tangent(Angle angle);

	// 
	Angle arcsine(float value);

	// 
	Angle arccosine(float value);

	// 
	Angle arctangent(float value);

	// Returns the smallest of the two Angles.
	Angle& least(Angle& A, Angle& B);

	// Returns the largest of the two Angles.
	Angle& greatest(Angle& A, Angle& B);
}

// Overload of binary operator ==
bool operator == (jlib::Angle A, jlib::Angle B);

// Overload of binary operator ==
bool operator == (jlib::Angle A, float degree);

// Overload of binary operator !=
bool operator != (jlib::Angle A, jlib::Angle B);

// Overload of binary operator !=
bool operator != (jlib::Angle A, float degree);

// Overload of binary operator <
bool operator < (jlib::Angle A, jlib::Angle B);

// Overload of binary operator <
bool operator < (jlib::Angle A, float degree);

// Overload of binary operator <=
bool operator <= (jlib::Angle A, jlib::Angle B);

// Overload of binary operator <=
bool operator <= (jlib::Angle A, float degree);

// Overload of binary operator >
bool operator > (jlib::Angle A, jlib::Angle B);

// Overload of binary operator >
bool operator > (jlib::Angle A, float degree);

// Overload of binary operator >=
bool operator >= (jlib::Angle A, jlib::Angle B);

// Overload of binary operator >=
bool operator >= (jlib::Angle A, float degree);

// Overload of binary operator <=>
std::strong_ordering operator <=> (jlib::Angle A, jlib::Angle B);

// Overload of binary operator <=>
std::strong_ordering operator <=> (jlib::Angle A, float degree);

// Overload of unary operator -
jlib::Angle operator - (jlib::Angle A);

// Overload of binary operator +
jlib::Angle operator + (jlib::Angle A, jlib::Angle B);

// Overload of binary operator +
jlib::Angle operator + (jlib::Angle A, float degree);

// Overload of binary operator -
jlib::Angle operator - (jlib::Angle A, jlib::Angle B);

// Overload of binary operator -
jlib::Angle operator - (jlib::Angle A, float degree);

// Overload of binary operator *
jlib::Angle operator * (jlib::Angle A, float scalar);

// Overload of binary operator /
jlib::Angle operator / (jlib::Angle A, float scalar);

// Overload of binary operator +=
jlib::Angle& operator += (jlib::Angle& A, jlib::Angle B);

// Overload of binary operator +=
jlib::Angle& operator += (jlib::Angle& A, float degree);

// Overload of binary operator -=
jlib::Angle& operator -= (jlib::Angle& A, jlib::Angle B);

// Overload of binary operator -=
jlib::Angle& operator -= (jlib::Angle& A, float degree);

// Overload of binary operator *=
jlib::Angle& operator *= (jlib::Angle& A, float scalar);

// Overload of binary operator /=
jlib::Angle& operator /= (jlib::Angle& A, float scalar);

// Overload of std::ostream operator <<
std::ostream& operator << (std::ostream& os, jlib::Angle A);

// Overload of std::wostream operator <<
std::wostream& operator << (std::wostream& wos, jlib::Angle A);