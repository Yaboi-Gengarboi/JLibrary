// JLibrary
// Rect.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the Rect template class.

module;

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#include "IntegerTypedefs.hpp"

#include <algorithm>
#include <ostream>
#include <string>

export module Rect;

import Arithmetic;
import FixedArray;
import Vector2;

export namespace jlib
{
	// 
	template <arithmetic T> class Rect
	{
		public:

		T x;
		T y;
		T w;
		T h;

		// Default constructor.
		// Sets the x component of the vertex of the Rect to 0.
		// Sets the y component of the vertex of the Rect to 0.
		// Sets the width of the Rect to 0.
		// Sets the height of the Rect to 0.
		Rect()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			w = static_cast<T>(0);
			h = static_cast<T>(0);
		}

		// 4-parameter constructor.
		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		Rect(T new_x, T new_y, T new_w, T new_h)
		{
			x = new_x;
			y = new_y;
			w = new_w;
			h = new_h;
		}

		// Single Vector2 constructor.
		// Sets the vertex of the Rect to the given point.
		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		Rect(const Vector2<T>& vertex, T new_w, T new_h)
		{
			x = vertex.x;
			y = vertex.y;
			w = new_w;
			h = new_h;
		}

		// Double Vector2 constructor.
		// Sets the vertex of the Rect to the given point.
		// Sets the dimensions of the Rect to the given dimensions.
		Rect(const Vector2<T>& vertex, const Vector2<T>& dimensions)
		{
			x = vertex.x;
			y = vertex.y;
			w = dimensions.x;
			h = dimensions.y;
		}

		// Default copy constructor.
		Rect(const Rect& other) = default;

		// Default move constructor.
		Rect(Rect&& other) = default;

		// Constructs the Rect from another type of Rect.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Rect(const Rect<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			w = static_cast<T>(other.w);
			h = static_cast<T>(other.h);
		}

		// Default copy assignment operator.
		Rect& operator = (const Rect& other) = default;

		// Default move assignment operator.
		Rect& operator = (Rect&& other) = default;

		// Destructor.
		~Rect() = default;

		// Sets all the values of the Rect at once.
		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		void set(T new_x, T new_y, T new_w, T new_h)
		{
			x = new_x;
			y = new_y;
			w = new_w;
			h = new_h;
		}

		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		void setVertex(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Sets the vertex of the Rect to the given point.
		void setVertex(const Vector2<T>& vertex)
		{
			x = vertex.x;
			y = vertex.y;
		}

		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		void setDimensions(T new_w, T new_h)
		{
			w = new_w;
			h = new_h;
		}

		// Sets the dimensions of the Rect to the given dimensions.
		void setDimensions(const Vector2<T>& dimensions)
		{
			w = dimensions.x;
			h = dimensions.y;
		}

		// Returns the perimeter of the Rect.
		float perimeter() const
		{
			return 2.0f * (w + h);
		}

		// Returns the area of the Rect.
		float area() const
		{
			return w * h;
		}

		// Returns the top-left vertex of the Rect.
		Vector2<T> topLeft() const
		{
			return Vector2<T>(std::min(x, x + w), std::min(y, y + h));
		}

		// Returns the top-right vertex of the Rect.
		Vector2<T> topRight() const
		{
			return Vector2<T>(std::max(x, x + w), std::min(y, y + h));
		}

		// Returns the bottom-left vertex of the Rect.
		Vector2<T> bottomLeft() const
		{
			return Vector2<T>(std::min(x, x + w), std::max(y, y + h));
		}

		// Returns the bottom-right vertex of the Rect.
		Vector2<T> bottomRight() const
		{
			return Vector2<T>(std::max(x, x + w), std::max(y, y + h));
		}

		// Returns the dimensions of the Rect.
		Vector2<T> dimensions() const
		{
			return Vector2<T>(w, h);
		}

		// Returns a FixedArray containing the vertices of the Rect.
		FixedArray<Vector2<T>, 4> getVertices() const
		{
			FixedArray<Vector2<T>, 4> arr;

			arr[0] = topLeft();
			arr[1] = topRight();
			arr[2] = bottomLeft();
			arr[3] = bottomRight();

			return arr;
		}

		// Checks if the given point lies within or on the Rect.
		template <arithmetic U>
		bool contains(U X, U Y)
		{
			T minX = std::min(x, static_cast<T>(x + w));
			T maxX = std::max(x, static_cast<T>(x + w));
			T minY = std::min(y, static_cast<T>(y + h));
			T maxY = std::max(y, static_cast<T>(y + h));

			return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
		}

		// Checks if the given point lies within or on the Rect.
		template <arithmetic U>
		bool contains(const Vector2<U>& point)
		{
			return contains(point.x, point.y);
		}

		// Returns a std::string representation of the Rect.
		std::string toString() const
		{
			return Vector2<T>(x, y).toString() + ", [" + std::to_string(w) + " x " + std::to_string(h) + ']';
		}

		// Returns a std::wstring representation of the Rect.
		std::wstring toWideString() const
		{
			return Vector2<T>(x, y).toWideString() + L", [" + std::to_wstring(w) + L" x " + std::to_wstring(h) + L']';
		}
	};

	// Checks if there is an intersection between the given Rects.
	template <arithmetic T>
	bool intersection(const Rect<T>& A, const Rect<T>& B)
	{
		Vector2<T> ATL(A.topLeft());
		Vector2<T> BTL(B.topLeft());
		Vector2<T> ABR(A.bottomRight());
		Vector2<T> BBR(B.bottomRight());

		if ((ABR.x < BTL.x) || (ABR.y < BTL.y) || (BBR.x < ATL.x) || (BBR.y < ATL.y))
			return false;
		return true;
	}

	typedef jlib::Rect<i32>       IntRect;
	typedef jlib::Rect<u32>       UIntRect;
	typedef jlib::Rect<float>     FloatRect;

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Rect<T>& A, const Rect<T>& B)
	{
		return (A.x == B.x) && (A.y == B.y) && (A.w == B.w) && (A.h == B.h);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Rect<T>& A, const Rect<T>& B)
	{
		return (A.x != B.x) || (A.y != B.y) || (A.w != B.w) || (A.h != B.h);
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Rect<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Rect<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}