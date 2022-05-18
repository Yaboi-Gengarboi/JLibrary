// JLibrary
// Containers
// MiscTemplateFunctions.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-03-05 by Justyn Durnford
// Header file defining several template functions.

module;

#include <array>
#include <functional>
#include <iostream>

export module MiscTemplateFunctions;

export namespace jlib
{
	// Copies every element in the range[from_first, from_first + size) to
	// the elements in the range [to_first, to_first + size).
	// This should be used when the types To and From are different.
	// Otherwise, std::copy from <algorithm> should be used.
	template <typename To, typename From>
	void copy(const From* from_first, const From* from_last, To* to_first)
	{
		for (std::ptrdiff_t i = 0; i < from_last - from_first; ++i)
			to_first[i] = static_cast<To>(from_first[i]);
	}

	// Prints the contents of the array of data using the std::cout ostream.
	// This code will not compile if type T does not overload the 
	// std::ostream insertion operator <<.
	template <typename T>
	void print_array(T* ptr, std::size_t size)
	{
		std::cout << "{ ";

		for (std::size_t i = 0; i < size - 1; ++i)
			std::cout << ptr[i] << ", ";

		std::cout << ptr[size - 1] << " }\n";
	}

	// Prints the contents of the array of data using the std::wcout wostream.
	// This code will not compile if type T does not overload the 
	// std::wostream insertion operator <<.
	template <typename T>
	void print_array_wide(T* ptr, std::size_t size)
	{
		std::wcout << L"{ ";

		for (std::size_t i = 0; i < size - 1; ++i)
			std::wcout << ptr[i] << L", ";

		std::wcout << ptr[size - 1] << L" }\n";
	}
}