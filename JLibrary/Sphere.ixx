// JLibrary
// Sphere.ixx
// Created on 2022-02-21 by Justyn Durnford
// Last modified on 2022-02-22 by Justyn Durnford
// Module file for the Sphere template class.

module;

#include "Arithmetic.hpp"
#include "Constants.hpp"

#include <cmath>
#include <ostream>
#include <string>

export module Sphere;

import Vector3;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with spheres in 3-dimensional space.
	template <arithmetic T> class Sphere
	{
		public:

		Vector3<T> center;
		T radius;

		// Default constructor.
		// Sets the x component of the center of the Sphere to 0.
		// Sets the y component of the center of the Sphere to 0.
		// Sets the z component of the center of the Sphere to 0.
		// Sets the radius of the Sphere to 0.
		Sphere()
		{
			radius = T(0);
		}

		// 4-parameter constructor.
		// Sets the x component of the center of the Sphere to new_x.
		// Sets the y component of the center of the Sphere to new_y.
		// Sets the z component of the center of the Sphere to new_z.
		// Sets the radius of the Sphere to new_radius.
		Sphere(T new_x, T new_y, T new_z, T new_radius)
		{
			center.set(new_x, new_y, new_z);
			radius = new_radius;
		}

		// Vector3 constructor.
		// Sets the center of the Sphere to new_center.
		// Sets the radius of the Sphere to new_radius.
		Sphere(const Vector3<T>& new_center, T new_radius)
		{
			center = new_center;
			radius = new_radius;
		}

		// Constructs the Sphere from another type of Sphere.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Sphere(const Sphere<U>& other)
		{
			center.copyFrom(other.center);
			radius = T(other.radius);
		}

		// Sets all the values of the Sphere at once.
		// Sets the x component of the center of the Sphere to new_x.
		// Sets the y component of the center of the Sphere to new_y.
		// Sets the z component of the center of the Sphere to new_z.
		// Sets the radius of the Sphere to new_radius.
		void set(T new_x, T new_y, T new_z, T new_radius)
		{
			center.set(new_x, new_y, new_z);
			radius = new_radius;
		}

		// Sets all the values of the Sphere at once.
		// Sets the center of the Sphere to new_center.
		// Sets the radius of the Sphere to new_radius.
		void set(const Vector3<T>& new_center, T new_radius)
		{
			center = new_center;
			radius = new_radius;
		}

		// Returns the surface area of the Sphere.
		constexpr float surfaceArea() const
		{
			return JLIB_4PI * std::powf(std::fabsf(radius), 2.0f);
		}

		// Returns the volume of the Sphere.
		constexpr float volume() const
		{
			return (4.0f / 3.0f) * JLIB_PI * std::powf(std::fabsf(radius), 3.0f);
		}

		// Checks if the given point lies within or on the Sphere.
		bool contains(T X, T Y, T Z)
		{
			return std::powf(X - center.x, 2.f) + std::powf(Y - center.y, 2.0f) + std::powf(Z - center.z, 2.0f) <= std::powf(std::fabsf(radius), 2.0f);
		}

		// Checks if the given point lies within or on the Sphere.
		template <arithmetic U>
		bool contains(U X, U Y, U Z)
		{
			return std::powf(X - center.x, 2.f) + std::powf(Y - center.y, 2.0f) + std::powf(Z - center.z, 2.0f) <= std::powf(std::fabsf(radius), 2.0f);
		}

		// Checks if the given point lies within or on the Sphere.
		bool contains(const Vector3<T>& P)
		{
			return contains(P.x, P.y, P.z);
		}

		// Checks if the given point lies within or on the Sphere.
		template <arithmetic U>
		bool contains(const Vector3<U>& P)
		{
			return contains(P.x, P.y, P.z);
		}

		// Returns a std::string representation of the Sphere.
		std::string toString() const
		{
			return center.toString() + " @ " + std::to_string(std::fabsf(radius));
		}

		// Returns a std::wstring representation of the Sphere.
		std::wstring toWideString() const
		{
			return center.toWideString() + L" @ " + std::to_wstring(std::fabsf(radius));
		}
	};

	// Checks if there is an intersection between the given Spheres.
	template <arithmetic T>
	bool intersection(const Sphere<T>& A, const Sphere<T>& B)
	{
		return std::powf(std::fabsf(A.radius) + std::fabsf(B.radius), 2.0f) <= (std::powf(B.center.x - A.center.x, 2.0f) + std::powf(B.center.y - A.center.y, 2.0f) + std::powf(B.center.z - A.center.z, 2.0f));
	}

	// Overload of binary operator == 
	template <arithmetic T>
	bool operator == (const Sphere<T>& A, const Sphere<T>& B)
	{
		return (A.center == B.center) && (A.radius == B.radius);
	}

	// Overload of binary operator != 
	template <arithmetic T>
	bool operator != (const Sphere<T>& A, const Sphere<T>& B)
	{
		return (A.center != B.center) || (A.radius != B.radius);
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Sphere<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Sphere<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}