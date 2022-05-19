// JLibrary
// String.hpp
// Created on 2022-05-01 by Justyn Durnford
// Last modified on 2022-05-10 by Justyn Durnford
// Header file for the String class.

#pragma once

#include <algorithm>
#include <compare>
#include <cstddef>
#include <initializer_list>
#include <iostream>
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
	std::wstring reverse_wstring(const std::wstring& wstr);

	// 
	std::string substring(const std::string& str, std::size_t pos_begin, std::size_t pos_end);

	// 
	std::wstring substring(const std::wstring& str, std::size_t pos_begin, std::size_t pos_end);

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	class String
	{
		std::wstring _wstr;

		public:

		using value_type = std::wstring::value_type;
		using size_type = std::wstring::size_type;
		using difference_type = std::ptrdiff_t;
		using reference = std::wstring::reference;
		using const_reference = std::wstring::const_reference;
		using pointer = std::wstring::pointer;
		using const_pointer = std::wstring::const_pointer;
		using iterator = std::wstring::iterator;
		using const_iterator = std::wstring::const_iterator;
		using reverse_iterator = std::wstring::reverse_iterator;
		using const_reverse_iterator = std::wstring::const_reverse_iterator;

		// Default constructor.
		String() = default;

		// char character constructor.
		String(char c, std::size_t count = 1);

		// wchar_t character constructor.
		String(wchar_t wc, std::size_t count = 1);

		// std::string constructor.
		String(const std::string& str, std::size_t pos = 0);

		// std::wstring constructor.
		String(const std::wstring& wstr, std::size_t pos = 0);

		// 
		String(std::string::const_iterator begin, std::string::const_iterator end);

		// 
		String(std::wstring::const_iterator begin, std::wstring::const_iterator end);

		// 
		String(std::initializer_list<char> char_list);

		// 
		String(std::initializer_list<wchar_t> wchar_list);

		// Copy constructor.
		String(const String& other) = default;

		// Move constructor.
		String(String&& other) = default;

		// 
		String(std::nullptr_t) = delete;

		// std::string constructor.
		String& operator = (const std::string& str);

		// std::wstring constructor.
		String& operator = (const std::wstring& wstr);

		// Copy assignment operator.
		String& operator = (const String& other) = default;

		// Move assignment operator.
		String& operator = (String&& other) = default;

		// 
		String& operator = (std::nullptr_t) = delete;

		// 
		~String() = default;

		// 
		String& assign(char c, std::size_t count);

		// 
		String& assign(wchar_t wc, std::size_t count);

		// 
		String& assign(const std::string& str, std::size_t pos = 0, std::size_t count = std::string::npos);

		// 
		String& assign(const std::wstring& wstr, std::size_t pos = 0, std::size_t count = std::wstring::npos);

		// 
		String& assign(std::string::const_iterator begin, std::string::const_iterator end);

		// 
		String& assign(std::wstring::const_iterator begin, std::wstring::const_iterator end);

		// 
		String& assign(std::initializer_list<char> char_list);

		// 
		String& assign(std::initializer_list<wchar_t> wchar_list);

		// 
		constexpr wchar_t& at(std::size_t index);

		// 
		constexpr const wchar_t& at(std::size_t index) const;

		// 
		constexpr wchar_t& operator [] (std::size_t index);

		// 
		constexpr const wchar_t& operator [] (std::size_t index) const;

		// 
		constexpr wchar_t& front();

		// 
		constexpr const wchar_t& front() const;

		// 
		constexpr wchar_t& back();

		// 
		constexpr const wchar_t& back() const;

		// 
		constexpr wchar_t* data();

		// 
		constexpr const wchar_t* data() const;

		// 
		constexpr wchar_t* data_end();

		// 
		constexpr const wchar_t* data_end() const;

		// 
		constexpr const wchar_t* c_str() const;

		// 
		constexpr operator std::wstring_view() const noexcept;

		// 
		constexpr iterator begin() noexcept;

		// 
		constexpr const_iterator begin() const noexcept;

		// 
		constexpr const_iterator cbegin() const noexcept;

		// 
		constexpr iterator end() noexcept;

		// 
		constexpr const_iterator end() const noexcept;

		// 
		constexpr const_iterator cend() const noexcept;

		// 
		constexpr reverse_iterator rbegin() noexcept;

		// 
		constexpr const_reverse_iterator rbegin() const noexcept;

		// 
		constexpr const_reverse_iterator crbegin() const noexcept;

		// 
		constexpr reverse_iterator rend() noexcept;

		// 
		constexpr const_reverse_iterator rend() const noexcept;

		// 
		constexpr const_reverse_iterator crend() const noexcept;

		// 
		constexpr bool is_empty() const noexcept;

		// 
		constexpr std::size_t size() const noexcept;

		// 
		constexpr std::size_t length() const noexcept;

		// 
		constexpr std::size_t max_size() const noexcept;

		// 
		constexpr void reserve(std::size_t new_cap);

		// 
		constexpr std::size_t capacity() const noexcept;

		// 
		constexpr void shrink_to_fit();

		// 
		constexpr void clear() noexcept;

		// 
		String& insert(char c, std::size_t index = 0, std::size_t count = 1);

		// 
		String& insert(wchar_t wc, std::size_t index = 0, std::size_t count = 1);

		// 
		String& insert(const std::string& str, std::size_t index = 0);

		// 
		String& insert(const std::wstring& wstr, std::size_t index = 0);

		// 
		String& insert(std::initializer_list<char> char_list, std::size_t index = 0);

		// 
		String& insert(std::initializer_list<wchar_t> wchar_list, std::size_t index = 0);

		// 
		template <class InputIt>
		String& insert(InputIt first, InputIt last, const_iterator pos)
		{
			_wstr.insert(pos, first, last);
			return *this;
		}

		// 
		String& erase(std::size_t index = 0, std::size_t count = std::wstring::npos);

		// 
		String& erase(const_iterator position);

		// 
		String& erase(const_iterator first, const_iterator last);

		// 
		constexpr void push_back(wchar_t wc);

		// 
		constexpr void pop_back();

		// 
		String& append(char c, std::size_t count = 1);

		// 
		String& append(wchar_t wc, std::size_t count = 1);

		// 
		String& append(const std::string& str);

		// 
		String& append(const std::wstring& wstr);

		// 
		String& append(std::initializer_list<char> char_list);

		// 
		String& append(std::initializer_list<wchar_t> wchar_list);

		// 
		template <class InputIt>
		String& append(InputIt first, InputIt last)
		{
			_wstr.append(first, last);
			return *this;
		}

		// 
		String& operator += (char c);

		// 
		String& operator += (wchar_t wc);

		// 
		String& operator += (const std::string& str);

		// 
		String& operator += (const std::wstring& wstr);

		// 
		String& operator += (std::initializer_list<char> char_list);

		// 
		String& operator += (std::initializer_list<wchar_t> wchar_list);

		// 
		constexpr bool starts_with(char c) const;

		// 
		constexpr bool starts_with(wchar_t wc) const;

		// 
		constexpr bool starts_with(const std::string& str) const;

		// 
		constexpr bool starts_with(const std::wstring& wstr) const;

		// 
		constexpr bool ends_with(char c) const;

		// 
		constexpr bool ends_with(wchar_t wc) const;

		// 
		constexpr bool ends_with(const std::string& str) const;

		// 
		constexpr bool ends_with(const std::wstring& wstr) const;

		// 
		constexpr bool contains(char c) const;

		// 
		constexpr bool contains(wchar_t wc) const;

		// 
		constexpr bool contains(const std::string& str) const;

		// 
		constexpr bool contains(const std::wstring& wstr) const;

		// 
		String& replace(std::size_t pos, std::size_t count, const String& str);

		// 
		String& replace(const_iterator first, const_iterator last, const String& str);

		// 
		std::wstring substr(std::size_t pos = 0, std::size_t count = std::wstring::npos) const;

		// 
		std::wstring substr(const_iterator first, const_iterator last) const;

		// 
		constexpr std::size_t copy(wchar_t* dest, std::size_t count, std::size_t pos = 0) const;

		// 
		constexpr void resize(std::size_t count);

		// 
		constexpr void resize(std::size_t count, wchar_t wc);

		//
		constexpr void swap(String& other);

		// 
		constexpr std::size_t find(char c, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t find(wchar_t wc, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t find(const std::string& str, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t find(const std::wstring& wstr, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t rfind(char c, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		constexpr std::size_t rfind(wchar_t wc, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		constexpr std::size_t rfind(const std::string& str, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		constexpr std::size_t rfind(const std::wstring& wstr, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		constexpr std::size_t find_first_of(const std::string& str, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t find_first_of(const std::wstring& wstr, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t find_first_not_of(const std::string& str, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t find_first_not_of(const std::wstring& wstr, std::size_t pos = 0) const noexcept;

		// 
		constexpr std::size_t find_last_of(const std::string& str, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		constexpr std::size_t find_last_of(const std::wstring& wstr, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		constexpr std::size_t find_last_not_of(const std::string& str, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		constexpr std::size_t find_last_not_of(const std::wstring& wstr, std::size_t pos = std::wstring::npos) const noexcept;

		// 
		std::string to_str() const;

		// 
		std::wstring to_wstr() const;

		// 
		std::wstring& get_wstring();

		// 
		const std::wstring& get_wstring() const;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	void print(const String& str);

	// 
	void println(const String& str);

	// 
	std::strong_ordering compare(const String& A, const String& B);
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// 
jlib::String operator + (const jlib::String& A, const jlib::String& B);

// 
jlib::String operator + (const jlib::String& A, const std::string& B);

// 
jlib::String operator + (const jlib::String& A, const std::wstring& B);

// 
bool operator == (const jlib::String& A, const jlib::String& B);

// 
bool operator == (const jlib::String& A, const std::string& B);

// 
bool operator == (const std::string& A, const jlib::String& B);

// 
bool operator == (const jlib::String& A, const std::wstring& B);

// 
bool operator == (const std::wstring& A, const jlib::String& B);

// 
bool operator != (const jlib::String& A, const jlib::String& B);

// 
bool operator != (const jlib::String& A, const std::string& B);

// 
bool operator != (const std::string& A, const jlib::String& B);

// 
bool operator != (const jlib::String& A, const std::wstring& B);

// 
bool operator != (const std::wstring& A, const jlib::String& B);

// 
std::strong_ordering operator <=> (const jlib::String& A, const jlib::String& B);

// 
std::strong_ordering operator <=> (const jlib::String& A, const std::string& B);

// 
std::strong_ordering operator <=> (const std::string& A, const jlib::String& B);

// 
std::strong_ordering operator <=> (const jlib::String& A, const std::wstring& B);

// 
std::strong_ordering operator <=> (const std::wstring& A, const jlib::String& B);

// 
std::ostream& operator << (std::ostream& os, const jlib::String& str);

// 
std::wostream& operator << (std::wostream& wos, const jlib::String& str);

// 
std::istream& operator >> (std::istream& is, jlib::String& str);

// 
std::wistream& operator >> (std::wistream& wis, jlib::String& str);