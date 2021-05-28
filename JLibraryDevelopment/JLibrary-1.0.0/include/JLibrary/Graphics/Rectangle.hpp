// JLibraryDevelopment
// Rectangle.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-05-28 by Justyn Durnford
// Header file for the Rectangle template class.

#pragma once

#include <JLibrary/Math/Point2.hpp>

namespace jl
{
	// 
	template <std_arithmetic T> class Rectangle
	{
		public:

		Point2<T> vertex;
		T width;
		T height;

		// \brief Default constructor.
		// Sets the x component of the vertex of the Rectangle to 0.
		// Sets the y component of the vertex of the Rectangle to 0.
		// Sets the width of the Rectangle to 0.
		// Sets the height of the Rectangle to 0.
		Rectangle()
		{
			width = static_cast<T>(0);
			height = static_cast<T>(0);
		}

		// \brief 4-parameter constructor.
		// Sets the x component of the vertex of the Rectangle to X.
		// Sets the y component of the vertex of the Rectangle to Y.
		// Sets the width of the Rectangle to Width.
		// Sets the height of the Rectangle to Height.
		// \param X: X coordinate of the Rectangle's vertex
		// \param Y: Y coordinate of the Rectangle's vertex
		// \param Width: Width of the Rectangle
		// \param Height: Height of the Rectangle
		Rectangle(T X, T Y, T Width, T Height)
		{
			vertex.set(X, Y);
			width = Width;
			height = Height;
		}

		// \brief Point2 constructor.
		// Sets the vertex of the Rectangle to the given Point2.
		// Sets the width of the Rectangle to Width.
		// Sets the height of the Rectangle to Height.
		// \param P: Vertex of the Rectangle
		// \param Width: Width of the Rectangle
		// \param Height: Height of the Rectangle
		Rectangle(const Point2<T>& P, T Width, T Height)
		{
			vertex = P;
			width = Width;
			height = Height;
		}

		// \brief Constructs the Rectangle from another type of Rectangle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		// \param other: Rectangle to copy from.
		template <std_arithmetic U>
		explicit Rectangle(const Rectangle<U>& other)
		{
			vertex.x = static_cast<T>(other.vertex.x);
			vertex.y = static_cast<T>(other.vertex.y);
			width = static_cast<T>(other.width);
			height = static_cast<T>(other.height);
		}

		// Copy constructor.
		Rectangle(const Rectangle& other) = default;

		// Move constructor.
		Rectangle(Rectangle&& other) = default;

		// Copy assignment operator.
		Rectangle& operator = (const Rectangle& other) = default;

		// Move assignment operator.
		Rectangle& operator = (Rectangle&& other) = default;

		// \brief Sets all the values of the Rectangle at once.
		// Sets the x component of the vertex of the Rectangle to X.
		// Sets the y component of the vertex of the Rectangle to Y.
		// Sets the width of the Rectangle to Width.
		// Sets the height of the Rectangle to Height.
		// \param X: X coordinate of the Rectangle's vertex
		// \param Y: Y coordinate of the Rectangle's vertex
		// \param Width: Width of the Rectangle
		// \param Height: Height of the Rectangle
		void set(T X, T Y, T Width, T Height)
		{
			vertex.set(X, Y);
			width = Width;
			height = Height;
		}

		// Returns the perimeter of the Rectangle.
		inline double perimeter() const
		{
			return 2.0 * (width + height);
		}

		// Returns the area of the Rectangle.
		inline double area() const
		{
			return width * height;
		}

		// Returns the top-left vertex of the Rectangle.
		inline Point2<T> topLeft() const
		{
			return vertex;
		}

		// Returns the top-right vertex of the Rectangle.
		inline Point2<T> topRight() const
		{
			return Point2<T>(vertex.x + width, vertex.y);
		}

		// Returns the bottom-left vertex of the Rectangle.
		inline Point2<T> bottomLeft() const
		{
			return Point2<T>(vertex.x, vertex.y + height);
		}

		// Returns the bottom-right vertex of the Rectangle.
		inline Point2<T> bottomRight() const
		{
			return Point2<T>(vertex.x + width, vertex.y + height);
		}

		// Checks if the given Point2 lies within or on the Rectangle.
		// \param X: X coordinate of the Point2 to test
		// \param Y: Y coordinate of the Point2 to test
		template <std_arithmetic U>
		inline bool contains(T X, T Y)
		{
			return (X >= vertex.x) && (X <= vertex.x += width) && (Y >= vertex.y) && (Y <= vertex.y + height);
		}

		// Checks if the given Point2 lies within or on the Rectangle.
		// \param P: Point2 to test
		template <std_arithmetic U>
		inline bool contains(const Point2<U>& P)
		{
			return (P.x >= vertex.x) && (P.x <= vertex.x += width) && (P.y >= vertex.y) && (P.y <= vertex.y + height);
		}

		// Returns a std::string representation of the Rectangle.
		inline std::string toString() const
		{
			return vertex.toString() + ", " + std::to_string(width) + ", " + std::to_string(height);
		}

		// Returns a std::wstring representation of the Rectangle.
		inline std::wstring toWString() const
		{
			return vertex.toWString() + L", " + std::to_wstring(width) + L", " + std::to_wstring(height);
		}
	};

	// Checks if there is an intersection between the given Rectangles.
	// \param A: First Rectangle
	// \param B: Second Rectangle
	template <std_arithmetic T>
	bool intersection(const Rectangle<T>& A, const Rectangle<T>& B)
	{
		Point2<T> ABR(A.bottomRight());
		Point2<T> BBR(B.bottomRight());

		if ((ABR.x < B.vertex.x) || (ABR.y < B.vertex.y) || (BBR.x < A.vertex.x) || (BBR.y < A.vertex.y))
			return false;
		return true;
	}
}

// Overload of binary operator ==
template <jl::std_arithmetic T>
bool operator == (const jl::Rectangle<T>& A, const jl::Rectangle<T>& B)
{
	return (A.vertex == B.vertex) && (A.width == B.width) && (A.height == B.height);
}

// Overload of binary operator !=
template <jl::std_arithmetic T>
bool operator != (const jl::Rectangle<T>& A, const jl::Rectangle<T>& B)
{
	return (A.vertex != B.vertex) || (A.width != B.width) || (A.height != B.height);
}