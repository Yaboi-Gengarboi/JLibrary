// JLibraryDevelopment
// Point2.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-07-06 by Justyn Durnford
// Header file for the Point2 template class.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <JLibrary/Math/Arithmetic.hpp>
#include <JLibrary/System/StringConvert.hpp>
#include <cmath>

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with points in 2-dimensional space.
	template <std_arithmetic T> class Point2
	{
		public:

		T x;
		T y;

		// Default constructor.
		// Sets the x component of the Point2 to 0.
		// Sets the y component of the Point2 to 0.
		Point2()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
		}

		// Constructs the Point2 from the given coordinates.
		// Sets the x component of the Point2 to X.
		// Sets the y component of the Point2 to Y.
		Point2(T X, T Y)
		{
			x = X;
			y = Y;
		}

		// Constructs the Point2 from another type of Point2.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Point2(const Point2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Sets all the values of the Point2 at once.
		// Sets the x component of the Point2 to X.
		// Sets the y component of the Point2 to Y.
		void set(T X, T Y)
		{
			x = X;
			y = Y;
		}

		// Returns a std::string representation of the Point2.
		std::string toString() const
		{
			return '(' + std::to_string(x) + ", " + std::to_string(y) + ')';
		}

		// Returns a std::wstring representation of the Point2.
		std::wstring toWideString() const
		{
			return str_to_wstr(toString());
		}

		// Returns a std::u32string representation of the Point2.
		std::u32string toU32String() const
		{
			return str_to_u32str(toString());
		}
	};
	
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Returns the distance between the two Point2s.
	template <std_arithmetic T>
	float distance_between(const Point2<T>& A, const Point2<T>& B)
	{
		return std::sqrt(std::pow(B.x - A.x, 2.f) + std::pow(B.y - A.y, 2.f));
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Shorthand for jlib::Point2<char>.
	typedef jlib::Point2<char>                   Point2c;
	// Shorthand for jlib::Point2<unsigned char>.
	typedef jlib::Point2<unsigned char>          Point2uc;
	// Shorthand for jlib::Point2<short>
	typedef jlib::Point2<short>                  Point2s;
	// Shorthand for jlib::Point2<unsigned short>
	typedef jlib::Point2<unsigned short>         Point2us;
	// Shorthand for jlib::Point2<int>
	typedef jlib::Point2<int>                    Point2i;
	// Shorthand for jlib::Point2<unsigned int>
	typedef jlib::Point2<unsigned int>           Point2ui;
	// Shorthand for jlib::Point2<float>
	typedef jlib::Point2<float>                  Point2f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Point2<T>& A, const jlib::Point2<T>& B)
{
	return (A.x == B.x) && (A.y == B.y);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Point2<T>& A, const jlib::Point2<T>& B)
{
	return (A.x != B.x) || (A.y == B.y);
}