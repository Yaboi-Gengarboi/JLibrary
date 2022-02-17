// JLibrary
// Color.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-24 by Justyn Durnford
// Source file for the Color class.

#pragma warning( disable : 4244 ) 

#include "Color.hpp"
#include "Hexadecimal.hpp"

import MiscTemplateFunctions;

#include <array>
using std::array;

#include <bit>
using std::bit_cast;

#include <cstring>
using std::memcpy;

#include <initializer_list>
using std::initializer_list;

#include <iomanip>
using std::hex;

#include <ostream>
using std::ostream;
using std::wostream;

#include <string>
using std::string;
using std::wstring;
using std::to_string;
using std::to_wstring;

namespace jlib
{
	Color::Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	Color::Color(u8 new_r, u8 new_g, u8 new_b, u8 new_a)
	{
		r = new_r;
		g = new_g;
		b = new_b;
		a = new_a;
	}

	Color::Color(u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;
	}

	Color::Color(const array<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];
	}

	Color::Color(initializer_list<u8> list)
	{
		r = *(list.begin() + 0);
		g = *(list.begin() + 1);
		b = *(list.begin() + 2);
		a = *(list.begin() + 3);
	}

	Color& Color::operator = (u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;

		return *this;
	}

	Color& Color::operator = (const array<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];

		return *this;
	}

	Color& Color::operator = (initializer_list<u8> list)
	{
		r = *(list.begin() + 0);
		g = *(list.begin() + 1);
		b = *(list.begin() + 2);
		a = *(list.begin() + 3);

		return *this;
	}

	void Color::set(u8 new_r, u8 new_g, u8 new_b, u8 new_a)
	{
		r = new_r;
		g = new_g;
		b = new_b;
		a = new_a;
	}

	void Color::set(u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;
	}

	void Color::set(const array<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];
	}

	u32 Color::toInt() const
	{
		return (r << 24) | (g << 16) | (b << 8) | a;
	}

	array<u8, 4> Color::toArray() const
	{
		return array<u8, 4>{ r, g, b, a };
	}

	string Color::toString() const
	{
		string str;
		str.reserve(8);
		str += to_hex_str(r);
		str += to_hex_str(g);
		str += to_hex_str(b);
		str += to_hex_str(a);
		return str;
	}

	wstring Color::toWideString() const
	{
		wstring str;
		str.reserve(8);
		str += to_hex_wstr(r);
		str += to_hex_wstr(g);
		str += to_hex_wstr(b);
		str += to_hex_wstr(a);
		return str;
	}

	array<u8, 4> to_bytes(u32 i)
	{
		array<u8, 4> bytes;

		bytes[0] = (i & 0xff000000) >> 24;
		bytes[1] = (i & 0x00ff0000) >> 16;
		bytes[2] = (i & 0x0000ff00) >> 8;
		bytes[3] = (i & 0x000000ff) >> 0;

		return bytes;
	}

	string to_hex_str(u8 cbyte)
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

	wstring to_hex_wstr(u8 cbyte)
	{
		wstring hexstr(L"00");

		for (u8 i = 0; i < 2; ++i)
		{
			switch (cbyte % 16)
			{
				case 10: hexstr[1 - i] = L'a';                                    break;
				case 11: hexstr[1 - i] = L'b';                                    break;
				case 12: hexstr[1 - i] = L'c';                                    break;
				case 13: hexstr[1 - i] = L'd';                                    break;
				case 14: hexstr[1 - i] = L'e';                                    break;
				case 15: hexstr[1 - i] = L'f';                                    break;
				default: hexstr[1 - i] = static_cast<wchar_t>((cbyte % 16) + 48); break;
			}

			cbyte /= 16;
		}

		return hexstr;
	}

	void copy_color_data(const Color* src, u8* dst, size_t bytes)
	{
		const u8* ptr = bit_cast<const u8*>(src);
		memcpy(dst, ptr, bytes);
	}
}

bool operator == (const jlib::Color& A, const jlib::Color& B)
{
	return (A.r == B.r) && (A.g == B.g) && (A.b == B.b) && (A.a == B.a);
}

bool operator != (const jlib::Color& A, const jlib::Color& B)
{
	return (A.r != B.r) && (A.g != B.g) && (A.b != B.b) && (A.a != B.a);
}

