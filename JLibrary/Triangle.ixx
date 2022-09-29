// JLibrary
// Triangle.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-09-28 by Justyn Durnford
// Module file for the Triangle template class.

module;

#include "Arithmetic.hpp"

#include <ostream>
#include <string>

export module Triangle;

import Vector2;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with triangles in 2-dimensional space.
	template <arithmetic T> class Triangle
	{
		public:

		Vector2<T> A;
		Vector2<T> B;
		Vector2<T> C;

		// Default constructor.
		// Sets each vertex of the Triangle to (0, 0).
		Triangle() = default;

		// Sets the A vertex to the point given by (Ax, Ay).
		// Sets the B vertex to the point given by (Bx, By).
		// Sets the C vertex to the point given by (Cx, Cy).
		Triangle(T Ax, T Ay, T Bx, T By, T Cx, T Cy)
		{
			A = Vector2<T>(Ax, Ay);
			B = Vector2<T>(Bx, By);
			C = Vector2<T>(Cx, Cy);
		}

		// Sets the A vertex to the point given by a.
		// Sets the B vertex to the point given by b.
		// Sets the C vertex to the point given by c.
		Triangle(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c)
		{
			A = a;
			B = b;
			C = c;
		}

		// Constructs the Triangle from another type of Triangle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Triangle(const Triangle<U>& other)
		{
			A.x = static_cast<T>(other.A.x);
			A.y = static_cast<T>(other.A.y);
			B.x = static_cast<T>(other.B.x);
			B.y = static_cast<T>(other.B.y);
			C.x = static_cast<T>(other.C.x);
			C.y = static_cast<T>(other.C.y);
		}

		// Sets all the values of the Triangle at once.
		// Sets the A vertex to the point given by (Ax, Ay).
		// Sets the B vertex to the point given by (Bx, By).
		// Sets the C vertex to the point given by (Cx, Cy).
		void set(T Ax, T Ay, T Bx, T By, T Cx, T Cy)
		{
			A = Vector2<T>(Ax, Ay);
			B = Vector2<T>(Bx, By);
			C = Vector2<T>(Cx, Cy);
		}

		// Sets all the values of the Triangle at once.
		// Sets the A vertex to the point given by a.
		// Sets the B vertex to the point given by b.
		// Sets the C vertex to the point given by c.
		void set(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c)
		{
			A = a;
			B = b;
			C = c;
		}

		// Returns a std::string representation of the Triangle.
		std::string toString() const
		{
			return "A: " + A.toString() + ", B: " + B.toString() + ", C: " + C.toString();
		}

		// Returns a std::wstring representation of the Triangle.
		std::wstring toWideString() const
		{
			return L"A: " + A.toWideString() + L", B: " + B.toWideString() + L", C: " + C.toWideString();
		}
	};

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Triangle<T>& T1, const Triangle<T>& T2)
	{
		return (T1.A == T2.A) && (T1.B == T2.B) && (T1.C == T2.C);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Triangle<T>& T1, const Triangle<T>& T2)
	{
		return (T1.A != T2.A) || (T1.B != T2.B) || (T1.C != T2.C);
	}

	// Overload of std::ostream operator << 
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Triangle<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator << 
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Triangle<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}