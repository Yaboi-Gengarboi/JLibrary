// JLibrary
// MiscStringFunctions.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file defining several string-related functions.

#pragma once

#include <string>

namespace jlib
{
	// 
	std::wstring str_to_wstr(const std::string& str);

	// 
	std::string wstr_to_str(const std::wstring& wstr);

	//
	std::string reverse_string(const std::string& str);

	// 
	std::wstring reverse_string(const std::wstring& wstr);

	// 
	std::string substring(const std::string& str, std::size_t pos_begin, std::size_t pos_end);

	// 
	std::wstring substring(const std::wstring& str, std::size_t pos_begin, std::size_t pos_end);
}