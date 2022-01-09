// JLibrary
// Circle.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the Circle template class.

module;

#include "Constants.hpp"

#include <cmath>
#include <ostream>
#include <string>

export module Circle;

import Arithmetic;
import Vector2;

export namespace jlib
{
	// 
	template <arithmetic T> class Circle
	{
		public:

		T x;
		T y;
		T r;

		// Default constructor.
		// Sets the x component of the center of the Circle to 0.
		// Sets the y component of the center of the Circle to 0.
		// Sets the radius of the Circle to 0.
		Circle()
		{
			r = static_cast<T>(0);
		}

		// 3-parameter constructor.
		// Sets the x component of the center of the Circle to new_x.
		// Sets the y component of the center of the Circle to new_y.
		// Sets the radius of the Circle to new_r.
		Circle(T new_x, T new_y, T new_r)
		{
			x = new_x;
			y = new_y;
			r = new_r;
		}

		// Point constructor.
		// Sets the center of the Circle to the given point.
		// Sets the radius of the Circle to new_r.
		Circle(const Vector2<T>& center, T new_r)
		{
			x = center.x;
			y = center.y;
			r = new_r;
		}

		// Constructs the Circle from another type of Circle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Circle(const Circle<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			r = static_cast<T>(other.r);
		}

		// Sets all the values of the Circle at once.
		// Sets the x component of the center of the Circle to new_x.
		// Sets the y component of the center of the Circle to new_y.
		// Sets the radius of the Circle to new_r.
		void set(T new_x, T new_y, T new_r)
		{
			x = new_x;
			y = new_y;
			r = new_r;
		}

		// Sets all the values of the Circle at once.
		// Sets the center of the Circle to the given point.
		// Sets the radius of the Circle to new_r.
		void set(const Vector2<T>& center, T new_r)
		{
			x = center.x;
			y = center.y;
			r = new_r;
		}

		// Returns the circumference of the Circle.
		float circumference() const
		{
			return JLIB_2PI * std::fabsf(r);
		}

		// Returns the area of the Circle.
		float area() const
		{
			return JLIB_PI * std::powf(std::fabsf(r), 2.0f);
		}

		// Checks if the given point lies within or on the Circle.
		template <arithmetic U>
		bool contains(T X, T Y)
		{
			return std::powf(X - x, 2.f) + std::powf(Y - y, 2.0f) <= std::powf(std::fabsf(r), 2.0f);
		}

		// Checks if the given point lies within or on the Circle.
		template <arithmetic U>
		bool contains(const Vector2<U>& P)
		{
			return std::powf(P.x - x, 2.0f) + std::powf(P.y - y, 2.0f) <= std::powf(std::fabsf(r), 2.0f);
		}

		// Returns a std::string representation of the Circle.
		std::string toString() const
		{
			return Vector2<T>(x, y).toString() + " @ " + std::to_string(std::fabsf(r));
		}

		// Returns a std::wstring representation of the Circle.
		std::wstring toWideString() const
		{
			return Vector2<T>(x, y).toWideString() + L" @ " + std::to_wstring(std::fabsf(r));
		}
	};

	// Checks if there is an intersection between the given Circles.
	template <arithmetic T>
	bool intersection(const Circle<T>& A, const Circle<T>& B)
	{
		return std::powf(std::fabsf(A.r) + std::fabsf(B.r), 2.0f) <= (std::powf(B.x - A.x, 2.0f) + std::powf(B.y - A.y, 2.0f));
	}

	// Overload of binary operator == 
	template <arithmetic T>
	bool operator == (const Circle<T>& A, const Circle<T>& B)
	{
		return (A.x == B.x) && (A.y == B.y) && (A.r == B.r);
	}

	// Overload of binary operator != 
	template <arithmetic T>
	bool operator != (const Circle<T>& A, const Circle<T>& B)
	{
		return (A.x != B.x) || (A.y != B.y) || (A.r != B.r);
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