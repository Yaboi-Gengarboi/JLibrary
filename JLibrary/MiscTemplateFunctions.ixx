// JLibrary
// MiscTemplateFunctions.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-09-28 by Justyn Durnford
// Module file defining several template functions.

module;

#include "Arithmetic.hpp"

#include <array>
#include <functional>
#include <iostream>
#include <numeric>

export module MiscTemplateFunctions;

import ComplexNumber;

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

	// Returns the sum of the passed numbers.
	template <arithmetic T>
	T add_all(T* first, T* last)
	{
		T sum = 0;

		for (T* ptr = first; ptr < last; ++ptr)
			sum += *ptr;

		return sum;
	}

	// Returns the average of the passed numbers.
	template <arithmetic T>
	float average(T* first, T* last)
	{
		return float(add_all(first, last)) / (last - first);
	}

	// 
	template <arithmetic T>
	std::array<ComplexNumber<float>, 2> solve_quadratic(T a, T b, T c)
	{
		std::array<ComplexNumber<float>, 2> arr;

		ComplexNumber<float> discriminant = complex_sqrt(std::powf(b, 2.0f) - (4.0f * a * c));

		arr[0] = (-b - discriminant) / (2.0f * a);
		arr[1] = (-b + discriminant) / (2.0f * a);

		return arr;
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