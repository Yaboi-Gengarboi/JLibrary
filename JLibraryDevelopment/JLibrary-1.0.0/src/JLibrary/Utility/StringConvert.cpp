// JLibraryDevelopment
// StringConvert.cpp
// Created on 2021-07-03 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Source file for functions that handle conversions
// between different types of strings.

#include <JLibrary/Utility/StringConvert.hpp>

// <string>
using std::size_t;
using std::string;
using std::u32string;
using std::wstring;

wstring jlib::str_to_wstr(const string& str)
{
	wstring newstr;
	const size_t s(str.size());
	newstr.resize(s);

	for (size_t i(0); i < s; ++i)
		newstr[i] = static_cast<wchar_t>(str[i]);

	return newstr;
}

u32string jlib::str_to_u32str(const string& str)
{
	u32string newstr;
	const size_t s(str.size());
	newstr.resize(s);

	for (size_t i(0); i < s; ++i)
		newstr[i] = static_cast<char32_t>(str[i]);

	return newstr;
}

u32string jlib::wstr_to_u32str(const wstring& wstr)
{
	u32string newstr;
	const size_t s(wstr.size());
	newstr.resize(s);

	for (size_t i(0); i < s; ++i)
		newstr[i] = static_cast<char32_t>(wstr[i]);

	return newstr;
}