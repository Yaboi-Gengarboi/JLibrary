// JLibrary
// Hexadecimal.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Source file for Hexadecimal.hpp.

#include "Hexadecimal.hpp"

#include <bit>
using std::bit_cast;

#include <string>
using std::string;
using std::wstring;

namespace jlib
{
	string to_hex_string(float number, bool prepend, bool fill)
	{
		return to_hex_string<int>(bit_cast<int>(number), prepend, fill);
	}

	wstring to_hex_wstring(float number, bool prepend, bool fill)
	{
		return to_hex_wstring<int>(bit_cast<int>(number), prepend, fill);
	}
}