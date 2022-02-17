// JLibrary
// Square.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-28 by Justyn Durnford
// Module file for the Square template class.

module;

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

#include <algorithm>
#include <ostream>
#include <string>

export module Square;

import FixedArray;
import Vector2;

export namespace jlib
{
	// 
	template <arithmetic T> class Square
	{
		public:

		T x;
		T y;
		T l;

		// Default constructor.
		// Sets the x component of the vertex of the Square to 0.
		// Sets the y component of the vertex of the Square to 0.
		// Sets the length of the Square to 0.
		Square()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			l = static_cast<T>(0);
		}

		// 3-parameter constructor.
		// Sets the x component of the vertex of the Square to new_x.
		// Sets the y component of the vertex of the Square to new_y.
		// Sets the length of the Square to new_l.
		Square(T new_x, T new_y, T new_l)
		{
			x = new_x;
			y = new_y;
			l = new_l;
		}

		// Single Vector2 constructor.
		// Sets the vertex of the Square to the given point.
		// Sets the length of the Square to new_l.
		Square(const Vector2<T>& vertex, T new_l)
		{
			x = vertex.x;
			y = vertex.y;
			l = new_l;
		}

		// Default copy constructor.
		Square(const Square& other) = default;

		// Default move constructor.
		Square(Square&& other) = default;

		// Constructs the Square from another type of Square.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Square(const Square<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			l = static_cast<T>(other.l);
		}

		// Default copy assignment operator.
		Square& operator = (const Square& other) = default;

		// Default move assignment operator.
		Square& operator = (Square&& other) = default;

		// Destructor.
		~Square() = default;

		// Sets all the values of the Square at once.
		// Sets the x component of the vertex of the Square to new_x.
		// Sets the y component of the vertex of the Square to new_y.
		// Sets the length of the Square to new_l.
		void set(T new_x, T new_y, T new_l)
		{
			x = new_x;
			y = new_y;
			l = new_l;
		}

		// Sets the x component of the vertex of the Square to new_x.
		// Sets the y component of the vertex of the Square to new_y.
		void setVertex(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Sets the vertex of the Square to the given point.
		void setVertex(const Vector2<T>& vertex)
		{
			x = vertex.x;
			y = vertex.y;
		}

		// Returns the perimeter of the Square.
		float perimeter() const
		{
			return 4.0f * l;
		}

		// Returns the area of the Square.
		float area() const
		{
			return l * l;
		}

		// Returns the top-left vertex of the Square.
		Vector2<T> topLeft() const
		{
			return Vector2<T>(std::min(x, x + l), std::min(y, y + l));
		}

		// Returns the top-right vertex of the Square.
		Vector2<T> topRight() const
		{
			return Vector2<T>(std::max(x, x + l), std::min(y, y + l));
		}

		// Returns the bottom-left vertex of the Square.
		Vector2<T> bottomLeft() const
		{
			return Vector2<T>(std::min(x, x + l), std::max(y, y + l));
		}

		// Returns the bottom-right vertex of the Square.
		Vector2<T> bottomRight() const
		{
			return Vector2<T>(std::max(x, x + l), std::max(y, y + l));
		}

		// Returns a FixedArray containing the vertices of the Square.
		FixedArray<Vector2<T>, 4> getVertices() const
		{
			FixedArray<Vector2<T>, 4> arr;

			arr[0] = topLeft();
			arr[1] = topRight();
			arr[2] = bottomLeft();
			arr[3] = bottomRight();

			return arr;
		}

		// Checks if the given point lies within or on the Square.
		template <arithmetic U>
		bool contains(U X, U Y)
		{
			T minX = std::min(x, static_cast<T>(x + l));
			T maxX = std::max(x, static_cast<T>(x + l));
			T minY = std::min(y, static_cast<T>(y + l));
			T maxY = std::max(y, static_cast<T>(y + l));

			return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
		}

		// Checks if the given point lies within or on the Square.
		template <arithmetic U>
		bool contains(const Vector2<U>& point)
		{
			return contains(point.x, point.y);
		}

		// Returns a std::string representation of the Square.
		std::string toString() const
		{
			return Vector2<T>(x, y).toString() + ", [" + std::to_string(l) + " x " + std::to_string(l) + ']';
		}

		// Returns a std::wstring representation of the Square.
		std::wstring toWideString() const
		{
			return Vector2<T>(x, y).toWideString() + L", [" + std::to_wstring(l) + L" x " + std::to_wstring(l) + L']';
		}
	};

	// Checks if there is an intersection between the given Squares.
	template <arithmetic T>
	bool intersection(const Square<T>& A, const Square<T>& B)
	{
		Vector2<T> ATL(A.topLeft());
		Vector2<T> BTL(B.topLeft());
		Vector2<T> ABR(A.bottomRight());
		Vector2<T> BBR(B.bottomRight());

		if ((ABR.x < BTL.x) || (ABR.y < BTL.y) || (BBR.x < ATL.x) || (BBR.y < ATL.y))
			return false;
		return true;
	}

	typedef jlib::Square<i32>       IntSquare;
	typedef jlib::Square<u32>       UIntSquare;
	typedef jlib::Square<float>     FloatSquare;

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Square<T>& A, const Square<T>& B)
	{
		return (A.x == B.x) && (A.y == B.y) && (A.l == B.l);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Square<T>& A, const Square<T>& B)
	{
		return (A.x != B.x) || (A.y != B.y) || (A.l != B.l);
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Square<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Square<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}