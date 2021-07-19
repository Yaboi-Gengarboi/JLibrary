// JLibraryDevelopment
// Circle.hpp
// Created on 2021-05-26 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Header file for the Circle template class.

#pragma once

#include <JLibrary/Math/Point2.hpp>

namespace jlib
{
	// 
	template <std_arithmetic T> class Circle
	{
		public:

		Point2<T> center;
		T radius;

		// Default constructor.
		// Sets the x component of the center of the Circle to 0.
		// Sets the y component of the center of the Circle to 0.
		// Sets the radius of the Circle to 0.
		Circle()
		{
			radius = static_cast<T>(0);
		}

		// 3-parameter constructor.
		// Sets the x component of the center of the Circle to X.
		// Sets the y component of the center of the Circle to Y.
		// Sets the radius of the Circle to Radius.
		Circle(T X, T Y, T Radius)
		{
			center.set(X, Y);
			radius = Radius;
		}

		// Point2 constructor.
		// Sets the center of the Circle to the given Point2.
		// Sets the radius of the Circle to Radius.
		Circle(const Point2<T>& P, T Radius)
		{
			center = P;
			radius = Radius;
		}

		// Constructs the Circle from another type of Circle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Circle(const Circle<U>& other)
		{
			center.x = static_cast<T>(other.center.x);
			center.y = static_cast<T>(other.center.y);
			radius = static_cast<T>(other.radius);
		}

		// Sets all the values of the Circle at once.
		// Sets the x component of the center of the Circle to X.
		// Sets the y component of the center of the Circle to Y.
		// Sets the radius of the Circle to Radius.
		void set(T X, T Y, T Radius)
		{
			center.set(X, Y);
			radius = Radius;
		}

		// Returns the circumference of the Circle.
		float circumference() const
		{
			return 2.f * 3.1415927f * std::fabsf(radius);
		}
		
		// Returns the area of the Circle.
		float area() const
		{
			return 3.1415927f * std::powf(std::fabsf(radius), 2.f);
		}

		// Checks if the given Point2 lies within or on the Circle.
		template <std_arithmetic U>
		bool contains(T X, T Y)
		{
			return std::powf(X - center.x, 2.f) + std::powf(Y - center.y, 2.f) <= std::powf(std::fabsf(radius), 2.f);
		}

		// Checks if the given Point2 lies within or on the Circle.
		template <std_arithmetic U>
		bool contains(const Point2<U>& P)
		{
			return std::powf(P.x - center.x, 2.f) + std::powf(P.y - center.y, 2.f) <= std::powf(std::fabsf(radius), 2.f);
		}

		// Returns a std::string representation of the Circle.
		std::string toString() const
		{
			return center.toString() + ", " + std::to_string(std::fabsf(radius));
		}

		// Returns a std::wstring representation of the Circle.
		std::wstring toWideString() const
		{
			return center.toWideString() + L", " + std::to_wstring(std::fabsf(radius));
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Checks if there is an intersection between the given Circles.
	template <std_arithmetic T>
	bool intersection(const Circle<T>& A, const Circle<T>& B)
	{
		return std::powf(std::fabsf(A.radius) + std::fabsf(B.radius), 2.f) <= (std::powf(B.center.x - A.center.x, 2.f) + std::powf(B.center.y - A.center.y, 2.f));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator == 
template <jlib::std_arithmetic T>
bool operator == (const jlib::Circle<T>& A, const jlib::Circle<T>& B)
{
	return (A.center == B.center) && (A.radius == B.radius);
}

// Overload of binary operator != 
template <jlib::std_arithmetic T>
bool operator != (const jlib::Circle<T>& A, const jlib::Circle<T>& B)
{
	return (A.center != B.center) || (A.radius != B.radius);
}