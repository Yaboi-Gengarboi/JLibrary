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
// Color.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the Color class.

#pragma once

#include <JLibrary/System/Integer.hpp>
#include <JLibrary/Utility/StringConvert.hpp>
#include <array>
#include <initializer_list>

namespace jlib
{
	class Color
	{
		public:

		const static u8 MAX = 255u;

		std::array<u8, 4> data;

		// Default constructor.
		// Sets each component of the Color to 0.
		Color();

		// u8 constructor.
		// Sets the red component of the Color to R.
		// Sets the green component of the Color to G.
		// Sets the blue component of the Color to B.
		// Sets the alpha component of the Color to A.
		Color(u8 R, u8 G, u8 B, u8 A = MAX);

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

		// unsigned int constructor.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color(u32 color);

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

		// unsigned int assignment operator.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color& operator = (u32 color);

		// Returns the red component of the Color.
		u8& r();

		// Returns the red component of the Color.
		const u8& r() const;

		// Returns the green component of the Color.
		u8& g();

		// Returns the green component of the Color.
		const u8& g() const;

		// Returns the blue component of the Color.
		u8& b();

		// Returns the blue component of the Color.
		const u8& b() const;

		// Returns the alpha component of the Color.
		u8& a();

		// Returns the alpha component of the Color.
		const u8& a() const;

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to R.
		// Sets the green component of the Color to G.
		// Sets the blue component of the Color to B.
		// Sets the alpha component of the Color to A.
		void set(u8 R, u8 G, u8 B, u8 A);

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		void set(const std::array<u8, 4>& arr);

		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		void set(u32 color);

		// Returns a 32-but unsigned integer representation of the Color.
		u32 toInt() const;

		// Returns a std::array copy of the Color's components.
		std::array<u8, 4> toArray() const;

		// Returns a std::string representation of the Color.
		std::string toString() const;

		// Returns a std::wstring representation of the Color.
		std::wstring toWideString() const;

		// Returns a std::u32string representation of the Color.
		std::u32string toU32String() const;

		// Returns the element at the given index.
		u8& operator [] (std::size_t index);

		// Returns the element at the given index.
		const u8& operator [] (std::size_t index) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		// Define common colors.
		// More RGB color combinations can be found at https://www.rapidtables.com/web/color/RGB_Color.html
		const static Color Black;
		const static Color White;
		const static Color Red;
		const static Color Green;
		const static Color Blue;
		const static Color Cyan;
		const static Color Magenta;
		const static Color Yellow;
		const static Color Silver;
		const static Color Gray;
		const static Color Maroon;
		const static Color Olive;
		const static Color Dark_Green;
		const static Color Purple;
		const static Color Teal;
		const static Color Navy;
		const static Color Transparent;
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Returns the individual bytes of the unsigned int.
	std::array<u8, 4> to_bytes(u32 i);

	// Returns a hexadecimal std::string representation of the byte.
	std::string to_hex_str(u8 cbyte);

	// Returns a hexadecimal std::wstring representation of the byte.
	std::wstring to_hex_wstr(u8 cbyte);

	// Returns a hexadecimal std::u32string representation of the byte.
	std::u32string to_hex_u32str(u8 cbyte);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
bool operator == (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator !=
bool operator != (const jlib::Color& A, const jlib::Color& B);