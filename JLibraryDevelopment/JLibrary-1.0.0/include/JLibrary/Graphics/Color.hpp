// JLibraryDevelopment
// Color.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-06-11 by Justyn Durnford
// Header file for the Color class.

#pragma once

#include <string>

namespace jl
{
	class Color
	{
		public:

		const static unsigned char MAX = 255u;

		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

		// Default constructor.
		// Sets each component of the Color to 0.
		Color();

		// 3-unsigned char constructor.
		// Sets the red component of the Color to R.
		// Sets the green component of the Color to G.
		// Sets the blue component of the Color to B.
		// Sets the alpha component of the Color to 255u.
		Color(unsigned char R, unsigned char G, unsigned char B);

		// 4-unsigned char constructor.
		// Sets the red component of the Color to R.
		// Sets the green component of the Color to G.
		// Sets the blue component of the Color to B.
		// Sets the alpha component of the Color to A.
		Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

		// unsigned int constructor.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color(unsigned int color);

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

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to R.
		// Sets the green component of the Color to G.
		// Sets the blue component of the Color to B.
		// Sets the alpha component of the Color to A.
		void set(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		void set(unsigned int color);

		// Returns a 32-but unsigned integer representation of the Color.
		unsigned int toInt() const;

		// Returns a std::string representation of the Color.
		std::string toString() const;

		// Returns a std::wstring representation of the Color.
		std::wstring toWString() const;

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

	// Returns a hexadecimal std::string representation of the byte.
	std::string to_hex_str(unsigned char byte);

	// Returns a hexadecimal std::wstring representation of the byte.
	std::wstring to_hex_wstr(unsigned char byte);
}

// Overload of binary operator ==
bool operator == (const jl::Color& A, const jl::Color& B);

// Overload of binary operator !=
bool operator != (const jl::Color& A, const jl::Color& B);