jlib::Color operator + (const jlib::Color& A, const jlib::Color& B)
{
	int r = int(A.r) + int(B.r);
	int g = int(A.g) + int(B.g);
	int b = int(A.b) + int(B.b);
	int a = int(A.a) + int(B.a);

	jlib::clamp<int>(r, 0, 255);
	jlib::clamp<int>(g, 0, 255);
	jlib::clamp<int>(b, 0, 255);
	jlib::clamp<int>(a, 0, 255);

	return jlib::Color(r, g, b, a);
}

jlib::Color operator - (const jlib::Color& A, const jlib::Color& B)
{
	int r = int(A.r) - int(B.r);
	int g = int(A.g) - int(B.g);
	int b = int(A.b) - int(B.b);
	int a = int(A.a) - int(B.a);

	jlib::clamp<int>(r, 0, 255);
	jlib::clamp<int>(g, 0, 255);
	jlib::clamp<int>(b, 0, 255);
	jlib::clamp<int>(a, 0, 255);

	return jlib::Color(r, g, b, a);
}

jlib::Color& operator += (jlib::Color& A, const jlib::Color& B)
{
	int r = int(A.r) + int(B.r);
	int g = int(A.g) + int(B.g);
	int b = int(A.b) + int(B.b);
	int a = int(A.a) + int(B.a);

	jlib::clamp<int>(r, 0, 255);
	jlib::clamp<int>(g, 0, 255);
	jlib::clamp<int>(b, 0, 255);
	jlib::clamp<int>(a, 0, 255);

	A.r = static_cast<jlib::u8>(r);
	A.g = static_cast<jlib::u8>(g);
	A.b = static_cast<jlib::u8>(b);
	A.a = static_cast<jlib::u8>(a);

	return A;
}

jlib::Color& operator -= (jlib::Color& A, const jlib::Color& B)
{
	int r = int(A.r) - int(B.r);
	int g = int(A.g) - int(B.g);
	int b = int(A.b) - int(B.b);
	int a = int(A.a) - int(B.a);

	jlib::clamp<int>(r, 0, 255);
	jlib::clamp<int>(g, 0, 255);
	jlib::clamp<int>(b, 0, 255);
	jlib::clamp<int>(a, 0, 255);

	A.r = static_cast<jlib::u8>(r);
	A.g = static_cast<jlib::u8>(g);
	A.b = static_cast<jlib::u8>(b);
	A.a = static_cast<jlib::u8>(a);

	return A;
}

jlib::Color operator * (const jlib::Color& A, float f)
{
	float r = jlib::clamp_of(A.r * f, 0.0f, 255.0f);
	float g = jlib::clamp_of(A.g * f, 0.0f, 255.0f);
	float b = jlib::clamp_of(A.b * f, 0.0f, 255.0f);
	float a = jlib::clamp_of(A.a * f, 0.0f, 255.0f);

	return jlib::Color(r, g, b, a);
}

jlib::Color operator / (const jlib::Color& A, float f)
{
	float r = jlib::clamp_of(A.r / f, 0.0f, 255.0f);
	float g = jlib::clamp_of(A.g / f, 0.0f, 255.0f);
	float b = jlib::clamp_of(A.b / f, 0.0f, 255.0f);
	float a = jlib::clamp_of(A.a / f, 0.0f, 255.0f);

	return jlib::Color(r, g, b, a);
}

jlib::Color& operator *= (jlib::Color& A, float f)
{
	A.r = static_cast<jlib::u8>(jlib::clamp_of(A.r * f, 0.0f, 255.0f));
	A.g = static_cast<jlib::u8>(jlib::clamp_of(A.g * f, 0.0f, 255.0f));
	A.b = static_cast<jlib::u8>(jlib::clamp_of(A.b * f, 0.0f, 255.0f));
	A.a = static_cast<jlib::u8>(jlib::clamp_of(A.a * f, 0.0f, 255.0f));

	return A;
}

jlib::Color& operator /= (jlib::Color& A, float f)
{
	A.r = static_cast<jlib::u8>(jlib::clamp_of(A.r / f, 0.0f, 255.0f));
	A.g = static_cast<jlib::u8>(jlib::clamp_of(A.g / f, 0.0f, 255.0f));
	A.b = static_cast<jlib::u8>(jlib::clamp_of(A.b / f, 0.0f, 255.0f));
	A.a = static_cast<jlib::u8>(jlib::clamp_of(A.a / f, 0.0f, 255.0f));

	return A;
}

ostream& operator << (ostream& os, const jlib::Color& A)
{
	os << A.toString();
	return os;
}

wostream& operator << (wostream& wos, const jlib::Color& A)
{
	wos << A.toWideString();
	return wos;
}