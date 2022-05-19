// JLibrary
// Circle.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-02-22 by Justyn Durnford
// Module file for the Circle template class.

module;

#include "Arithmetic.hpp"
#include "Constants.hpp"

#include <cmath>
#include <ostream>
#include <string>

export module Circle;

import Vector2;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with circles in 2-dimensional space.
	template <arithmetic T> class Circle
	{
		public:

		Vector2<T> center;
		T radius;

		// Default constructor.
		// Sets the x component of the center of the Circle to 0.
		// Sets the y component of the center of the Circle to 0.
		// Sets the radius of the Circle to 0.
		Circle()
		{
			radius = T(0);
		}

		// 3-parameter constructor.
		// Sets the x component of the center of the Circle to new_x.
		// Sets the y component of the center of the Circle to new_y.
		// Sets the radius of the Circle to new_radius.
		Circle(T new_x, T new_y, T new_radius)
		{
			center.set(new_x, new_y);
			radius = new_radius;
		}

		// Vector2 constructor.
		// Sets the center of the Circle to new_center.
		// Sets the radius of the Circle to new_radius.
		Circle(const Vector2<T>& new_center, T new_radius)
		{
			center = new_center;
			radius = new_radius;
		}

		// Constructs the Circle from another type of Circle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Circle(const Circle<U>& other)
		{
			center.copyFrom(other.center);
			radius = T(other.radius);
		}

		// Sets all the values of the Circle at once.
		// Sets the x component of the center of the Circle to new_x.
		// Sets the y component of the center of the Circle to new_y.
		// Sets the radius of the Circle to new_radius.
		void set(T new_x, T new_y, T new_radius)
		{
			center.set(new_x, new_y);
			radius = new_radius;
		}

		// Sets all the values of the Circle at once.
		// Sets the center of the Circle to new_center.
		// Sets the radius of the Circle to new_radius.
		void set(const Vector2<T>& new_center, T new_radius)
		{
			center = new_center;
			radius = new_radius;
		}

		// Returns the circumference of the Circle.
		constexpr float circumference() const
		{
			return JLIB_2PI * std::fabsf(radius);
		}

		// Returns the area of the Circle.
		constexpr float area() const
		{
			return JLIB_PI * std::powf(std::fabsf(radius), 2.0f);
		}

		// Checks if the given point lies within or on the Circle.
		bool contains(T x, T y)
		{
			return contains(Vector2<T>(x, y));
		}

		// Checks if the given point lies within or on the Circle.
		template <arithmetic U>
		bool contains(U x, U y)
		{
			return contains(Vector2<U>(x, y));
		}

		// Checks if the given point lies within or on the Circle.
		bool contains(const Vector2<T>& point)
		{
			return distance(center, point) <= radius;
		}

		// Checks if the given point lies within or on the Circle.
		template <arithmetic U>
		bool contains(const Vector2<U>& point)
		{
			Vector2f A(center);
			Vector2f B(point);

			return distance(A, B) <= radius;
		}

		// Returns a std::string representation of the Circle.
		std::string toString() const
		{
			return center.toString() + " @ " + std::to_string(std::fabsf(radius));
		}

		// Returns a std::wstring representation of the Circle.
		std::wstring toWideString() const
		{
			return center.toWideString() + L" @ " + std::to_wstring(std::fabsf(radius));
		}
	};

	// Checks if there is an intersection between the given Circles.
	template <arithmetic T>
	bool intersection(const Circle<T>& A, const Circle<T>& B)
	{
		return std::powf(std::fabsf(A.radius) + std::fabsf(B.radius), 2.0f) <= (std::powf(B.x - A.x, 2.0f) + std::powf(B.y - A.y, 2.0f));
	}

	// Overload of binary operator == 
	template <arithmetic T>
	bool operator == (const Circle<T>& A, const Circle<T>& B)
	{
		return (A.center == B.center) && (A.radius == B.radius);
	}

	// Overload of binary operator != 
	template <arithmetic T>
	bool operator != (const Circle<T>& A, const Circle<T>& B)
	{
		return (A.center != B.center) || (A.radius != B.radius);
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Circle<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Circle<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}