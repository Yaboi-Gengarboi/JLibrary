// JLibraryDevelopment
// Point2.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-05-23 by Justyn Durnford
// Header file for the Point2 template class.

#pragma once

#include <Jlibrary/Math/Arithmetic.hpp>

#include <cmath>
#include <string>

namespace jl
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
		// \param X: X coordinate
		// \param Y: Y coordinate
		Point2(T X, T Y)
		{
			x = X;
			y = Y;
		}

		// Constructs the Point2 from another type of Point2.
		//
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		//
		// \param other: Point2 to convert
		template <std_arithmetic U>
		explicit Point2(const Point2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Copy constructor.
		Point2(const Point2& other) = default;

		// Move constructor.
		Point2(Point2&& other) = default;

		// Copy assignment operator.
		Point2& operator = (const Point2& other) = default;

		// Move assignment operator.
		Point2& operator = (Point2 && other) = default;

		// Sets the Point2 from the given coordinates.
		// \param X: X coordinate
		// \param Y: Y coordinate
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
	};

	// Returns the distance between the two Point2s.
	template <std_arithmetic T, std_arithmetic U>
	inline double distance_between(const Point2<T>& A, const Point2<U>& B)
	{
		return std::sqrt(std::pow(B.x - A.x, 2) + std::pow(B.y - A.y, 2));
	}

	// Define common types
	typedef jl::Point2<char>               Point2_8;
	typedef jl::Point2<unsigned char>      Point2_8u;
	typedef jl::Point2<short>              Point2_16;
	typedef jl::Point2<unsigned short>     Point2_16u;
	typedef jl::Point2<int>                Point2_32;
	typedef jl::Point2<unsigned int>       Point2_32u;
	typedef jl::Point2<long long>          Point2_64;
	typedef jl::Point2<unsigned long long> Point2_64u;
	typedef jl::Point2<float>              Point2_32f;
	typedef jl::Point2<double>             Point2_64f;
}

// Equality comparison operator.
// Returns true if:
//  - A.x == B.x AND
//  - A.y == B.y
// Returns false otherwise.
template <jl::std_arithmetic T, jl::std_arithmetic U>
bool operator == (const jl::Point2<T>& A, const jl::Point2<U>& B)
{
	return (A.x == B.x) && (A.y == B.y);
}

// Inequality comparison operator.
// Returns true if:
//  - A.x != B.x OR
//  - A.y != B.y
// Returns false otherwise.
template <jl::std_arithmetic T, jl::std_arithmetic U>
bool operator != (const jl::Point2<T>& A, const jl::Point2<U>& B)
{
	return (A.x != B.x) || (A.y == B.y);
}