// JLibrary
// MiscStringFunctions.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Source file for MiscStringFunctions.hpp.

#ifndef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#endif // #ifndef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "MiscStringFunctions.hpp"

#include <algorithm>
using std::reverse;

#include <codecvt>
using std::codecvt_utf8_utf16;

#include <locale>
using std::wstring_convert;

#include <string>
using std::string;
using std::wstring;

namespace jlib
{
	wstring_convert<codecvt_utf8_utf16<wchar_t>> string_converter;

	wstring str_to_wstr(const string& str)
	{
		return string_converter.from_bytes(str);
	}

	string wstr_to_str(const wstring& wstr)
	{
		return string_converter.to_bytes(wstr);
	}

	string reverse_string(const string& str)
	{
		string newstr(str);
		reverse(newstr.begin(), newstr.end());
		return newstr;
	}

	wstring reverse_string(const wstring& wstr)
	{
		wstring newstr(wstr);
		reverse(newstr.begin(), newstr.end());
		return newstr;
	}

	string substring(const string& str, size_t pos_begin, size_t pos_end)
	{
		string newstr;
		newstr.resize(pos_end - pos_begin);

		for (size_t i = pos_begin; i < pos_end; ++i)
			newstr[i] = str[i];

		return newstr;
	}

	wstring substring(const wstring& str, size_t pos_begin, size_t pos_end)
	{
		wstring newstr;
		newstr.resize(pos_end - pos_begin);

		for (size_t i = pos_begin; i < pos_end; ++i)
			newstr[i] = str[i];

		return newstr;
	}
}