// JLibraryDevelopment
// Rectangle.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-05-26 by Justyn Durnford
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

		// Default constructor.
		Rectangle()
		{
			width = static_cast<T>(0);
			height = static_cast<T>(0);
		}

		// 4-parameter constructor.
		// Sets the x component of the vertex of the Rectangle to X.
		// Sets the y component of the vertex of the Rectangle to Y.
		// Sets the width of the Rectangle to Width.
		// Sets the height of the Rectangle to Height.
		Rectangle(T X, T Y, T Width, T Height)
		{
			vertex.set(X, Y);
			width = Width;
			height = Height;
		}

		// Point2 constructor.
		// Sets the vertex of the Rectangle to the given Point2.
		// Sets the width of the Rectangle to Width.
		// Sets the height of the Rectangle to Height.
		Rectangle(const Point2<T>& P, T Width, T Height)
		{
			vertex = P;
			width = Width;
			height = Height;
		}

		// Constructs the Rectangle from another type of Rectangle.
		//
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		//
		// \param other: Rectangle to convert
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

		// Returns the top-left vertex of the Rectangle.
		Point2<T> topLeft() const
		{
			return vertex;
		}

		// Returns the top-right vertex of the Rectangle.
		Point2<T> topRight() const
		{
			return Point2<T>(vertex.x + width, vertex.y);
		}

		// Returns the bottom-left vertex of the Rectangle.
		Point2<T> bottomLeft() const
		{
			return Point2<T>(vertex.x, vertex.y + height);
		}

		// Returns the bottom-right vertex of the Rectangle.
		Point2<T> bottomRight() const
		{
			return Point2<T>(vertex.x + width, vertex.y + height);
		}

		// Sets the x component of the vertex of the Rectangle to X.
		// Sets the y component of the vertex of the Rectangle to Y.
		// Sets the width of the Rectangle to Width.
		// Sets the height of the Rectangle to Height.
		void set(T X, T Y, T Width, T Height)
		{
			vertex.set(X, Y);
			width = Width;
			height = Height;
		}

		// Returns the perimeter of the Rectangle.
		double perimeter() const
		{
			return 2.0 * (width + height);
		}

		// Returns the area of the Rectangle.
		double area() const
		{
			return width * height;
		}

		// Returns true if the Rectangle contains the Point2.
		template <std_arithmetic U>
		bool contains(const Point2<U>& P)
		{
			return (P.x >= vertex.x) && (P.x <= vertex.x += width) && (P.y >= vertex.y) && (P.y <= vertex.y + height);
		}

		// Returns a std::string representation of the Rectangle.
		std::string toString() const
		{
			return vertex.toString() + ", " + std::to_string(width) + ", " + std::to_string(height);
		}

		// Returns a std::wstring representation of the Rectangle.
		std::wstring toWString() const
		{
			return vertex.toWString() + L", " + std::to_wstring(width) + L", " + std::to_wstring(height);
		}
	};

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

template <jl::std_arithmetic T>
bool operator == (const jl::Rectangle<T>& A, const jl::Rectangle<T>& B)
{
	return (A.vertex == B.vertex) && (A.width == B.width) && (A.height == B.height);
}

template <jl::std_arithmetic T>
bool operator != (const jl::Rectangle<T>& A, const jl::Rectangle<T>& B)
{
	return (A.vertex != B.vertex) || (A.width != B.width) || (A.height != B.height);
}