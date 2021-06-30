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
// Color.cpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-06-29 by Justyn Durnford
// Source file for the Color class.

#include <JLibrary/Graphics/Color.hpp>
using namespace std;
using namespace jlib;

Color::Color()
{
	r = 0u;
	g = 0u;
	b = 0u;
	a = 0u;
}

Color::Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A = MAX)
{
	r = R;
	g = G;
	b = B;
	a = A;
}

Color::Color(unsigned int color)
{
	r = (color & 0xff000000) >> 24;
	g = (color & 0x00ff0000) >> 16;
	b = (color & 0x0000ff00) >> 8;
	a = (color & 0x000000ff) >> 0;
}

void Color::set(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
	r = R;
	g = G;
	b = B;
	a = A;
}

void Color::set(unsigned int color)
{
	r = (color & 0xff000000) >> 24;
	g = (color & 0x00ff0000) >> 16;
	b = (color & 0x0000ff00) >> 8;
	a = (color & 0x000000ff) >> 0;
}

unsigned int Color::toInt() const
{
	return (r << 24) | (g << 16) | (b << 8) | a;
}

string Color::toString() const
{
	string str;
	str.reserve(8u);
	str += to_hex_str(r);
	str += to_hex_str(g);
	str += to_hex_str(b);
	str += to_hex_str(a);
	return str;
}

wstring Color::toWideString() const
{
	wstring wstr;
	wstr.reserve(8u);
	wstr += to_hex_wstr(r);
	wstr += to_hex_wstr(g);
	wstr += to_hex_wstr(b);
	wstr += to_hex_wstr(a);
	return wstr;
}

const Color Color::Black(0x00, 0x00, 0x00);
const Color Color::White(0xff, 0xff, 0xff);
const Color Color::Red(0xff, 0x00, 0x00);
const Color Color::Green(0x00, 0xff, 0x00);
const Color Color::Blue(0x00, 0x00, 0xff);
const Color Color::Cyan(0x00, 0xff, 0xff);
const Color Color::Magenta(0xff, 0x00, 0xff);
const Color Color::Yellow(0xff, 0xff, 0x00);
const Color Color::Silver(0xc0, 0xc0, 0xc0);
const Color Color::Gray(0x80, 0x80, 0x80);
const Color Color::Maroon(0x80, 0x00, 0x00);
const Color Color::Olive(0x80, 0x80, 0x00);
const Color Color::Dark_Green(0x00, 0x80, 0x00);
const Color Color::Purple(0x80, 0x00, 0x80);
const Color Color::Teal(0x00, 0x80, 0x80);
const Color Color::Navy(0x00, 0x00, 0x80);
const Color Color::Transparent(0x00, 0x00, 0x00, 0x00);

unsigned char* jlib::to_bytes(unsigned int i)
{
	unsigned char* bytes = new unsigned char[4];
	
	bytes[0] = (i & 0xff000000) >> 24;
	bytes[1] = (i & 0x00ff0000) >> 16;
	bytes[2] = (i & 0x0000ff00) >> 8;
	bytes[3] = (i & 0x000000ff) >> 0;

	return bytes;
}

string jlib::to_hex_str(unsigned char byte)
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

wstring jlib::to_hex_wstr(unsigned char byte)
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

bool operator == (const Color& A, const Color& B)
{
	return (A.r == B.r) && (A.g == B.g) && (A.b == B.b) && (A.a == B.a);
}

bool operator != (const Color& A, const Color& B)
{
	return (A.r != B.r) || (A.g != B.g) || (A.b != B.b) || (A.a != B.a);
}