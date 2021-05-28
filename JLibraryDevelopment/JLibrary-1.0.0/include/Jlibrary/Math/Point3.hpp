// JLibraryDevelopment
// Point3.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-05-26 by Justyn Durnford
// Header file for the Point3 template class.

#pragma once

#include <Jlibrary/Math/Arithmetic.hpp>

#include <cmath>
#include <string>

namespace jl
{
	// Utility template class for representing, manipulating
	// and computing with points in 3-dimensional space.
	template <std_arithmetic T> class Point3
	{
		public:

		T x;
		T y;
		T z;

		// \brief Default constructor.
		// Sets the x component of the Point3 to 0.
		// Sets the y component of the Point3 to 0.
		Point3()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
		}

		// \brief Constructs the Point2 from the given coordinates.
		// Sets the x component of the Point3 to X.
		// Sets the y component of the Point3 to Y.
		// Sets the z component of the Point3 to Z.
		// \param X: X coordinate
		// \param Y: Y coordinate
		// \param Z: Z coordinate
		Point3(T X, T Y, T Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		// \brief Constructs the Point3 from another type of Point3.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		// \param other: Point3 to copy from
		template <std_arithmetic U>
		explicit Point3(const Point3<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
		}

		// Copy constructor.
		Point3(const Point3& other) = default;

		// Move constructor.
		Point3(Point3&& other) = default;

		// Copy assignment operator.
		Point3& operator = (const Point3& other) = default;

		// Move assignment operator.
		Point3& operator = (Point3&& other) = default;

		// \brief Sets all the values of the Point3 at once.
		// Sets the x component of the Point3 to X.
		// Sets the y component of the Point3 to Y.
		// Sets the z component of the Point3 to Z.
		// \param X: X coordinate
		// \param Y: Y coordinate
		// \param Z: Z coordinate
		void set(T X, T Y, T Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		// Returns a std::string representation of the Point3.
		inline std::string toString() const
		{
			return '(' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ')';
		}

		// Returns a std::wstring representation of the Point3.
		inline std::wstring toWString() const
		{
			return L'(' + std::to_wstring(x) + L", " + std::to_wstring(y) + L", " + std::to_wstring(z) + L')';
		}
	};

	// Returns the distance between the two Point3s.
	// \param A: First Point2
	// \param B: Second Point2
	template <std_arithmetic T>
	inline double distance_between(const Point3<T>& A, const Point3<T>& B)
	{
		return std::sqrt(std::pow(B.x - A.x, 2) + std::pow(B.y - A.y, 2) + std::pow(B.z - A.z, 2));
	}

	// Define common types
	typedef jl::Point3<char>               Point3_8;
	typedef jl::Point3<unsigned char>      Point3_8u;
	typedef jl::Point3<short>              Point3_16;
	typedef jl::Point3<unsigned short>     Point3_16u;
	typedef jl::Point3<int>                Point3_32;
	typedef jl::Point3<unsigned int>       Point3_32u;
	typedef jl::Point3<long long>          Point3_64;
	typedef jl::Point3<unsigned long long> Point3_64u;
	typedef jl::Point3<float>              Point3_32f;
	typedef jl::Point3<double>             Point3_64f;
}

// Overload of binary operator ==
template <jl::std_arithmetic T>
bool operator == (const jl::Point3<T>& A, const jl::Point3<T>& B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
}

// Overload of binary operator !=
template <jl::std_arithmetic T>
bool operator != (const jl::Point3<T>& A, const jl::Point3<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.z != B.z);
}