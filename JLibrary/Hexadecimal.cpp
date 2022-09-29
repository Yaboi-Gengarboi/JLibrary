// JLibrary
// Hexadecimal.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-07-04 by Justyn Durnford
// Source file for Hexadecimal.hpp.

#include "Hexadecimal.hpp"
#include "String.hpp"

#include <algorithm>
using std::transform;

#include <cctype>
using std::toupper;

#include <bit>
using std::endian;
using std::bit_cast;

#include <iomanip>
using std::hex;
using std::setfill;
using std::setw;

#include <stdexcept>
using std::invalid_argument;

#include <sstream>
using std::stringstream;
using std::wstringstream;

#include <string>
using std::size_t;
using std::string;
using std::wstring;
using std::stoi;

namespace jlib
{
	string to_hex_string(unsigned char byte, bool prepend, bool uppercase)
	{
		stringstream str_stream;

		if (prepend)
			str_stream << "0x";

		str_stream << setfill('0') << setw(2) << hex << int(byte);

		string str(str_stream.str());

		if (uppercase)
			transform(str.begin(), str.end(), str.begin(), toupper);

		return str;
	}

	wstring to_hex_wstring(unsigned char byte, bool prepend, bool uppercase)
	{
		return str_to_wstr(to_hex_string(byte, prepend, uppercase));
	}

	string to_hex_string(float number, bool prepend, bool fill, bool uppercase)
	{
		return to_hex_string<int>(bit_cast<int>(number), prepend, fill, uppercase);
	}

	wstring to_hex_wstring(float number, bool prepend, bool fill, bool uppercase)
	{
		return to_hex_wstring<int>(bit_cast<int>(number), prepend, fill, uppercase);
	}

	string to_hex_string(const void* ptr, size_t byte_count, bool uppercase)
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

		if (uppercase)
			transform(str.begin(), str.end(), str.begin(), toupper);

		return str;
	}

	wstring to_hex_wstring(const void* ptr, size_t byte_count, bool uppercase)
	{
		return str_to_wstr(to_hex_string(ptr, byte_count, uppercase));
	}

	float hex_to_float(const string& str)
	{
		if (str.size() != 8)
			throw invalid_argument("\"float hex_to_float(const std::string& str)\" threw an error: String is not long enough.");

		int i;

		if (str.find("0x") == 0)
			i = stoi(str.substr(2), nullptr, 16);
		else
			i = stoi(str, nullptr, 16);

		return bit_cast<float>(i);
	}
}