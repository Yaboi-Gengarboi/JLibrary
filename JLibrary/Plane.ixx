// JLibrary
// Plane.ixx
// Created on 2022-01-19 by Justyn Durnford
// Last modified on 2022-03-18 by Justyn Durnford
// Module file for the Plane template class.

module;

#include "Angle.hpp"
#include "Arithmetic.hpp"

#include <cmath>
#include <string>

export module Plane;

import LinearEquation2;
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
		bool contains(const Vector3<T>& P) const
		{
			return (normal.x * (P.x - point.x) + normal.y * (P.y - point.y) + normal.z * (P.z - point.z)) == 0;
		}

		// 
		LinearEquation2<T> getEquation() const
		{
			LinearEquation2<T> eq;

			eq.coefficients[0] = normal.x / -(normal.z);
			eq.coefficients[1] = normal.y / -(normal.z);

			eq.offsets[0] = point.x;
			eq.offsets[1] = point.y;

			eq.z_offset = point.z;

			return eq;
		}
	};

	// 
	template <arithmetic T>
	bool are_parallel(const Plane<T>& A, const Plane<T>& B)
	{
		float xm = static_cast<float>(A.normal.x) / static_cast<float>(B.normal.x);
		float ym = static_cast<float>(A.normal.y) / static_cast<float>(B.normal.y);
		float zm = static_cast<float>(A.normal.z) / static_cast<float>(B.normal.z);

		return (xm == ym) && (xm == zm);
	}

	// 
	template <arithmetic T>
	bool are_orthogonal(const Plane<T>& A, const Plane<T>& B)
	{
		return angle_between(A.normal, B.normal).value == 90.0f;
	}

	// Finds the distance between the 2 given planes, assuming they are parallel.
	template <arithmetic T>
	float distance_bewteen(const Plane<T>& A, const Plane<T>& B)
	{
		if (are_parallel(A, B))
		{
			Vector3<T> PQ(A.point, B.point);
			return std::fabsf(comp_proj(PQ, A.normal));
		}

		return 0.0f;
	}

	// Calculates the angle between the 2 given planes.
	template <arithmetic T>
	Angle angle_between(const Plane<T>& A, const Plane<T>& B)
	{
		return arccosine(dot_product(A.normal, B.normal) / (A.normal.magnitude() * B.normal.magnitude()));
	}
}