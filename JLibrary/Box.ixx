// JLibrary
// Box.ixx
// Created on 2022-02-22 by Justyn Durnford
// Last modified on 2022-02-22 by Justyn Durnford
// Module file for the Box template class.

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

export module Box;

import Vector3;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with boxes in 3-dimensional space.
	template <arithmetic T> class Box
	{
		public:

		Vector3<T> vertex;
		T length;
		T width;
		T height;

		// Default constructor.
		// Sets the x component of the vertex of the Box to 0.
		// Sets the y component of the vertex of the Box to 0.
		// Sets the z component of the vertex of the Box to 0.
		// Sets the length of the Box to 0.
		// Sets the width of the Box to 0.
		// Sets the height of the Box to 0.
		Box()
		{
			length = T(0);
			width = T(0);
			height = T(0);
		}

		// Default constructor.
		// Sets the x component of the vertex of the Box to 0.
		// Sets the y component of the vertex of the Box to 0.
		// Sets the z component of the vertex of the Box to 0.
		// Sets the length of the Box to 0.
		// Sets the width of the Box to 0.
		// Sets the height of the Box to 0.
		Box(T new_x, T new_y, T new_z, T new_length, T new_width, T new_height)
		{
			vertex.set(new_x, new_y, new_z);
			length = new_length;
			width = new_width;
			height = new_height;
		}

		// Single Vector3 constructor.
		// Sets the vertex of the Box to new_vertex.
		// Sets the length of the Box to new_length.
		// Sets the width of the Box to new_width.
		// Sets the height of the Box to new_h.
		Box(const Vector3<T>& new_vertex, T new_length, T new_width, T new_height)
		{
			vertex = new_vertex;
			length = new_length;
			width = new_width;
			height = new_height;
		}

		// Double Vector3 constructor.
		// Sets the vertex of the Box to new_vertex.
		// Sets the dimensions of the Box to the given dimensions.
		Box(const Vector3<T>& new_vertex, const Vector3<T>& dimensions)
		{
			vertex = new_vertex;
			length = dimensions.x;
			width = dimensions.y;
			height = dimensions.z;
		}

		// Default copy constructor.
		Box(const Box& other) = default;

		// Default move constructor.
		Box(Box&& other) = default;

		// Constructs the Box from another type of Box.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Box(const Box<U>& other)
		{
			vertex.copyFrom(other.vertex);
			length = T(other.length);
			width = T(other.width);
			height = T(other.height);
		}

		// Default copy assignment operator.
		Box& operator = (const Box& other) = default;

		// Default move assignment operator.
		Box& operator = (Box&& other) = default;

		// Destructor.
		~Box() = default;

		// Sets all the values of the Box at once.
		// Sets the x component of the vertex of the Box to new_x.
		// Sets the y component of the vertex of the Box to new_y.
		// Sets the z component of the vertex of the Box to new_z.
		// Sets the length of the Box to new_length.
		// Sets the width of the Box to new_width.
		// Sets the height of the Box to new_height.
		void set(T new_x, T new_y, T new_z, T new_length, T new_width, T new_height)
		{
			vertex.set(new_x, new_y, new_z);
			length = new_length;
			width = new_width;
			height = new_height;
		}

		// Sets the x component of the vertex of the Box to new_x.
		// Sets the y component of the vertex of the Box to new_y.
		// Sets the z component of the vertex of the Box to new_z.
		void setVertex(T new_x, T new_y, T new_z)
		{
			vertex.set(new_x, new_y, new_z);
		}

		// Sets the vertex of the Box to new_vertex.
		void setVertex(const Vector3<T>& new_vertex)
		{
			vertex = new_vertex;
		}

		// Sets the length of the Box to new_length.
		// Sets the width of the Box to new_width.
		// Sets the height of the Box to new_height.
		void setDimensions(T new_length, T new_width, T new_height)
		{
			length = new_length;
			width = new_width;
			height = new_height;
		}

		// Sets the dimensions of the Box to the given dimensions.
		void setDimensions(const Vector3<T>& dimensions)
		{
			length = dimensions.x;
			width = dimensions.y;
			height = dimensions.z;
		}

		// Returns the surface area of the Box.
		constexpr float surfaceArea() const
		{
			return 2.0f * (width * length + height * length + height * width);
		}

		// Returns the volume of the Box.
		constexpr float volume() const
		{
			return length * width * height;
		}

		// Returns a std::string representation of the Box.
		std::string toString() const
		{
			return vertex.toString() + ", [" + std::to_string(length) + " x " + std::to_string(width) + " x " + std::to_string(height) + ']';
		}

		// Returns a std::wstring representation of the Box.
		std::wstring toWideString() const
		{
			return vertex.toWideString() + L", [" + std::to_wstring(length) + L" x " + std::to_wstring(width) + L" x " + std::to_wstring(height) + L']';
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Box<T>& A, const Box<T>& B)
	{
		return (A.vertex == B.vertex) && (A.length == B.length) && (A.width == B.width) && (A.height == B.height);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Box<T>& A, const Box<T>& B)
	{
		return (A.vertex != B.vertex) || (A.length != B.length) || (A.width != B.width) || (A.height != B.height);
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Box<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Box<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}