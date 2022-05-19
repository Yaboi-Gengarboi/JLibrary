// JLibrary
// Rect.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-02-22 by Justyn Durnford
// Module file for the Rect template class.

module;

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

#include <algorithm>
#include <array>
#include <ostream>
#include <string>

export module Rect;

import Vector2;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with rectangles in 2-dimensional space.
	template <arithmetic T> class Rect
	{
		public:

		Vector2<T> vertex;
		T length;
		T height;

		// Default constructor.
		// Sets the x component of the vertex of the Rect to 0.
		// Sets the y component of the vertex of the Rect to 0.
		// Sets the length of the Rect to 0.
		// Sets the height of the Rect to 0.
		Rect()
		{
			length = T(0);
			height = T(0);
		}

		// 4-parameter constructor.
		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		// Sets the length of the Rect to new_length.
		// Sets the height of the Rect to new_height.
		Rect(T new_x, T new_y, T new_length, T new_height)
		{
			vertex.set(new_x, new_y);
			length = new_length;
			height = new_height;
		}

		// Single Vector2 constructor.
		// Sets the vertex of the Rect to new_vertex.
		// Sets the length of the Rect to new_length.
		// Sets the height of the Rect to new_height.
		Rect(const Vector2<T>& new_vertex, T new_length, T new_height)
		{
			vertex = new_vertex;
			length = new_length;
			height = new_height;
		}

		// Double Vector2 constructor.
		// Sets the vertex of the Rect to new_vertex.
		// Sets the dimensions of the Rect to the given dimensions.
		Rect(const Vector2<T>& new_vertex, const Vector2<T>& dimensions)
		{
			vertex = new_vertex;
			length = dimensions.x;
			height = dimensions.y;
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
			vertex.copyFrom(other.vertex);
			length = T(other.length);
			height = T(other.height);
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
		// Sets the length of the Rect to new_length.
		// Sets the height of the Rect to new_height.
		void set(T new_x, T new_y, T new_length, T new_height)
		{
			vertex.set(new_x, new_y);
			length = new_length;
			height = new_height;
		}

		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		void setVertex(T new_x, T new_y)
		{
			vertex.set(new_x, new_y);
		}

		// Sets the vertex of the Rect to new_vertex.
		void setVertex(const Vector2<T>& new_vertex)
		{
			vertex = new_vertex;
		}

		// Sets the length of the Rect to new_length.
		// Sets the height of the Rect to new_height.
		void setDimensions(T new_length, T new_height)
		{
			length = new_length;
			height = new_height;
		}

		// Sets the dimensions of the Rect to the given dimensions.
		void setDimensions(const Vector2<T>& dimensions)
		{
			length = dimensions.x;
			height = dimensions.y;
		}

		// Returns the perimeter of the Rect.
		constexpr float perimeter() const
		{
			return 2.0f * (length + height);
		}

		// Returns the area of the Rect.
		constexpr float area() const
		{
			return length * height;
		}

		// Returns the top-left vertex of the Rect.
		Vector2<T> topLeft() const
		{
			return Vector2<T>(std::min(vertex.x, vertex.x + length), std::min(vertex.y, vertex.y + height));
		}

		// Returns the top-right vertex of the Rect.
		Vector2<T> topRight() const
		{
			return Vector2<T>(std::max(vertex.x, vertex.x + length), std::min(vertex.y, vertex.y + height));
		}

		// Returns the bottom-left vertex of the Rect.
		Vector2<T> bottomLeft() const
		{
			return Vector2<T>(std::min(vertex.x, vertex.x + length), std::max(vertex.y, vertex.y + height));
		}

		// Returns the bottom-right vertex of the Rect.
		Vector2<T> bottomRight() const
		{
			return Vector2<T>(std::max(vertex.x, vertex.x + length), std::max(vertex.y, vertex.y + height));
		}

		// Returns the dimensions of the Rect.
		Vector2<T> dimensions() const
		{
			return Vector2<T>(length, height);
		}

		// Returns a FixedArray containing the vertices of the Rect.
		std::array<Vector2<T>, 4> getVertices() const
		{
			std::array<Vector2<T>, 4> arr;

			arr[0] = topLeft();
			arr[1] = topRight();
			arr[2] = bottomLeft();
			arr[3] = bottomRight();

			return arr;
		}

		// Checks if the given point lies within or on the Rect.
		bool contains(T x, T y)
		{
			T min_x = std::min(vertex.x, vertex.x + length);
			T max_x = std::max(vertex.x, vertex.x + length);
			T min_y = std::min(vertex.y, vertex.y + height);
			T max_y = std::max(vertex.y, vertex.y + height);

			return (x >= min_x) && (x <= max_x) && (y >= min_y) && (y <= max_y);
		}

		// Checks if the given point lies within or on the Rect.
		template <arithmetic U>
		bool contains(U x, U y)
		{
			float min_x = std::min(float(vertex.x), float(vertex.x + length));
			float max_x = std::max(float(vertex.x), float(vertex.x + length));
			float min_y = std::min(float(vertex.y), float(vertex.y + height));
			float max_y = std::max(float(vertex.y), float(vertex.y + height));

			return (x >= min_x) && (x <= max_x) && (y >= min_y) && (y <= max_y);
		}

		// Checks if the given point lies within or on the Rect.
		bool contains(const Vector2<T>& point)
		{
			return contains(point.x, point.y);
		}

		// Checks if the given point lies within or on the Rect.
		template <arithmetic U>
		bool contains(const Vector2<U>& point)
		{
			return contains(float(point.x), float(point.y));
		}

		// Returns a std::string representation of the Rect.
		std::string toString() const
		{
			return vertex.toString() + ", [" + std::to_string(length) + " x " + std::to_string(height) + ']';
		}

		// Returns a std::wstring representation of the Rect.
		std::wstring toWideString() const
		{
			return vertex.toWideString() + L", [" + std::to_wstring(length) + L" x " + std::to_wstring(height) + L']';
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

		if ((ABR.vertex.x < BTL.vertex.x) || (ABR.vertex.y < BTL.vertex.y) || 
			(BBR.vertex.x < ATL.vertex.x) || (BBR.vertex.y < ATL.vertex.y))
			return false;
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	typedef jlib::Rect<i32>       IntRect;
	typedef jlib::Rect<u32>       UIntRect;
	typedef jlib::Rect<float>     FloatRect;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Rect<T>& A, const Rect<T>& B)
	{
		return (A.vertex == B.vertex) && (A.length == B.length) && (A.height == B.height);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Rect<T>& A, const Rect<T>& B)
	{
		return (A.vertex != B.vertex) || (A.length != B.length) || (A.height != B.height);
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