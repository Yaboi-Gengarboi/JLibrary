// JLibrary
// Color.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Header file for the Color class.

#pragma once

#include "IntegerTypedefs.hpp"

#include <array>
#include <initializer_list>
#include <iostream>

namespace jlib
{
	// Class that represents a color that can be drawn.
	class Color
	{
		public:

		static const u8 MAX = 0xff;

		enum : u32
		{
			Black     = 0x000000ff,
			White     = 0xffffffff,
			Red       = 0xff0000ff,
			Green     = 0x00ff00ff,
			Blue      = 0x0000ffff,
			Cyan      = 0x00ffffff,
			Magenta   = 0xff00ffff,
			Yellow    = 0xffff00ff,
			Silver    = 0xc0c0c0ff,
			Gray      = 0x808080ff,
			Maroon    = 0x800000ff,
			Olive     = 0x808000ff,
			DarkGreen = 0x008000ff,
			Purple    = 0x800080ff,
			Teal      = 0x008080ff,
			Navy      = 0x000080ff,
			Clear     = 0x00000000
		};

		u8 r, g, b, a;

		// Default constructor.
		// Sets each component of the Color to 0.
		Color();

		// Primary constructor.
		// Sets the red component of the Color to new_r.
		// Sets the green component of the Color to new_g.
		// Sets the blue component of the Color to new_b.
		// Sets the alpha component of the Color to new_a.
		Color(u8 new_r, u8 new_g, u8 new_b, u8 new_a = MAX);

		// Secondary constructor.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color(u32 color);

		// std::array constructor.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color(const std::array<u8, 4>& arr);

		// std::initializer_list constructor.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color(std::initializer_list<u8> list);

		// Default copy constructor.
		Color(const Color& other) = default;

		// Default move constructor.
		Color(Color&& other) = default;

		// unsigned int assignment operator.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color& operator = (u32 color);

		// std::array assignment operator.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color& operator = (const std::array<u8, 4>& arr);

		// std::initializer_list assignment operator.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color& operator = (std::initializer_list<u8> list);

		// Default copy assignment operator.
		Color& operator = (const Color& other) = default;

		// Default move assignment operator.
		Color& operator = (Color&& other) = default;

		// Destructor.
		~Color() = default;

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to new_r.
		// Sets the green component of the Color to new_g.
		// Sets the blue component of the Color to new_b.
		// Sets the alpha component of the Color to new_a.
		void set(u8 new_r, u8 new_g, u8 new_b, u8 new_a);

		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		void set(u32 color);

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		void set(const std::array<u8, 4>& arr);

		// Returns a 32-but unsigned integer representation of the Color.
		u32 toInt() const;

		// Returns a std::array copy of the Color's components.
		std::array<u8, 4> toArray() const;

		// Returns a std::string representation of the Color.
		std::string toString() const;

		// Returns a std::wstring representation of the Color.
		std::wstring toWideString() const;
	};

	// Returns the individual bytes of the unsigned int.
	std::array<u8, 4> to_bytes(u32 i);

	// Copies the color bytes into the given destination.
	void copy_color_data(const Color* src, u8* dst, std::size_t bytes);

	// Prints the Color to std::cout.
	void print(const Color& color);

	// Prints the Color to std::cout with a new line.
	void println(const Color& color);
}

// Overload of binary operator ==
bool operator == (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator !=
bool operator != (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator +
jlib::Color operator + (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator -
jlib::Color operator - (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator +=
jlib::Color& operator += (jlib::Color& A, const jlib::Color& B);

// Overload of binary operator -=
jlib::Color& operator -= (jlib::Color& A, const jlib::Color& B);

// Overload of binary operator *
jlib::Color operator * (const jlib::Color& A, float f);

// Overload of binary operator /
jlib::Color operator / (const jlib::Color& A, float f);

// Overload of binary operator *=
jlib::Color& operator *= (jlib::Color& A, float f);

// Overload of binary operator /=
jlib::Color& operator /= (jlib::Color& A, float f);

// Overload of std::ostream operator <<
std::ostream& operator << (std::ostream& os, const jlib::Color& A);

// Overload of std::wostream operator <<
std::wostream& operator << (std::wostream& os, const jlib::Color& A);