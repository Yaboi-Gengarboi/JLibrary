// JLibraryDevelopment
// Color.cpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-05-25 by Justyn Durnford
// Source file for the Color class.

#include <JLibrary/Graphics/Color.hpp>
using namespace std;
using namespace jl;

string jl::to_hex_str(unsigned char byte)
{
	string hexstr("00");

	for (unsigned char i = 0u; i < 2u; ++i)
	{
		switch (byte % 16u)
		{
			case 10u: hexstr[1u - i] = 'a';                break;
			case 11u: hexstr[1u - i] = 'b';                break;
			case 12u: hexstr[1u - i] = 'c';                break;
			case 13u: hexstr[1u - i] = 'd';                break;
			case 14u: hexstr[1u - i] = 'e';                break;
			case 15u: hexstr[1u - i] = 'f';                break;
			default:  hexstr[1u - i] = (byte % 16u) + 48u; break;
		}

		byte /= 16u;
	}

	return hexstr;
}

wstring jl::to_hex_wstr(unsigned char byte)
{
	wstring hexstr(L"00");

	for (unsigned char i = 0u; i < 2u; ++i)
	{
		switch (byte % 16u)
		{
			case 10u: hexstr[1u - i] = L'a';                                     break;
			case 11u: hexstr[1u - i] = L'b';                                     break;
			case 12u: hexstr[1u - i] = L'c';                                     break;
			case 13u: hexstr[1u - i] = L'd';                                     break;
			case 14u: hexstr[1u - i] = L'e';                                     break;
			case 15u: hexstr[1u - i] = L'f';                                     break;
			default:  hexstr[1u - i] = static_cast<wchar_t>((byte % 16u) + 48u); break;
		}

		byte /= 16u;
	}

	return hexstr;
}

Color::Color()
{
	red = 0u;
	green = 0u;
	blue = 0u;
	alpha = 0u;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
	red = r;
	green = g;
	blue = b;
	alpha = MAX;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

void Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

string Color::toString() const
{
	string str;
	str.reserve(8ull);
	str += to_hex_str(red);
	str += to_hex_str(green);
	str += to_hex_str(blue);
	str += to_hex_str(alpha);
	return str;
}

wstring Color::toWString() const
{
	wstring wstr;
	wstr.reserve(8ull);
	wstr += to_hex_wstr(red);
	wstr += to_hex_wstr(green);
	wstr += to_hex_wstr(blue);
	wstr += to_hex_wstr(alpha);
	return wstr;
}

bool operator == (const Color& A, const Color& B)
{
	return (A.red == B.red) && (A.green == B.green) && (A.blue == B.blue) && (A.alpha == B.alpha);
}

bool operator != (const Color& A, const Color& B)
{
	return (A.red != B.red) || (A.green != B.green) || (A.blue != B.blue) || (A.alpha != B.alpha);
}