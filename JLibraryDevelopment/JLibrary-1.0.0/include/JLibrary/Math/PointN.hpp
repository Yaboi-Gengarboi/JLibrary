// JLibraryDevelopment
// Point2.hpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the PointN template class.

#pragma once

#ifndef NOMINMAX
	#define NOMINMAX
#endif // NOMINMAX

#include <JLibrary/Math/Arithmetic.hpp>
#include <array>
#include <cmath>
#include <stdexcept>
#include <string>

#pragma once

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with points with N-dimensions.
	template <std_arithmetic T, std::size_t N> class PointN
	{
		// Copies each element from the given source.
		void copyFrom(const T* src_begin)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = src_begin[i];
		}

		public:

		std::array<T, N> data;

		// Default constructor.
		// Sets each component of the PointN to 0.
		PointN()
		{
			for (T& elem : data)
				elem = static_cast<T>(0);
		}

		// Constructs the PointN from the given coordinates.
		PointN(std::initializer_list<T> list)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = *(list.begin() + i);
		}

		// Constructs the PointN from another type of PointN.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		PointN(const PointN<U, N>& other)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = static_cast<T>(other.data[i]);
		}

		// Constructs the PointN from the given coordinates.
		PointN& operator = (std::initializer_list<T> list)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = *(list.begin() + i);
			return *this;
		}

		// Returns the amount of dimensions the PointN has.
		std::size_t dimensions() const
		{
			return N;
		}

		// Returns the first element of the PointN.
		// Throws a std::out_of_range if the PointN is empty.
		T& first()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[0];
		}

		// Returns the first element of the PointN.
		// Throws a std::out_of_range if the PointN is empty.
		const T& first() const
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[0];
		}

		// Returns the last element of the PointN.
		// Throws a std::out_of_range if the PointN is empty.
		T& last()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[N - 1];
		}

		// Returns the last element of the PointN.
		// Throws a std::out_of_range if the PointN is empty.
		const T& last() const
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[N - 1];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		T& at(std::size_t index)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid PointN index.");

			return data[index];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		const T& at(std::size_t index) const
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid PointN index.");

			return data[index];
		}

		// Returns the element at the given index.
		T& operator [] (std::size_t index)
		{
			return data[index];
		}

		// Returns the element at the given index.
		const T& operator [] (std::size_t index) const
		{
			return data[index];
		}

		// Returns a std::string representation of the PointN.
		std::string toString() const
		{
			if (N == 0)
				return "";
			if (N == 1)
				return '(' + std::to_string(data[0]) + ')';

			std::string str;

			str += '(';
			for (std::size_t i(0); i < N - 1; ++i)
				str += std::to_string(data[i]) + ", ";
			str += std::to_string(data[N - 1]) + ')';

			return str;
		}

		// Returns a std::wstring representation of the PointN.
		std::wstring toWideString() const
		{
			if (N == 0)
				return L"";
			if (N == 1)
				return L'(' + std::to_wstring(data[0]) + L')';

			std::wstring str;

			str += L'(';
			for (std::size_t i(0); i < N - 1; ++i)
				str += std::to_wstring(data[i]) + L", ";
			str += std::to_wstring(data[N - 1]) + L')';

			return str;
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Returns the distance between the two PointNs.
	template <std_arithmetic T, std::size_t N>
	float distance_between(const PointN<T, N>& A, const PointN<T, N>& B)
	{
		float value = 0.f;

		for (std::size_t i(0); i < N; ++i)
			value += std::pow(B[i] - A[i], 2);

		return std::sqrt(value);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
template <jlib::std_arithmetic T, std::size_t N>
bool operator == (const jlib::PointN<T, N>& A, const jlib::PointN<T, N>& B)
{
	return A.data == B.data;
}

// Overload of binary operator !=
template <jlib::std_arithmetic T, std::size_t N>
bool operator != (const jlib::PointN<T, N>& A, const jlib::PointN<T, N>& B)
{
	return A.data != B.data;
}