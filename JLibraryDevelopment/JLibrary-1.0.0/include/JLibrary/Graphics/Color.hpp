// JLibraryDevelopment
// Color.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-05-25 by Justyn Durnford
// Header file for the Color class.

#pragma once

#include <string>

namespace jl
{
	// Returns a hexadecimal std::string representation of the byte.
	std::string to_hex_str(unsigned char byte);

	// Returns a hexadecimal std::wstring representation of the byte.
	std::wstring to_hex_wstr(unsigned char byte);

	class Color
	{
		public:

		const static unsigned char MAX = 255u;

		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;

		// Default constructor.
		// Sets each component of the Color to 0.
		Color();

		// 3-unsigned char constructor.
		// Sets the red component of the Color to r.
		// Sets the green component of the Color to g.
		// Sets the blue component of the Color to b.
		// Sets the alpha component of the Color to 255u.
		Color(unsigned char r, unsigned char g, unsigned char b);

		// 4-unsigned char constructor.
		// Sets the red component of the Color to r.
		// Sets the green component of the Color to g.
		// Sets the blue component of the Color to b.
		// Sets the alpha component of the Color to a.
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		// Copy constructor.
		Color(const Color& other) = default;

		// Move constructor.
		Color(Color&& other) = default;

		// Copy assignment operator.
		Color& operator = (const Color& other) = default;

		// Move assignment operator.
		Color& operator = (Color && other) = default;

		// Destructor.
		~Color() = default;

		// Sets the red component of the Color to r.
		// Sets the green component of the Color to g.
		// Sets the blue component of the Color to b.
		// Sets the alpha component of the Color to a.
		void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		// Returns a std::string representation of the Color.
		std::string toString() const;

		// Returns a std::wstring representation of the Color.
		std::wstring toWString() const;
	};
}

// Overload of binary operator ==
bool operator == (const jl::Color& A, const jl::Color& B);

// Overload of binary operator !=
bool operator != (const jl::Color& A, const jl::Color& B);