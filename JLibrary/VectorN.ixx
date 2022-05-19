// JLibrary
// VectorN.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-18 by Justyn Durnford
// Module file for the VectorN template class.

module;

#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

export module VectorN;

import MiscTemplateFunctions;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors with user-defined dimensions.
	template <arithmetic T, std::size_t N> class VectorN
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = std::array<T, N>::iterator;
		using const_iterator = std::array<T, N>::const_iterator;
		using reverse_iterator = std::array<T, N>::reverse_iterator;
		using const_reverse_iterator = std::array<T, N>::const_reverse_iterator;

		private:

		std::array<T, N> _data;

		public:

		// Default constructor.
		VectorN()
		{
			for (size_type i = 0; i < N; ++i)
				_data[i] = static_cast<T>(0);
		}

		// Value constructor.
		// Sets every dimension of the VectorN to the given value.
		VectorN(value_type value)
		{
			std::fill(_data.begin(), _data.end(), value);
		}

		// Constructs the VectorN from the given coordinates.
		VectorN(std::initializer_list<T> elems)
		{
			std::copy(elems.begin(), elems.end(), _data.data());
		}

		// Constructs the VectorN as the displacement vector of the two points.
		VectorN(const VectorN& A, const VectorN& B)
		{
			for (size_type i(0); i < N; ++i)
				_data[i] = B._data[i] - A._data[i];
		}

		// Default copy constructor.
		VectorN(const VectorN& other) = default;

		// Default move constructor.
		VectorN(VectorN&& other) = default;

		// Constructs the VectorN from another type of VectorN.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != charT or V != valT.
		template <arithmetic U>
		VectorN(const VectorN<U, N>& other)
		{
			jlib::copy(other.data(), other.data() + N, data());
		}

		// Constructs the VectorN from the given coordinates.
		VectorN& operator = (std::initializer_list<T> elems)
		{
			std::copy(elems.begin(), elems.end(), _data.data());
			return *this;
		}

		// Default copy assignment operator.
		VectorN& operator = (const VectorN& other) = default;

		// Default move assignment operator.
		VectorN& operator = (VectorN&& other) = default;

		// Copies the components of a different type of VectorN.
		template <arithmetic U>
		void copyFrom(const VectorN<U, N>& other)
		{
			jlib::copy(other.data(), other.data() + N, data());
		}

		// Returns the amount of dimensions the VectorN has.
		constexpr size_type dimensions() const noexcept
		{
			return N;
		}

		// Returns the first element of the VectorN.
		constexpr reference front()
		{
			return _data[0];
		}

		// Returns the first element of the VectorN.
		constexpr const_reference front() const
		{
			return _data[0];
		}

		// Returns the last element of the VectorN.
		constexpr reference back()
		{
			return _data[N - 1];
		}

		// Returns the last element of the VectorN.
		constexpr const_reference back() const
		{
			return _data[N - 1];
		}

		// Returns the pointer to the elements of the VectorN.
		constexpr pointer data() noexcept
		{
			return _data.data();
		}

		// Returns the pointer to the elements of the VectorN.
		constexpr const_pointer data() const noexcept
		{
			return _data.data();
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		constexpr iterator begin() noexcept
		{
			return _data.begin();
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		constexpr const_iterator begin() const noexcept
		{
			return _data.cbegin();
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		constexpr const_iterator cbegin() const noexcept
		{
			return _data.cbegin();
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		constexpr iterator end() noexcept
		{
			return _data.end();
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		constexpr const_iterator end() const noexcept
		{
			return _data.cend();
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		constexpr const_iterator cend() const noexcept
		{
			return _data.cend();
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		constexpr reference at(size_type index)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid VectorN index.");
			return _data[index];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		constexpr const_reference at(size_type index) const
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid VectorN index.");
			return _data[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		constexpr void set(size_type index, const_reference value)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid VectorN index.");
			_data[index] = value;
		}

		// Returns the element at the given index.
		constexpr reference operator [] (size_type index)
		{
			return _data[index];
		}

		// Returns the element at the given index.
		constexpr const_reference operator [] (size_type index) const
		{
			return _data[index];
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Returns a VectorN whose elements are the absolute values of 
	// each of the specified VectorN's elements.
	template <arithmetic T, std::size_t N>
	const VectorN<T, N>& abs(const VectorN<T, N>& vec)
	{
		VectorN<T, N> new_vec;

		for (std::size_t i = 0; i < N; ++i)
			new_vec[i] = std::abs(vec[i]);
	}

	// Returns the scalar projection of A onto B.
	template <arithmetic T, std::size_t N>
	constexpr float comp_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return dot_product(A, B) / magnitude(B);
	}

	// Returns the distance between the 2 given VectorNs.
	template <arithmetic T, std::size_t N>
	constexpr float distance(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return std::sqrtf(distance_squared(A, B));
	}

	// Returns the distance squared between the 2 given Vector2s, treated as points.
	template <arithmetic T, std::size_t N>
	constexpr float distance_squared(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float result = 0.0f;

		for (std::size_t i = 0; i < N; ++i)
			result += std::powf(static_cast<float>(B[i] - A[i]), 2.0f);

		return result;
	}

	// Returns the dot product of the 2 given VectorNs.
	template <arithmetic T, std::size_t N>
	constexpr float dot_product(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float value = 0.0f;

		for (std::size_t i(0); i < N; ++i)
			value += (A[i] * B[i]);

		return value;
	}

	// Returns the magnitude of the given VectorN.
	template <arithmetic T, std::size_t N>
	constexpr float magnitude(const VectorN<T, N>& vec)
	{
		float value = 0.0f;

		for (std::size_t i = 0; i < N; ++i)
			value += std::powf(static_cast<float>(vec[i]), 2);

		return std::sqrtf(value);
	}

	// Returns a VectorN whose elements are the maximum of each of the 
	// pairs of elements in two specified VectorNs.
	template <arithmetic T, std::size_t N>
	VectorN<T, N> max(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> C;

		for (std::size_t i = 0; i < N; ++i)
			C[i] = std::max(A[i], B[i]);

		return C;
	}

	// Returns a VectorN whose elements are the minimum of each of the 
	// pairs of elements in two specified VectorNs.
	template <arithmetic T, std::size_t N>
	VectorN<T, N> min(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> C;

		for (std::size_t i = 0; i < N; ++i)
			C[i] = std::min(A[i], B[i]);

		return C;
	}

	// Normalizes the VectorN by scaling each of its components so that it
	// has a magnitude of 1.
	template <arithmetic T, std::size_t N>
	void normalize(VectorN<T, N>& vec)
	{
		const float m = magnitude(vec);

		for (std::size_t i = 0; i < N; ++i)
			vec[i] /= m;
	}

	// Prints the given VectorN to std::cout.
	template <arithmetic T, std::size_t N>
	void print(const VectorN<T, N>& vec)
	{
		std::cout << to_string(vec);
	}

	// Prints the given VectorN to std::cout with a newline.
	template <arithmetic T, std::size_t N>
	void println(const VectorN<T, N>& vec)
	{
		std::cout << to_string(vec) << '\n';
	}

	// Returns a std::string representation of the given VectorN.
	template <arithmetic T, std::size_t N>
	std::string to_string(const VectorN<T, N>& vec)
	{
		if (N == 0)
			return "";
		if (N == 1)
			return '<' + std::to_string(vec[0]) + '>';

		std::string str;

		str += '<';
		for (std::size_t i = 0; i < N - 1; ++i)
			str += std::to_string(vec[i]) + ", ";
		str += std::to_string(vec[N - 1]) + '>';

		return str;
	}

	// Returns a std::wstring representation of the given VectorN.
	template <arithmetic T, std::size_t N>
	std::wstring to_wstring(const VectorN<T, N>& vec)
	{
		if (N == 0)
			return L"";
		if (N == 1)
			return L'<' + std::to_wstring(vec[0]) + L'>';

		std::wstring wstr;

		wstr += L'<';
		for (std::size_t i = 0; i < N - 1; ++i)
			wstr += std::to_wstring(vec[i]) + L", ";
		wstr += std::to_wstring(vec[N - 1]) + L'>';

		return wstr;
	}

	// Returns a unit vector of the given VectorN.
	template <arithmetic T, std::size_t N>
	VectorN<float, N> unit_vector(const VectorN<T, N>& vec)
	{
		const float m = magnitude(vec);
		VectorN<float, N> new_vec(vec);

		for (std::size_t i = 0; i < N; ++i)
			new_vec[i] /= m;

		return new_vec;
	}

	// Returns the vector projection of A onto B.
	template <arithmetic T, std::size_t N>
	VectorN<float, N> vector_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		const float f = (dot_product(A, B) / dot_product(A, A));
		VectorN<float, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] *= f;

		return V;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	typedef jlib::VectorN<bool, 4>   Vector4b;
	typedef jlib::VectorN<i8, 4>     Vector4c;
	typedef jlib::VectorN<u8, 4>     Vector4uc;
	typedef jlib::VectorN<i16, 4>    Vector4s;
	typedef jlib::VectorN<u16, 4>    Vector4us;
	typedef jlib::VectorN<i32, 4>    Vector4i;
	typedef jlib::VectorN<u32, 4>    Vector4u;
	typedef jlib::VectorN<i64, 4>    Vector4l;
	typedef jlib::VectorN<u64, 4>    Vector4ul;
	typedef jlib::VectorN<size_t, 4> Vector4uz;
	typedef jlib::VectorN<float, 4>  Vector4f;
	typedef jlib::VectorN<double, 4> Vector4d;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <arithmetic T, std::size_t N>
	bool operator == (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (A[i] != B[i])
				return false;
		}

		return true;
	}

	// Overload of binary operator !=
	template <arithmetic T, std::size_t N>
	bool operator != (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (A[i] != B[i])
				return true;
		}

		return false;
	}

	// Overload of binary operator <
	template <arithmetic T, std::size_t N>
	bool operator < (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return magnitude(A) < magnitude(B);
	}

	// Overload of binary operator <=
	template <arithmetic T, std::size_t N>
	bool operator <= (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return magnitude(A) <= magnitude(B);
	}

	// Overload of binary operator >
	template <arithmetic T, std::size_t N>
	bool operator > (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return magnitude(A) > magnitude(B);
	}

	// Overload of binary operator >=
	template <arithmetic T, std::size_t N>
	bool operator >= (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return magnitude(A) >= magnitude(B);
	}

	// Overload of unary operator -
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator - (const VectorN<T, N>& A)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * -1;

		return V;
	}

	// Overload of binary operator +
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator + (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] + B[i];

		return V;
	}

	// Overload of binary operator -
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator - (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] - B[i];

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator * (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * B[i];

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator * (const VectorN<T, N>& A, U scalar)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * scalar;

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator * (U scalar, const VectorN<T, N>& A)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * scalar;

		return V;
	}

	// Overload of binary operator /
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator / (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] / B[i];

		return V;
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator / (const VectorN<T, N>& A, U scalar)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] / scalar;

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator / (U scalar, const VectorN<T, N>& A)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = scalar / A[i];

		return V;
	}

	// Overload of binary operator +=
	template <arithmetic T, std::size_t N>
	VectorN<T, N>& operator += (VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] += B[i];

		return A;
	}

	// Overload of binary operator -=
	template <arithmetic T, std::size_t N>
	VectorN<T, N>& operator -= (VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] -= B[i];

		return A;
	}

	// Overload of binary operator *=
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N>& operator *= (VectorN<T, N>& A, U scalar)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] *= scalar;

		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N>& operator /= (VectorN<T, N>& A, U scalar)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] /= scalar;

		return A;
	}

	// Overload of std::ostream operator <<
	template <arithmetic T, std::size_t N>
	std::ostream& operator << (std::ostream& os, const VectorN<T, N>& A)
	{
		os << to_string(A);
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T, std::size_t N>
	std::wostream& operator << (std::wostream& wos, const VectorN<T, N>& A)
	{
		wos << to_wstring(A);
		return wos;
	}
}