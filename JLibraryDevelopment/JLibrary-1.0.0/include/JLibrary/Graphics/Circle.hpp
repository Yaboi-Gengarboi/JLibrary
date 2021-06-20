////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Circle.hpp
// Created on 2021-05-26 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
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

		// Copy constructor.
		Circle(const Circle& other) = default;

		// Move constructor.
		Circle(Circle&& other) = default;

		// Copy assignment operator.
		Circle& operator = (const Circle& other) = default;

		// Move assignment operator.
		Circle& operator = (Circle&& other) = default;

		// Destructor.
		~Circle() = default;

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
		inline float circumference() const
		{
			return 2.f * 3.1415927f * std::abs(radius);
		}
		
		// Returns the area of the Circle.
		inline float area() const
		{
			return 3.1415927f * std::pow(std::abs(radius), 2.f);
		}

		// Checks if the given Point2 lies within or on the Circle.
		template <std_arithmetic U>
		inline bool contains(T X, T Y)
		{
			return std::powf(X - center.x, 2.f) + std::powf(Y - center.y, 2.f) <= std::powf(std::abs(radius), 2.f);
		}

		// Checks if the given Point2 lies within or on the Circle.
		template <std_arithmetic U>
		inline bool contains(const Point2<U>& P)
		{
			return std::powf(P.x - center.x, 2.f) + std::powf(P.y - center.y, 2.f) <= std::powf(std::abs(radius), 2.f);
		}

		// Returns a std::string representation of the Circle.
		inline std::string toString() const
		{
			return center.toString() + ", " + std::to_string(std::abs(radius));
		}

		// Returns a std::string representation of the Circle.
		inline std::wstring toWString() const
		{
			return center.toWString() + ", " + std::to_wstring(std::abs(radius));
		}
	};

	// Checks if there is an intersection between the given Circles.
	template <std_arithmetic T>
	inline bool intersection(const Circle<T>& A, const Circle<T>& B)
	{
		return std::powf(std::abs(A.radius) + std::abs(B.radius), 2.f) <= (std::powf(B.center.x - A.center.x, 2.f) + std::powf(B.center.y - A.center.y, 2.f));
	}
}

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