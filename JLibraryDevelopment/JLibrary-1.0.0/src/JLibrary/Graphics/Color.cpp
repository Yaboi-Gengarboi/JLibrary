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
// Last modified on 2021-07-07 by Justyn Durnford
// Source file for the Color class.

#include <JLibrary/Graphics/Color.hpp>
using namespace jlib;

// <array>
using std::array;

#include <cstddef>
using std::size_t;
 
// <initializer_list>
using std::initializer_list;
   
// <string>
using std::string;
using std::wstring;
using std::u32string;

Color::Color()
{
	data = { 0, 0, 0, 0 };
}

Color::Color(u8 R, u8 G, u8 B, u8 A)
{
	data = { R, G, B, A };
}

Color::Color(const array<u8, 4>& arr)
{
	data = arr;
}

Color::Color(initializer_list<u8> list)
{
	data[0] = *(list.begin() + 0);
	data[1] = *(list.begin() + 1);
	data[2] = *(list.begin() + 2);
	data[3] = *(list.begin() + 3);
}

Color::Color(u32 color)
{
	data[0] = (color & 0xff000000) >> 24;
	data[1] = (color & 0x00ff0000) >> 16;
	data[2] = (color & 0x0000ff00) >> 8;
	data[3] = (color & 0x000000ff) >> 0;
}

Color& Color::operator = (const array<u8, 4>& arr)
{
	data = arr;
	return *this;
}

Color& Color::operator = (initializer_list<u8> list)
{
	data[0] = *(list.begin() + 0);
	data[1] = *(list.begin() + 1);
	data[2] = *(list.begin() + 2);
	data[3] = *(list.begin() + 3);

	return *this;
}

Color& Color::operator = (u32 color)
{
	data[0] = (color & 0xff000000) >> 24;
	data[1] = (color & 0x00ff0000) >> 16;
	data[2] = (color & 0x0000ff00) >> 8;
	data[3] = (color & 0x000000ff) >> 0;

	return *this;
}

u8& Color::r()
{
	return data[0];
}

const u8& Color::r() const
{
	return data[0];
}

u8& Color::g()
{
	return data[1];
}

const u8& Color::g() const
{
	return data[1];
}

u8& Color::b()
{
	return data[2];
}

const u8& Color::b() const
{
	return data[2];
}

u8& Color::a()
{
	return data[3];
}

const u8& Color::a() const
{
	return data[3];
}

void Color::set(u8 R, u8 G, u8 B, u8 A)
{
	data = { R, G, B, A };
}

void Color::set(const array<u8, 4>& arr)
{
	data = arr;
}

void Color::set(u32 color)
{
	data[0] = (color & 0xff000000) >> 24;
	data[1] = (color & 0x00ff0000) >> 16;
	data[2] = (color & 0x0000ff00) >> 8;
	data[3] = (color & 0x000000ff) >> 0;
}

u32 Color::toInt() const
{
	return (r() << 24) | (g() << 16) | (b() << 8) | a();
}

array<u8, 4> Color::toArray() const
{
	return data;
}

string Color::toString() const
{
	string str;
	str.reserve(8);
	str += to_hex_str(r());
	str += to_hex_str(g());
	str += to_hex_str(b());
	str += to_hex_str(a());
	return str;
}

wstring Color::toWideString() const
{
	return str_to_wstr(toString());
}

u32string Color::toU32String() const
{
	return str_to_u32str(toString());
}

u8& Color::operator [] (size_t index)
{
	return data[index];
}

const u8& Color::operator [] (size_t index) const
{
	return data[index];
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

array<u8, 4> jlib::to_bytes(u32 i)
{
	array<u8, 4> bytes;
	
	bytes[0] = (i & 0xff000000) >> 24;
	bytes[1] = (i & 0x00ff0000) >> 16;
	bytes[2] = (i & 0x0000ff00) >> 8;
	bytes[3] = (i & 0x000000ff) >> 0;

	return bytes;
}

string jlib::to_hex_str(u8 cbyte)
{
	string hexstr("00");

	for (u8 i = 0; i < 2; ++i)
	{
		switch (cbyte % 16)
		{
			case 10: hexstr[1 - i] = 'a';               break;
			case 11: hexstr[1 - i] = 'b';               break;
			case 12: hexstr[1 - i] = 'c';               break;
			case 13: hexstr[1 - i] = 'd';               break;
			case 14: hexstr[1 - i] = 'e';               break;
			case 15: hexstr[1 - i] = 'f';               break;
			default: hexstr[1 - i] = (cbyte % 16) + 48; break;
		}

		cbyte /= 16;
	}

	return hexstr;
}

wstring jlib::to_hex_wstr(u8 cbyte)
{
	return str_to_wstr(to_hex_str(cbyte));
}

u32string jlib::to_hex_u32str(u8 cbyte)
{
	return str_to_u32str(to_hex_str(cbyte));
}

bool operator == (const Color& A, const Color& B)
{
	return A.data == B.data;
}

bool operator != (const Color& A, const Color& B)
{
	return A.data != B.data;
}