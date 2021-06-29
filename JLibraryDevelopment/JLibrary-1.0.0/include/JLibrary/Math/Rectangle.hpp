////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Rectangle.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-06-28 by Justyn Durnford
// Header file for the Rectangle template class

#pragma once

#include <JLibrary/Math/Point2.hpp>
#include <algorithm>

namespace jlib
{
	// 
	template <std_arithmetic T> class Rectangle
	{
		public:

		Point2<T> vertex;
		T width;
		T height;

		// Default constructor.
		// Sets the x component of the vertex of the Rectangle to 0.
		// Sets the y component of the vertex of the Rectangle to 0.
		// Sets the width of the Rectangle to 0.
		// Sets the height of the Rectangle to 0.
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
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
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

		// Sets all the values of the Rectangle at once.
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
		inline float perimeter() const
		{
			return 2.f * (width + height);
		}

		// Returns the area of the Rectangle.
		inline float area() const
		{
			return width * height;
		}

		// Returns the top-left vertex of the Rectangle.
		inline Point2<T> topLeft() const
		{
			return Point2<T>(std::min(vertex.x, vertex.x + width), std::min(vertex.y, vertex.y + height));
		}

		// Returns the top-right vertex of the Rectangle.
		inline Point2<T> topRight() const
		{
			return Point2<T>(std::max(vertex.x, vertex.x + width), std::min(vertex.y, vertex.y + height));
		}

		// Returns the bottom-left vertex of the Rectangle.
		inline Point2<T> bottomLeft() const
		{
			return Point2<T>(std::min(vertex.x, vertex.x + width), std::max(vertex.y, vertex.y + height));
		}

		// Returns the bottom-right vertex of the Rectangle.
		inline Point2<T> bottomRight() const
		{
			return Point2<T>(std::max(vertex.x, vertex.x + width), std::max(vertex.y, vertex.y + height));
		}

		// Checks if the given Point2 lies within or on the Rectangle.
		template <std_arithmetic U>
		bool contains(T X, T Y)
		{
			Point2<T> A(topLeft());
			Point2<T> B(bottomRight());

			return (X <= B.x) && (X >= A.x) && (Y <= B.y) && (Y >= A.y);
		}

		// Checks if the given Point2 lies within or on the Rectangle.
		template <std_arithmetic U>
		bool contains(const Point2<U>& P)
		{
			Point2<T> A(topLeft());
			Point2<T> B(bottomRight());

			return (P.x <= B.x) && (P.x >= A.x) && (P.y <= B.y) && (P.y >= A.y);
		}

		// Returns a std::string representation of the Rectangle.
		inline std::string toString() const
		{
			return vertex.toString() + ", " + std::to_string(width) + ", " + std::to_string(height);
		}

		// Returns a std::wstring representation of the Rectangle.
		inline std::wstring toWideString() const
		{
			return vertex.toWideString() + L", " + std::to_wstring(width) + L", " + std::to_wstring(height);
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Checks if there is an intersection between the given Rectangles.
	template <std_arithmetic T>
	bool intersection(const Rectangle<T>& A, const Rectangle<T>& B)
	{
		Point2<T> ATL(A.topLeft());
		Point2<T> BTL(B.topLeft());
		Point2<T> ABR(A.bottomRight());
		Point2<T> BBR(B.bottomRight());

		if ((ABR.x < BTL.x) || (ABR.y < BTL.y) || (BBR.x < ATL.x) || (BBR.y < ATL.y))
			return false;
		return true;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Shorthand for jlib::Rectangle<int>.
	typedef jlib::Rectangle<int>                 IntRect;
	// Shorthand for jlib::Rectangle<float>.
	typedef jlib::Rectangle<float>               FloatRect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Rectangle<T>& A, const jlib::Rectangle<T>& B)
{
	return (A.vertex == B.vertex) && (A.width == B.width) && (A.height == B.height);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Rectangle<T>& A, const jlib::Rectangle<T>& B)
{
	return (A.vertex != B.vertex) || (A.width != B.width) || (A.height != B.height);
}