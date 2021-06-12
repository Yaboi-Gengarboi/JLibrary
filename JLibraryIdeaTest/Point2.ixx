module;
// JLibraryIdeaTest
// Point2.ixx
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-11 by Justyn Durnford
// Module interface file for the Point2 template struct.

#include "Arithmetic.hpp"
#include <cmath>
#include <string>

export module Point2;

export namespace jl
{
	// Utility template class for representing, manipulating
	// and computing with points in 2-dimensional space.
	template <std_arithmetic T> struct Point2
	{
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

		// Copy constructor.
		Point2(const Point2& other) = default;

		// Move constructor.
		Point2(Point2&& other) = default;

		// Copy assignment operator.
		Point2& operator = (const Point2& other) = default;

		// Move assignment operator.
		Point2& operator = (Point2&& other) = default;

		// Sets all the values of the Point2 at once.
		// Sets the x component of the Point2 to X.
		// Sets the y component of the Point2 to Y.
		void set(T X, T Y)
		{
			x = X;
			y = Y;
		}

		// Returns a std::string representation of the Point2.
		inline std::string toString() const
		{
			return '(' + std::to_string(x) + ", " + std::to_string(y) + ')';
		}

		// Returns a std::wstring representation of the Point2.
		inline std::wstring toWString() const
		{
			return L'(' + std::to_wstring(x) + L", " + std::to_wstring(y) + L')';
		}
	};

	// Returns the distance between the two Point2s.
	template <std_arithmetic T>
	inline float distance_between(const Point2<T>& A, const Point2<T>& B)
	{
		return std::sqrt(std::powf(B.x - A.x, 2.f) + std::powf(B.y - A.y, 2.f));
	}

	// Define common types.
	typedef jl::Point2<char>               Point2_8i;
	typedef jl::Point2<unsigned char>      Point2_8u;
	typedef jl::Point2<short>              Point2_16i;
	typedef jl::Point2<unsigned short>     Point2_16u;
	typedef jl::Point2<int>                Point2_32i;
	typedef jl::Point2<unsigned int>       Point2_32u;
	typedef jl::Point2<float>              Point2_32f;
}

// Overload of binary operator ==
export template <jl::std_arithmetic T>
bool operator == (const jl::Point2<T>& A, const jl::Point2<T>& B)
{
	return (A.x == B.x) && (A.y == B.y);
}

// Overload of binary operator !=
export template <jl::std_arithmetic T>
bool operator != (const jl::Point2<T>& A, const jl::Point2<T>& B)
{
	return (A.x != B.x) || (A.y == B.y);
}