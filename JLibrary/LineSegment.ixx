// JLibrary
// LineSegment.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-28 by Justyn Durnford
// Module file for the LineSegment template class.

module;

#include "Arithmetic.hpp"

#include <initializer_list>
#include <ostream>
#include <string>

export module LineSegment;

import Vector2;

export namespace jlib
{
	// 
	template <arithmetic T> class LineSegment
	{
		public:

		Vector2<T> start;
		Vector2<T> end;

		// 
		LineSegment() = default;

		// 
		LineSegment(T Ax, T Ay, T Bx, T By)
		{
			start.set(Ax, Ay);
			end.set(Bx, By);
		}

		// 
		LineSegment(const Vector2<T>& A, const Vector2<T>& B)
		{
			start = A;
			end = B;
		}

		//
		template <arithmetic U>
		LineSegment(const LineSegment<U>& other)
		{
			start = static_cast<Vector2<T>>(other.start);
			end = static_cast<Vector2<T>>(other.end);
		}

		// 
		LineSegment(std::initializer_list<T> list)
		{
			start.set(*(list.begin() + 0), *(list.begin() + 1));
			end.set(*(list.begin() + 2), *(list.begin() + 3));
		}

		// 
		LineSegment& operator = (std::initializer_list<T> list)
		{
			start.set(*(list.begin() + 0), *(list.begin() + 1));
			end.set(*(list.begin() + 2), *(list.begin() + 3));

			return *this;
		}

		// 
		void set(T Ax, T Ay, T Bx, T By)
		{
			start.set(Ax, Ay);
			end.set(Bx, By);
		}

		// 
		Vector2<T> displacementVector() const
		{
			return Vector2<T>(start, end);
		}

		// 
		std::string toString() const
		{
			return start.toString() + " -> " + end.toString();
		}

		// 
		std::wstring toWideString() const
		{
			return start.toWideString() + L" -> " + end.toWideString();
		}
	};

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const LineSegment<T>& A, const LineSegment<T>& B)
	{
		return (A.start == B.start) && (A.end == B.end);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const LineSegment<T>& A, const LineSegment<T>& B)
	{
		return (A.start != B.start) || (A.end != B.end);
	}

	// Overload of std::ostream operator << 
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const LineSegment<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator << 
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const LineSegment<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}