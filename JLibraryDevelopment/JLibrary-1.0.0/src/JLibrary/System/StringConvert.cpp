// JLibraryDevelopment
// StringConvert.cpp
// Created on 2021-07-03 by Justyn Durnford
// Last modified on 2021-07-03 by Justyn Durnford
// Source file for functions that handle conversions
// between different types of strings.

#include <JLibrary/System/StringConvert.hpp>

// <string>
using std::string;
using std::u32string;
using std::wstring;

wstring jlib::str_to_wstr(const string& str)
{
	wstring newstr;
	newstr.resize(str.size());

	for (size_t i(0); i < str.size(); ++i)
		newstr[i] = static_cast<wchar_t>(str[i]);
}

u32string jlib::str_to_u32str(const string& str)
{
	u32string newstr;
	newstr.resize(str.size());

	for (size_t i(0); i < str.size(); ++i)
		newstr[i] = static_cast<char32_t>(str[i]);
}