// JLibraryDevelopment
// Circle.hpp
// Created on 2021-05-26 by Justyn Durnford
// Last modified on 2021-05-28 by Justyn Durnford
// Header file for the Circle template class.

#pragma once

#include <JLibrary/Math/Point2.hpp>

namespace jl
{
	// 
	template <std_arithmetic T> class Circle
	{
		public:

		Point2<T> center;
		T radius;

		// \brief Default constructor.
		// Sets the x component of the center of the Circle to 0.
		// Sets the y component of the center of the Circle to 0.
		// Sets the radius of the Circle to 0.
		Circle()
		{
			radius = static_cast<T>(0);
		}

		// \brief 3-parameter constructor.
		// Sets the x component of the center of the Circle to X.
		// Sets the y component of the center of the Circle to Y.
		// Sets the radius of the Circle to Radius.
		// \param X: X coordinate of the Circle's center
		// \param Y: Y coordinate of the Circle's center
		// \param Radius: Radius of the Circle
		Circle(T X, T Y, T Radius)
		{
			center.set(X, Y);
			radius = Radius;
		}

		// \brief Point2 constructor.
		// Sets the center of the Circle to the given Point2.
		// Sets the radius of the Circle to Radius.
		// \param P: Center of the Circle
		// \param Radius: Radius of the Circle
		Circle(const Point2<T>& P, T Radius)
		{
			center = P;
			radius = Radius;
		}

		// \brief Constructs the Circle from another type of Circle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		// \param other: Circle to copy from
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

		// \brief Sets all the values of the Circle at once.
		// Sets the x component of the center of the Circle to X.
		// Sets the y component of the center of the Circle to Y.
		// Sets the radius of the Circle to Radius.
		// \param X: X coordinate of the Circle's center
		// \param Y: Y coordinate of the Circle's center
		// \param Radius: Radius of the Circle
		void set(T X, T Y, T Radius)
		{
			center.set(X, Y);
			radius = Radius;
		}

		// Returns the circumference of the Circle.
		inline double circumference() const
		{
			return 2.0 * 3.14159265358979323846 * radius;
		}
		
		// Returns the area of the Circle.
		inline double area() const
		{
			return 3.14159265358979323846 * std::pow(radius, 2.0);
		}

		// Checks if the given Point2 lies within or on the Circle.
		// \param X: X coordinate of the Point2 to test
		// \param Y: Y coordinate of the Point2 to test
		template <std_arithmetic U>
		inline bool contains(T X, T Y)
		{
			return std::pow(X - center.x, 2.0) + std::pow(Y - center.y, 2.0) <= std::pow(radius, 2.0);
		}

		// Checks if the given Point2 lies within or on the Circle.
		// \param P: Point2 to test
		template <std_arithmetic U>
		inline bool contains(const Point2<U>& P)
		{
			return std::pow(P.x - center.x, 2.0) + std::pow(P.y - center.y, 2.0) <= std::pow(radius, 2.0);
		}

		// Returns a std::string representation of the Circle.
		inline std::string toString() const
		{
			return center.toString() + ", " + std::to_string(radius);
		}

		// Returns a std::string representation of the Circle.
		inline std::wstring toWString() const
		{
			return center.toWString() + ", " + std::to_wstring(radius);
		}
	};

	// Checks if there is an intersection between the given Circles.
	// \param A: First Circle
	// \param B: Second Circle
	template <std_arithmetic T>
	inline bool intersection(const Circle<T>& A, const Circle<T>& B)
	{
		return std::pow(A.radius + B.radius, 2.0) <= (std::pow(B.center.x - A.center.x, 2.0) + std::pow(B.center.y - A.center.y, 2.0));
	}
}