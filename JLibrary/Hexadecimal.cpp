// JLibrary
// Hexadecimal.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Source file for Hexadecimal.hpp.

#include "Hexadecimal.hpp"
#include "String.hpp"

#include <bit>
using std::endian;
using std::bit_cast;

#include <iomanip>
using std::hex;
using std::setfill;
using std::setw;

#include <sstream>
using std::stringstream;
using std::wstringstream;

#include <string>
using std::size_t;
using std::string;
using std::wstring;

namespace jlib
{
	string to_hex_string(unsigned char byte, bool prepend)
	{
		stringstream str_stream;

		if (prepend)
			str_stream << "0x";

		str_stream << setfill('0') << setw(2) << hex << int(byte);
		return str_stream.str();
	}

	wstring to_hex_wstring(unsigned char byte, bool prepend)
	{
		wstringstream wstr_stream;

		if (prepend)
			wstr_stream << L"0x";

		wstr_stream << setfill(L'0') << setw(2) << hex << int(byte);
		return wstr_stream.str();
	}

	string to_hex_string(float number, bool prepend, bool fill)
	{
		return to_hex_string<int>(bit_cast<int>(number), prepend, fill);
	}

	wstring to_hex_wstring(float number, bool prepend, bool fill)
	{
		return to_hex_wstring<int>(bit_cast<int>(number), prepend, fill);
	}

	string to_hex_string(const void* ptr, size_t byte_count)
	{
		string str;
		str.reserve(byte_count * 2);
		stringstream str_stream;
		const unsigned char* char_ptr = reinterpret_cast<const unsigned char*>(ptr);

		for (size_t i = 0; i < byte_count; ++i)
		{
			str_stream << setfill('0') << setw(2) << hex << int(char_ptr[i]);

			if (endian::native == endian::little)
				str.insert(0, str_stream.str());
			else if (endian::native == endian::big)
				str += str_stream.str();

			str_stream.str("");
		}

		return str;
	}

	wstring to_hex_wstring(const void* ptr, size_t byte_count)
	{
		return str_to_wstr(to_hex_string(ptr, byte_count));
	}
}