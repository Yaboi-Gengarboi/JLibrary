// JLibrary
// String.cpp
// Created on 2022-05-01 by Justyn Durnford
// Last modified on 2022-05-10 by Justyn Durnford
// Source file for the String class.

#ifndef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#endif // #ifndef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "String.hpp"
using jlib::String;
using jlib::str_to_wstr;

#include <codecvt>
using std::codecvt_utf8_utf16;

#include <compare>
using std::strong_ordering;

#include <cstddef>
using std::size_t;

#include <initializer_list>
using std::initializer_list;

#include <iostream>
using std::wcout;
using std::istream;
using std::ostream;
using std::wistream;
using std::wostream;

#include <locale>
using std::wstring_convert;

#include <string>
using std::string;
using std::wstring;
using std::to_wstring;

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

	wstring reverse_wstring(const wstring& wstr)
	{
		wstring newstr(wstr);
		reverse(newstr.begin(), newstr.end());
		return newstr;
	}

	string substring(const string& str, size_t pos_begin, size_t pos_end)
	{
		return str.substr(pos_begin, pos_end - pos_begin);
	}

	wstring substring(const wstring& wstr, size_t pos_begin, size_t pos_end)
	{
		return wstr.substr(pos_begin, pos_end - pos_begin);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	String::String(char c, size_t count)
	{
		_wstr = str_to_wstr(string(count, c));
	}

	String::String(wchar_t wc, size_t count)
	{
		_wstr.resize(count, wc);
	}

	String::String(const string& str, size_t pos)
	{
		_wstr = str_to_wstr(str.substr(pos));
	}

	String::String(const wstring& wstr, size_t pos)
	{
		_wstr = wstr.substr(pos);
	}

	String::String(string::const_iterator begin, string::const_iterator end)
	{
		_wstr = str_to_wstr(string(begin, end));
	}

	String::String(wstring::const_iterator begin, wstring::const_iterator end)
	{
		_wstr = wstring(begin, end);
	}

	String::String(initializer_list<char> char_list)
	{
		_wstr = str_to_wstr(string(char_list));
	}

	String::String(initializer_list<wchar_t> wchar_list)
	{
		_wstr = wchar_list;
	}

	String& String::operator = (const string& str)
	{
		_wstr = str_to_wstr(str);
		return *this;
	}

	String& String::operator = (const wstring& wstr)
	{
		_wstr = wstr;
		return *this;
	}

	String& String::assign(char c, size_t count)
	{
		_wstr = str_to_wstr(string(count, c));
		return *this;
	}

	String& String::assign(wchar_t wc, size_t count)
	{
		_wstr.assign(count, wc);
		return *this;
	}

	String& String::assign(const string& str, size_t pos, size_t count)
	{
		_wstr = str_to_wstr(str.substr(pos, count));
		return *this;
	}

	String& String::assign(const wstring& wstr, size_t pos, size_t count)
	{
		_wstr = wstr.substr(pos, count);
		return *this;
	}

	String& String::assign(string::const_iterator begin, string::const_iterator end)
	{
		_wstr = str_to_wstr(string(begin, end));
		return *this;
	}

	String& String::assign(wstring::const_iterator begin, wstring::const_iterator end)
	{
		_wstr = wstring(begin, end);
		return *this;
	}

	String& String::assign(initializer_list<char> char_list)
	{
		_wstr = str_to_wstr(string(char_list));
		return *this;
	}

	String& String::assign(initializer_list<wchar_t> wchar_list)
	{
		_wstr = wchar_list;
		return *this;
	}

	constexpr wchar_t& String::at(size_t index)
	{
		return _wstr.at(index);
	}

	constexpr const wchar_t& String::at(size_t index) const
	{
		return _wstr.at(index);
	}

	constexpr wchar_t& String::operator [] (size_t index)
	{
		return _wstr[index];
	}

	constexpr const wchar_t& String::operator [] (size_t index) const
	{
		return _wstr[index];
	}

	constexpr wchar_t& String::front()
	{
		return _wstr.front();
	}

	constexpr const wchar_t& String::front() const
	{
		return _wstr.front();
	}

	constexpr wchar_t& String::back()
	{
		return _wstr.back();
	}

	constexpr const wchar_t& String::back() const
	{
		return _wstr.back();
	}

	constexpr wchar_t* String::data()
	{
		return _wstr.data();
	}

	constexpr const wchar_t* String::data() const
	{
		return _wstr.data();
	}

	constexpr wchar_t* String::data_end()
	{
		return _wstr.data() + _wstr.size();
	}

	constexpr const wchar_t* String::data_end() const
	{
		return _wstr.data() + _wstr.size();
	}

	constexpr const wchar_t* String::c_str() const
	{
		return _wstr.c_str();
	}

	constexpr String::operator std::wstring_view() const noexcept
	{
		return _wstr.operator std::basic_string_view<wchar_t, std::char_traits<wchar_t>>();
	}

	constexpr String::iterator String::begin() noexcept
	{
		return _wstr.begin();
	}

	constexpr String::const_iterator String::begin() const noexcept
	{
		return _wstr.cbegin();
	}

	constexpr String::const_iterator String::cbegin() const noexcept
	{
		return _wstr.cbegin();
	}

	constexpr String::iterator String::end() noexcept
	{
		return _wstr.end();
	}

	constexpr String::const_iterator String::end() const noexcept
	{
		return _wstr.cend();
	}

	constexpr String::const_iterator String::cend() const noexcept
	{
		return _wstr.cend();
	}

	constexpr String::reverse_iterator String::rbegin() noexcept
	{
		return _wstr.rbegin();
	}

	constexpr String::const_reverse_iterator String::rbegin() const noexcept
	{
		return _wstr.crbegin();
	}

	constexpr String::const_reverse_iterator String::crbegin() const noexcept
	{
		return _wstr.crbegin();
	}

	constexpr String::reverse_iterator String::rend() noexcept
	{
		return _wstr.rend();
	}

	constexpr String::const_reverse_iterator String::rend() const noexcept
	{
		return _wstr.crend();
	}

	constexpr String::const_reverse_iterator String::crend() const noexcept
	{
		return _wstr.crend();
	}

	constexpr bool String::is_empty() const noexcept
	{
		return _wstr.size() == 0;
	}

	constexpr size_t String::size() const noexcept
	{
		return _wstr.size();
	}

	constexpr size_t String::length() const noexcept
	{
		return _wstr.length();
	}

	constexpr size_t String::max_size() const noexcept
	{
		return _wstr.max_size();
	}

	constexpr void String::reserve(size_t new_cap)
	{
		_wstr.reserve(new_cap);
	}

	constexpr size_t String::capacity() const noexcept
	{
		return _wstr.capacity();
	}

	constexpr void String::shrink_to_fit()
	{
		_wstr.shrink_to_fit();
	}

	constexpr void String::clear() noexcept
	{
		_wstr.clear();
	}

	String& String::insert(char c, size_t index, size_t count)
	{
		_wstr.insert(index, str_to_wstr(string(count, c)));
		return *this;
	}

	String& String::insert(wchar_t wc, size_t index, size_t count)
	{
		_wstr.insert(index, wstring(count, wc));
		return *this;
	}

	String& String::insert(const string& str, size_t index)
	{
		_wstr.insert(index, str_to_wstr(str));
		return *this;
	}

	String& String::insert(const wstring& wstr, size_t index)
	{
		_wstr.insert(index, wstr);
		return *this;
	}

	String& String::insert(initializer_list<char> char_list, size_t index)
	{
		_wstr.insert(index, str_to_wstr(string(char_list)));
		return *this;
	}

	String& String::insert(initializer_list<wchar_t> wchar_list, size_t index)
	{
		_wstr.insert(index, wstring(wchar_list));
		return *this;
	}

	String& String::erase(size_t index, size_t count)
	{
		_wstr.erase(index, count);
		return *this;
	}

	String& String::erase(const_iterator position)
	{
		_wstr.erase(position);
		return *this;
	}

	String& String::erase(const_iterator first, const_iterator last)
	{
		_wstr.erase(first, last);
		return *this;
	}

	constexpr void String::push_back(wchar_t wc)
	{
		_wstr.push_back(wc);
	}

	constexpr void String::pop_back()
	{
		_wstr.pop_back();
	}

	String& String::append(char c, size_t count)
	{
		_wstr.append(str_to_wstr(string(count, c)));
		return *this;
	}
 
	String& String::append(wchar_t wc, size_t count)
	{
		_wstr.append(wstring(count, wc));
		return *this;
	}

	String& String::append(const string& str)
	{
		_wstr.append(str_to_wstr(str));
		return *this;
	}

	String& String::append(const wstring& wstr)
	{
		_wstr.append(wstr);
		return *this;
	}

	String& String::append(initializer_list<char> char_list)
	{
		_wstr.append(str_to_wstr(string(char_list)));
		return *this;
	}

	String& String::append(initializer_list<wchar_t> wchar_list)
	{
		_wstr.append(wstring(wchar_list));
		return *this;
	}

	String& String::operator += (char c)
	{
		_wstr.append(str_to_wstr(string(1, c)));
		return *this;
	}

	String& String::operator += (wchar_t wc)
	{
		_wstr += wc;
		return *this;
	}

	String& String::operator += (const string& str)
	{
		_wstr += str_to_wstr(str);
		return *this;
	}

	String& String::operator += (const wstring& wstr)
	{
		_wstr += wstr;
		return *this;
	}

	String& String::operator += (initializer_list<char> char_list)
	{
		_wstr += str_to_wstr(string(char_list));
		return *this;
	}

	String& String::operator += (initializer_list<wchar_t> wchar_list)
	{
		_wstr += wchar_list;
		return *this;
	}

	constexpr bool String::starts_with(char c) const
	{
		return _wstr.starts_with(str_to_wstr(string(1, c)));
	}

	constexpr bool String::starts_with(wchar_t wc) const
	{
		return _wstr.starts_with(wc);
	}

	constexpr bool String::starts_with(const string& str) const
	{
		return _wstr.starts_with(str_to_wstr(str));
	}

	constexpr bool String::starts_with(const wstring& wstr) const
	{
		return _wstr.starts_with(wstr);
	}

	constexpr bool String::ends_with(char c) const
	{
		return _wstr.ends_with(str_to_wstr(string(1, c)));
	}

	constexpr bool String::ends_with(wchar_t wc) const
	{
		return _wstr.ends_with(wc);
	}

	constexpr bool String::ends_with(const string& str) const
	{
		return _wstr.ends_with(str_to_wstr(str));
	}

	constexpr bool String::ends_with(const wstring& wstr) const
	{
		return _wstr.ends_with(wstr);
	}

	constexpr bool String::contains(char c) const
	{
		return _wstr.find(str_to_wstr(string(c, 1))) != wstring::npos;
	}

	constexpr bool String::contains(wchar_t wc) const
	{
		return _wstr.find(wc) != wstring::npos;
	}

	constexpr bool String::contains(const string& str) const
	{
		return _wstr.find(str_to_wstr(str)) != wstring::npos;
	}

	constexpr bool String::contains(const wstring& wstr) const
	{
		return _wstr.find(wstr) != wstring::npos;
	}

	String& String::replace(size_t pos, size_t count, const String& str)
	{
		_wstr.replace(pos, count, str._wstr);
		return *this;
	}

	String& String::replace(const_iterator first, const_iterator last, const String& str)
	{
		_wstr.replace(first, last, str._wstr);
		return *this;
	}

	wstring String::substr(size_t pos, size_t count) const
	{
		return _wstr.substr(pos, count);
	}

	wstring String::substr(const_iterator first, const_iterator last) const
	{
		return wstring(first, last);
	}

	constexpr size_t String::copy(wchar_t* dest, size_t count, size_t pos) const
	{
		return _wstr.copy(dest, count, pos);
	}

	constexpr void String::resize(size_t count)
	{
		_wstr.resize(count);
	}

	constexpr void String::resize(size_t count, wchar_t wc)
	{
		_wstr.resize(count, wc);
	}

	constexpr void String::swap(String& other)
	{
		_wstr.swap(other._wstr);
	}

	constexpr size_t String::find(char c, size_t pos) const noexcept
	{
		return _wstr.find(str_to_wstr(string(c, 1)), pos);
	}

	constexpr size_t String::find(wchar_t wc, size_t pos) const noexcept
	{
		return _wstr.find(wc, pos);
	}

	constexpr size_t String::find(const string& str, size_t pos) const noexcept
	{
		return _wstr.find(str_to_wstr(str), pos);
	}

	constexpr size_t String::find(const wstring& wstr, size_t pos) const noexcept
	{
		return _wstr.find(wstr, pos);
	}

	constexpr size_t String::rfind(char c, size_t pos) const noexcept
	{
		return _wstr.rfind(str_to_wstr(string(c, 1)), pos);
	}

	constexpr size_t String::rfind(wchar_t wc, size_t pos) const noexcept
	{
		return _wstr.rfind(wc, pos);
	}

	constexpr size_t String::rfind(const string& str, size_t pos) const noexcept
	{
		return _wstr.rfind(str_to_wstr(str), pos);
	}

	constexpr size_t String::rfind(const wstring& wstr, size_t pos) const noexcept
	{
		return _wstr.rfind(wstr, pos);
	}

	constexpr size_t String::find_first_of(const string& str, size_t pos) const noexcept
	{
		return _wstr.find_first_of(str_to_wstr(str), pos);
	}

	constexpr size_t String::find_first_of(const wstring& wstr, size_t pos) const noexcept
	{
		return _wstr.find_first_of(wstr, pos);
	}

	constexpr size_t String::find_first_not_of(const string& str, size_t pos) const noexcept
	{
		return _wstr.find_first_not_of(str_to_wstr(str), pos);
	}

	constexpr size_t String::find_first_not_of(const wstring& wstr, size_t pos) const noexcept
	{
		return _wstr.find_first_not_of(wstr, pos);
	}

	constexpr size_t String::find_last_of(const string& str, size_t pos) const noexcept
	{
		return _wstr.find_last_of(str_to_wstr(str), pos);
	}

	constexpr size_t String::find_last_of(const wstring& wstr, size_t pos) const noexcept
	{
		return _wstr.find_last_of(wstr, pos);
	}

	constexpr size_t String::find_last_not_of(const string& str, size_t pos) const noexcept
	{
		return _wstr.find_last_not_of(str_to_wstr(str), pos);
	}

	constexpr size_t String::find_last_not_of(const wstring& wstr, size_t pos) const noexcept
	{
		return _wstr.find_last_not_of(wstr, pos);
	}

	string String::to_str() const
	{
		return wstr_to_str(_wstr);
	}

	wstring String::to_wstr() const
	{
		return _wstr;
	}

	wstring& String::get_wstring()
	{
		return _wstr;
	}

	const wstring& String::get_wstring() const
	{
		return _wstr;
	}

	void print(const String& str)
	{
		wcout << str.data();
	}

	void println(const String& str)
	{
		wcout << str.data() << L'\n';
	}

	strong_ordering compare(const String& A, const String& B)
	{
		return A.get_wstring() <=> B.get_wstring();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

String operator + (const String& A, const String& B)
{
	return String(A.get_wstring() + B.get_wstring());
}

String operator + (const String& A, const string& B)
{
	return String(A.get_wstring() + str_to_wstr(B));
}

String operator + (const String& A, const wstring& B)
{
	return String(A.get_wstring() + B);
}

bool operator == (const jlib::String& A, const jlib::String& B)
{
	return A.get_wstring() == B.get_wstring();
}

bool operator == (const jlib::String& A, const std::string& B)
{
	return A.get_wstring() == str_to_wstr(B);
}

bool operator == (const std::string& A, const jlib::String& B)
{
	return str_to_wstr(A) == B.get_wstring();
}

bool operator == (const String& A, const wstring& B)
{
	return A.get_wstring() == B;
}

bool operator == (const wstring& A, const String& B)
{
	return A == B.get_wstring();
}

bool operator != (const jlib::String& A, const jlib::String& B)
{
	if (A.size() != B.size())
		return true;

	for (size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

bool operator != (const jlib::String& A, const std::string& B)
{
	wstring C(str_to_wstr(B));

	if (A.size() != C.size())
		return true;

	for (size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != C[i])
			return true;
	}

	return false;
}

bool operator != (const std::string& A, const jlib::String& B)
{
	wstring C(str_to_wstr(A));

	if (B.size() != C.size())
		return true;

	for (size_t i = 0; i < B.size(); ++i)
	{
		if (B[i] != C[i])
			return true;
	}

	return false;
}

bool operator != (const String& A, const wstring& B)
{
	if (A.size() != B.size())
		return true;

	for (size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

bool operator != (const wstring& A, const String& B)
{
	if (A.size() != B.size())
		return true;

	for (size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

strong_ordering operator <=> (const String& A, const String& B)
{
	return A.get_wstring() <=> B.get_wstring();
}

strong_ordering operator <=> (const String& A, const string& B)
{
	return A.get_wstring() <=> str_to_wstr(B);
}

strong_ordering operator <=> (const string& A, const String& B)
{
	return str_to_wstr(A) <=> B.get_wstring();
}

strong_ordering operator <=> (const String& A, const wstring& B)
{
	return A.get_wstring() <=> B;
}

strong_ordering operator <=> (const wstring& A, const String& B)
{
	return A <=> B.get_wstring();
}

ostream& operator << (ostream& os, const String& str)
{
	os << str.to_str();
	return os;
}

wostream& operator << (wostream& wos, const String& str)
{
	wos << str.get_wstring();
	return wos;
}

istream& operator >> (istream& is, String& str)
{
	string istr;
	is >> istr;
	str = str_to_wstr(istr);
	return is;
}

wistream& operator >> (wistream& wis, String& str)
{
	wis >> str.get_wstring();
	return wis;
}