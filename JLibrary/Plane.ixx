// JLibrary
// Plane.ixx
// Created on 2022-01-19 by Justyn Durnford
// Last modified on 2022-02-11 by Justyn Durnford
// Module file for the Plane template class.

module;

#include "Arithmetic.hpp"

#include <array>
#include <string>

export module Plane;

import LinearEquation3;
import Vector3;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with planes in 3-dimensional space.
	template <arithmetic T> class Plane
	{
		public:

		Vector3<T> point;
		Vector3<T> normal;

		// Default constructor.
		// Sets the Plane's point to <0, 0, 0>.
		// Sets the Plane's normal vector to <0, 0, 1>.
		Plane()
		{
			point.set(0, 0, 0);
			normal.set(0, 0, 1);
		}

		// 
		Plane(const Vector3<T>& new_point, const Vector3<T>& new_normal)
		{
			point = new_point;
			normal = new_normal;
		}

		// 
		Plane(const Vector3<T>& A, const Vector3<T>& B, const Vector3<T>& C)
		{
			point = A;
			normal = cross_product(Vector3<T>(A, B), Vector3<T>(A, C));
		}

		// Default copy constructor.
		Plane(const Plane& other) = default;

		// Default move constructor.
		Plane(Plane&& other) = default;

		// Constructs the Plane from another type of Plane.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Plane(const Plane<U>& other)
		{
			point.x = static_cast<T>(other.point.x);
			point.y = static_cast<T>(other.point.y);
			point.z = static_cast<T>(other.point.z);

			normal.x = static_cast<T>(other.normal.x);
			normal.y = static_cast<T>(other.normal.y);
			normal.z = static_cast<T>(other.normal.z);
		}

		// Default copy assignment operator.
		Plane& operator = (const Plane& other) = default;

		// Default move assignment operator.
		Plane& operator = (Plane&& other) = default;

		// Destructor.
		~Plane() = default;

		// 
		bool doesPointLieOnPlane(const Vector3<T>& P)
		{
			return (normal.x * (P.x - point.x) + normal.y * (P.y - point.y) + normal.z * (P.z - point.z)) == 0;
		}

		// 
		LinearEquation3<T> getEquation() const
		{
			return LinearEquation3<T>(normal.x, normal.y, normal.z, point.x, point.y, point.z);
		}
	};
}