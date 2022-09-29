// JLibrary
// Hexadecimal.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-07-02 by Justyn Durnford
// Header file defining several hexadecimal-related functions.

#pragma once

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

namespace jlib
{
	// Returns a hexadecimal std::string representation of the integer.
	template <std::integral T>
	std::string to_hex_string(T number, bool prepend = false, bool fill = false, bool uppercase = false)
	{
		std::stringstream str_stream;

		if (prepend)
			str_stream << "0x";

		if (fill)
			str_stream << std::setfill('0') << std::setw(sizeof(T) * 2);

		str_stream << std::hex << number;
		std::string str(str_stream.str());

		if (uppercase)
			std::transform(str.begin(), str.end(), str.begin(), std::toupper);

		return str;
	}

	// Returns a hexadecimal std::wstring representation of the integer.
	template <std::integral T>
	std::wstring to_hex_wstring(T number, bool prepend = false, bool fill = false, bool uppercase = false)
	{
		std::wstringstream wstr_stream;

		if (prepend)
			wstr_stream << L"0x";

		if (fill)
			wstr_stream << std::setfill(L'0') << std::setw(sizeof(T) * 2);

		wstr_stream << std::hex << number;
		return wstr_stream.str();
	}

	// Returns a hexadecimal std::string representation of the byte.
	std::string to_hex_string(unsigned char byte, bool prepend = false, bool uppercase = false);

	// Returns a hexadecimal std::wstring representation of the byte.
	std::wstring to_hex_wstring(unsigned char byte, bool prepend = false, bool uppercase = false);

	// Returns a hexadecimal std::string representation of the float.
	std::string to_hex_string(float number, bool prepend = false, bool fill = false, bool uppercase = false);

	// Returns a hexadecimal std::wstring representation of the float.
	std::wstring to_hex_wstring(float number, bool prepend = false, bool fill = false, bool uppercase = false);

	// Returns a hexadecimal std::string of the memory pointed to.
	std::string to_hex_string(const void* ptr, std::size_t byte_count, bool uppercase = false);

	// Returns a hexadecimal std::wstring of the memory pointed to.
	std::wstring to_hex_wstring(const void* ptr, std::size_t byte_count, bool uppercase = false);

	// Returns a float that is represented by the std::string.
	float hex_to_float(const std::string& str);
}