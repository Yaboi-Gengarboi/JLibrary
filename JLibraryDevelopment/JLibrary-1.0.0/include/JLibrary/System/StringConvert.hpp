// JLibraryDevelopment
// StringConvert.hpp
// Created on 2021-07-03 by Justyn Durnford
// Last modified on 2021-07-06 by Justyn Durnford
// Header file for functions that handle conversions
// between different types of strings.

#pragma once

#include <string>

namespace jlib
{
	// Converts a std::string to a std::wstring.
	std::wstring str_to_wstr(const std::string& str);

	// Converts a std::string to a std::u32string.
	std::u32string str_to_u32str(const std::string& str);
}