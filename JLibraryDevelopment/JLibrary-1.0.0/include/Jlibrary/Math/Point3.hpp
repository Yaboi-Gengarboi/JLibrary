// JLibraryDevelopment
// Point3.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the Point3 template class.

#pragma once

#ifndef NOMINMAX
	#define NOMINMAX
#endif // NOMINMAX

#include <JLibrary/Math/Arithmetic.hpp>
#include <cmath>
#include <string>

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with points in 3-dimensional space.
	template <std_arithmetic T> class Point3
	{
		public:

		T x;
		T y;
		T z;

		// Default constructor.
		// Sets the x component of the Point3 to 0.
		// Sets the y component of the Point3 to 0.
		Point3()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
		}

		// Constructs the Point3 from the given coordinates.
		// Sets the x component of the Point3 to X.
		// Sets the y component of the Point3 to Y.
		// Sets the z component of the Point3 to Z.
		Point3(T X, T Y, T Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		// Constructs the Point3 from another type of Point3.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Point3(const Point3<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
		}

		// Sets all the values of the Point3 at once.
		// Sets the x component of the Point3 to X.
		// Sets the y component of the Point3 to Y.
		// Sets the z component of the Point3 to Z.
		void set(T X, T Y, T Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		// Returns a std::string representation of the Point3.
		std::string toString() const
		{
			return '(' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ')';
		}

		// Returns a std::wstring representation of the Point3.
		std::wstring toWideString() const
		{
			return L'(' + std::to_wstring(x) + L", " + std::to_wstring(y) + L", " + std::to_wstring(z) + L')';
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Returns the distance between the two Point3s.
	template <std_arithmetic T>
	float distance_between(const Point3<T>& A, const Point3<T>& B)
	{
		return std::sqrt(std::pow(B.x - A.x, 2.f) + std::pow(B.y - A.y, 2.f) + std::pow(B.z - A.z, 2.f));
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Shorthand for jlib::Point3<char>.
	typedef jlib::Point3<char>                   Point3c;
	// Shorthand for jlib::Point3<unsigned char>.
	typedef jlib::Point3<unsigned char>          Point3uc;
	// Shorthand for jlib::Point3<short>
	typedef jlib::Point3<short>                  Point3s;
	// Shorthand for jlib::Point3<unsigned short>
	typedef jlib::Point3<unsigned short>         Point3us;
	// Shorthand for jlib::Point3<int>
	typedef jlib::Point3<int>                    Point3i;
	// Shorthand for jlib::Point3<unsigned int>
	typedef jlib::Point3<unsigned int>           Point3ui;
	// Shorthand for jlib::Point3<float>
	typedef jlib::Point3<float>                  Point3f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Point3<T>& A, const jlib::Point3<T>& B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Point3<T>& A, const jlib::Point3<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.z != B.z);
}