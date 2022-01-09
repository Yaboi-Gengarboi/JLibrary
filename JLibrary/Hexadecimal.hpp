// JLibrary
// Hexadecimal.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file defining several hexadecimal-related functions.

#pragma once

#include <iomanip>
#include <sstream>
#include <string>

namespace jlib
{
	// Returns a hexadecimal std::string representation of the integer.
	template <std::integral T>
	std::string to_hex_string(T number, bool prepend = false, bool fill = false)
	{
		std::stringstream str_stream;

		if (prepend)
			str_stream << "0x";

		if (fill)
			str_stream << std::setfill('0') << std::setw(sizeof(T) * 2);

		str_stream << std::hex << number;
		return str_stream.str();
	}

	// Returns a hexadecimal std::wstring representation of the integer.
	template <std::integral T>
	std::wstring to_hex_wstring(T number, bool prepend = false, bool fill = false)
	{
		std::wstringstream wstr_stream;

		if (prepend)
			wstr_stream << L"0x";

		if (fill)
			wstr_stream << std::setfill(L'0') << std::setw(sizeof(T) * 2);

		wstr_stream << std::hex << number;
		return wstr_stream.str();
	}

	// Returns a hexadecimal std::string representation of the float.
	std::string to_hex_string(float number, bool prepend = false, bool fill = false);

	// Returns a hexadecimal std::wstring representation of the float.
	std::wstring to_hex_wstring(float number, bool prepend = false, bool fill = false);
}