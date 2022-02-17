// JLibrary
// MiscTemplateFunctions.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-02-17 by Justyn Durnford
// Header file defining several template functions.

module;

#include "Arithmetic.hpp"

#include <array>
#include <functional>
#include <iostream>
#include <initializer_list>

export module MiscTemplateFunctions;

import ComplexNumber;

export namespace jlib
{
	// Sets the given value to lower if value < lower.
	template <arithmetic T>
	void clamp_min(T& value, T lower)
	{
		if (value < lower)
			value = lower;
	}

	// Sets the given value to upper if value > upper.
	template <arithmetic T>
	void clamp_max(T& value, T upper)
	{
		if (value > upper)
			value = upper;
	}

	// Sets the given value to lower if value < lower.
	// Sets the given value to upper if value > upper.
	template <arithmetic T>
	void clamp(T& value, T lower, T upper)
	{
		if (value < lower)
			value = lower;
		else if (value > upper)
			value = upper;
	}

	// Returns lower if the given value < lower.
	// Returns upper if the given value > upper.
	// Returns the given value if neither of the
	// above conditions are met.
	template <arithmetic T>
	T clamp_of(T value, T lower, T upper)
	{
		if (value < lower)
			return lower;
		if (value > upper)
			return upper;
		return value;
	}

	// Returns true if the given value is within, but not on, the given bounds.
	template <arithmetic T>
	bool is_within_exclusive(T value, T lower, T upper)
	{
		return (value > lower) && (value < upper);
	}

	// Returns true if the given value is within or on the given bounds.
	template <arithmetic T>
	bool is_within_inclusive(T value, T lower, T upper)
	{
		return (value >= lower) && (value <= upper);
	}

	// Calls the function func on the elements in the range [first, last).
	template <typename T>
	void for_each(T* first, T* last, std::function<void(T&)> func)
	{
		for (T* ptr = first; ptr < last; ++ptr)
			func(*ptr);
	}

	// Sets every element in the range [first, last) to value.
	template <typename T>
	void set_all(T* first, T* last, const T& value)
	{
		for (T* ptr = first; ptr < last; ++ptr)
			*ptr = value;
	}

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
	T add_all(std::initializer_list<T> list)
	{
		T sum = static_cast<T>(0);

		for (auto iter = list.begin(); iter != list.end(); ++iter)
			sum += *iter;

		return sum;
	}

	// Returns the average of the passed numbers.
	template <arithmetic T>
	T average(std::initializer_list<T> list)
	{
		return add_all(list) / list.size();
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

	// Converts the degree from celcius to fahrenheit.
	template <arithmetic T>
	T to_fahrenheit(T temp)
	{
		return temp * (9.0f / 5.0f) + 32;
	}

	// Converts the degree from fahrenheit to celcius.
	template <arithmetic T>
	T to_celcius(T temp)
	{
		return (temp - 32) * (5.0f / 9.0f);
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