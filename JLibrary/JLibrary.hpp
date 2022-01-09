// JLibrary
// JLibrary.hpp
// Created on 2021-08-06 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file for the JLibrary static library.

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#ifndef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#endif // #ifndef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4996)

#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

///////////////////////////////////////////////////////////////////////////////////////////////////
// STANDARD LIBRARY INDLUCES                                                                     //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <codecvt>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <locale>
#include <memory>
#include <numbers>
#include <stdexcept>
#include <string>
#include <utility>
#include <windows.h>
#include <xinput.h>

#ifdef SFML_SYSTEM_WINDOWS

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#endif // #ifdef SFML_SYSTEM_WINDOWS

///////////////////////////////////////////////////////////////////////////////////////////////////
// INTEGER TYPEDEFS                                                                              //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 8-bit signed integer.
	typedef signed char i8;
	// 8-bit unsigned integer.
	typedef unsigned char u8;

	// 16-bit signed integer.
	typedef signed short i16;
	// 16-bit unsigned integer.
	typedef unsigned short u16;

	// 32-bit signed integer.
	typedef signed int i32;
	// 32-bit unsigned integer.
	typedef unsigned int u32;

	#ifdef _WIN64

	// 64-bit signed integer.
	typedef signed long long i64;
	// 64-bit unsigned integer.
	typedef unsigned long long u64;

	#else

	// 64-bit signed integer.
	typedef signed __int64 i64;
	// 64-bit unsigned integer.
	typedef unsigned __int64 u64;

	#endif // #ifdef _WIN64

	// Minimum 8-bit signed integer value (-128).
	constexpr i8 I8_MIN = static_cast<i8>(-128);
	// Maximum 8-bit signed integer value (127).
	constexpr i8 I8_MAX = static_cast<i8>(127);

	// Minimun 8-bit unsigned integer value (0).
	constexpr u8 U8_MIN = static_cast<u8>(0);
	// Maximum 8-bit unsigned integer value (255).
	constexpr u8 U8_MAX = static_cast<u8>(255);

	// Minimum 16-bit signed integer value (-32768).
	constexpr i16 I16_MIN = static_cast<i16>(-32768);
	// Maximum 16-bit signed integer value (32767).
	constexpr i16 I16_MAX = static_cast<i16>(32767);

	// Minimun 16-bit unsigned integer value (0).
	constexpr u16 U16_MIN = static_cast<i16>(0);
	// Maximum 16-bit unsigned integer value (65535).
	constexpr u16 U16_MAX = static_cast<i16>(65535);

	// Minimum 32-bit signed integer value (-2147483648).
	constexpr i32 I32_MIN = static_cast<i32>(-2147483648);
	// Maximum 32-bit signed integer value (2147483647).
	constexpr i32 I32_MAX = static_cast<i32>(2147483647);

	// Minimum 32-bit unsigned integer value (0).
	constexpr u32 U32_MIN = static_cast<i32>(0);
	// Maximum 32-bit unsigned integer value (4294967295).
	constexpr u32 U32_MAX = static_cast<i32>(4294967295);

	// Minimum 64-bit signed integer value (-9223372036854775808).
	constexpr i64 I64_MIN = static_cast<i64>(-9223372036854775807 - 1);
	// Maximum 64-bit signed integer value (9223372036854775807).
	constexpr i64 I64_MAX = static_cast<i64>(9223372036854775807);

	// Minimum 64-bit unsigned integer value (0).
	constexpr u64 U64_MIN = static_cast<u64>(0);
	// Maximum 64-bit unsigned integer value (18446744073709551615).
	constexpr u64 U64_MAX = static_cast<u64>(18446744073709551615);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// STD_ARITHMETIC TEMPLATE CONCEPT                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	#ifndef JLIB_STD_ARITHMETIC

	#define JLIB_STD_ARITHMETIC
	template <typename T> concept std_arithmetic = std::is_arithmetic_v<T>;

	#endif // JLIBRARY_STD_ARITHMETIC
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// IMPORTANT CONSTANTS                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	constexpr float JLIB_PI = std::numbers::pi_v<float>;
	constexpr float JLIB_2PI = std::numbers::pi_v<float> *2.0f;
	constexpr float JLIB_PI_2 = std::numbers::pi_v<float> / 2.0f;
	constexpr float JLIB_PI_3 = std::numbers::pi_v<float> / 3.0f;
	constexpr float JLIB_PI_4 = std::numbers::pi_v<float> / 4.0f;
	constexpr float JLIB_PI_6 = std::numbers::pi_v<float> / 6.0f;
	constexpr float JLIB_TO_RAD = std::numbers::pi_v<float> / 180.0f;
	constexpr float JLIB_TO_DEG = 180.f / std::numbers::pi_v<float>;
	constexpr float JLIB_SQRT2 = std::numbers::sqrt2_v<float>;
	constexpr float JLIB_SQRT3 = std::numbers::sqrt3_v<float>;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// MISC TEMPLATE FUNCTIONS                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Sets the given value to lower if value < lower.
	template <std_arithmetic T>
	void clamp_min(T& value, T lower)
	{
		if (value < lower)
			value = lower;
	}

	// Sets the given value to upper if value > upper.
	template <std_arithmetic T>
	void clamp_max(T& value, T upper)
	{
		if (value > upper)
			value = upper;
	}

	// Sets the given value to lower if value < lower.
	// Sets the given value to upper if value > upper.
	template <std_arithmetic T>
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
	template <std_arithmetic T>
	T clamp_of(T value, T lower, T upper)
	{
		if (value < lower)
			return lower;
		if (value > upper)
			return upper;
		return value;
	}

	// Returns true if the given value is within, but not on, the given bounds.
	template <std_arithmetic T>
	bool is_within_exclusive(T value, T lower, T upper)
	{
		return (value > lower) && (value < upper);
	}

	// Returns true if the given value is within or on the given bounds.
	template <std_arithmetic T>
	bool is_within_inclusive(T value, T lower, T upper)
	{
		return (value >= lower) && (value <= upper);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// STRING FUNCTIONS                                                                              //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	std::wstring str_to_wstr(const std::string& str);

	// 
	std::string wstr_to_str(const std::wstring& wstr);

	//
	std::string reverse_string(const std::string& str);

	// 
	std::wstring reverse_string(const std::wstring& wstr);

	// 
	std::string substring(const std::string& str, std::size_t pos_begin, std::size_t pos_end);

	// 
	std::wstring substring(const std::wstring& str, std::size_t pos_begin, std::size_t pos_end);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PTR TEMPLATE CLASS                                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template wrapper class for pointers.
	// This class is NOT intended to be used for memory
	// allocation, it is simply for pointing to objects.
	template <typename T> class Ptr
	{
		T* _ptr;

		public:

		// Default constructor.
		Ptr()
		{
			_ptr = nullptr;
		}

		// Value constructor.
		Ptr(T* ptr)
		{
			_ptr = ptr;
		}

		// Copy constructor.
		Ptr(Ptr& other) = default;

		// Move constructor.
		Ptr(Ptr&& other) noexcept
		{
			_ptr = other._ptr;
			other._ptr = nullptr;
		}

		// Value assignment operator.
		Ptr& operator = (T* ptr)
		{
			_ptr = ptr;
			return *this;
		}

		// Copy assignment operator.
		Ptr& operator = (Ptr& other) = default;

		// Move assignment operator.
		Ptr& operator = (Ptr&& other) noexcept
		{
			_ptr = other._ptr;
			other._ptr = nullptr;
			return *this;
		}

		// Destructor.
		~Ptr() = default;

		// Resets the pointer to nullptr.
		void reset()
		{
			_ptr = nullptr;
		}

		// Returns the underlying raw-pointer.
		T* get()
		{
			return _ptr;
		}

		// Returns the underlying raw-pointer.
		const T* get() const
		{
			return _ptr;
		}

		// Releases and returns the underlying raw-pointer.
		T* release()
		{
			T* ptr = _ptr;
			_ptr = nullptr;
			return ptr;
		}

		// Dereference operator.
		T& operator * ()
		{
			return *_ptr;
		}

		// Dereference operator.
		const T& operator * () const
		{
			return *_ptr;
		}

		// Structure pointer dereference operator.
		T* operator -> ()
		{
			return _ptr;
		}

		// Conversion operator to implicitly convert the pointer to its raw pointer type (T*).
		operator T* () const
		{
			return static_cast<T*>(_ptr);
		}

		// Returns true if the Pointer != nullptr.
		operator bool() const
		{
			return _ptr != nullptr;
		}

		// Overload of unary operator ++
		Ptr& operator ++ ()
		{
			++_ptr;
			return *this;
		}

		// Overload of unary operator ++
		Ptr operator ++ (int)
		{
			Ptr p(*this);
			++_ptr;
			return p;
		}

		// Overload of unary operator --
		Ptr& operator -- ()
		{
			--_ptr;
			return *this;
		}

		// Overload of unary operator --
		Ptr operator -- (int)
		{
			Ptr p(*this);
			--_ptr;
			return p;
		}
	};

	// Overload of binary operator +
	template <typename T>
	Ptr<T> operator + (const Ptr<T>& A, std::ptrdiff_t offset)
	{
		return Ptr<T>(A.get() + offset);
	}

	// Overload of binary operator -
	template <typename T>
	Ptr<T> operator - (const Ptr<T>& A, std::ptrdiff_t offset)
	{
		return Ptr<T>(A.get() - offset);
	}

	// Overload of binary operator -
	template <typename T>
	std::ptrdiff_t operator - (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() - B.get();
	}

	// Overload of binary operator -
	template <typename T>
	std::ptrdiff_t operator - (const Ptr<T>& A, const T* B)
	{
		return A.get() - B;
	}

	// Overload of binary operator +=
	template <typename T>
	Ptr<T>& operator += (Ptr<T>& A, std::ptrdiff_t offset)
	{
		A.get() += offset;
		return *this;
	}

	// Overload of binary operator -=
	template <typename T>
	Ptr<T>& operator -= (Ptr<T>& A, std::ptrdiff_t offset)
	{
		A.get() -= offset;
		return *this;
	}

	// Overload of binary operator ==
	template <typename T>
	bool operator == (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() == B.get();
	}

	// Overload of binary operator ==
	template <typename T>
	bool operator == (const Ptr<T>& A, const T* B)
	{
		return A.get() == B;
	}

	// Overload of binary operator ==
	template <typename T>
	bool operator == (const Ptr<T>& A, std::nullptr_t)
	{
		return A.get() == nullptr;
	}

	// Overload of binary operator !=
	template <typename T>
	bool operator != (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() != B.get();
	}

	// Overload of binary operator !=
	template <typename T>
	bool operator != (const Ptr<T>& A, const T* B)
	{
		return A.get() != B;
	}

	// Overload of binary operator !=
	template <typename T>
	bool operator != (const Ptr<T>& A, std::nullptr_t)
	{
		return A.get() != nullptr;
	}

	// Overload of binary operator <
	template <typename T>
	bool operator < (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() < B.get();
	}

	// Overload of binary operator <
	template <typename T>
	bool operator < (const Ptr<T>& A, const T* B)
	{
		return A.get() < B;
	}

	// Overload of binary operator <=
	template <typename T>
	bool operator <= (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() <= B.get();
	}

	// Overload of binary operator <=
	template <typename T>
	bool operator <= (const Ptr<T>& A, const T* B)
	{
		return A.get() <= B;
	}

	// Overload of binary operator >
	template <typename T>
	bool operator > (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() > B.get();
	}

	// Overload of binary operator >
	template <typename T>
	bool operator > (const Ptr<T>& A, const T* B)
	{
		return A.get() > B;
	}

	// Overload of binary operator >=
	template <typename T>
	bool operator >= (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() >= B.get();
	}

	// Overload of binary operator >=
	template <typename T>
	bool operator >= (const Ptr<T>& A, const T* B)
	{
		return A.get() > B;
	}

	// Overload of binary operator <=>
	template <typename T>
	std::strong_ordering operator <=> (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() <=> B.get();
	}

	// Overload of binary operator <=>
	template <typename T>
	std::strong_ordering operator <=> (const Ptr<T>& A, const T* B)
	{
		return A.get() <=> B;
	}

	// Overload of std::ostream operator <<
	template <typename T>
	std::ostream& operator << (std::ostream& os, const Ptr<T>& A)
	{
		os << A.get();
		return os;
	}

	// Overload of std::wostream operator <<
	template <typename T>
	std::wostream& operator << (std::wostream& wos, const Ptr<T>& A)
	{
		wos << A.get();
		return wos;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// FIXEDARRAY TEMPLATE CLASS                                                                     //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <typename T, std::size_t N> class FixedArray
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		private:

		pointer _data;

		void allocate()
		{
			if (N != 0)
			{
				try
				{
					_data = new value_type[N];
				}
				catch (...)
				{
					_data = nullptr;
					throw;
				}
			}
			else
				_data = nullptr;
		}

		public:

		// Default constructor.
		FixedArray()
		{
			allocate();
		}

		// Value constructor.
		FixedArray(const_reference value)
		{
			allocate();
			for (size_type i = 0; i < N; ++i)
				_data[i] = value;
		}

		// std::initializer_list constructor.
		FixedArray(std::initializer_list<T> elems)
		{
			allocate();
			std::copy(elems.begin(), elems.begin() + N, _data);
		}

		// std::array constructor.
		FixedArray(const std::array<T, N>& arr)
		{
			allocate();
			std::copy(arr.begin(), arr.end(), _data);
		}

		// Copy constructor.
		FixedArray(const FixedArray& other)
		{
			allocate();
			std::copy(other.begin(), other.end(), _data);
		}

		// Different-type Copy constructor.
		template <typename U>
		explicit FixedArray(const FixedArray<U, N>& other)
		{
			allocate();
			for (size_type i = 0; i < N; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Move constructor.
		FixedArray(FixedArray&& other) noexcept
		{
			std::swap(_data, other._data);
		}

		// std::initializer_list assignment operator.
		FixedArray& operator = (std::initializer_list<T> elems)
		{
			std::copy(elems.begin(), elems.begin() + N, _data);
			return *this;
		}

		// std::array assignment operator.
		FixedArray& operator = (const std::array<T, N>& arr)
		{
			std::copy(arr.begin(), arr.end(), _data);
			return *this;
		}

		// Copy assignment operator.
		FixedArray& operator = (const FixedArray& other)
		{
			std::copy(other.begin(), other.end(), _data);
			return *this;
		}

		// Move assignment operator.
		FixedArray& operator = (FixedArray&& other) noexcept
		{
			delete[] _data;
			_data = nullptr;
			std::swap(_data, other._data);
			return *this;
		}

		// Destructor.
		~FixedArray() noexcept
		{
			delete[] _data;
		}

		// Returns the size of the FixedArray.
		constexpr size_type size() const noexcept
		{
			return N;
		}

		// Returns true if the FixedArray has a size of 0.
		constexpr bool isEmpty() const noexcept
		{
			return N == 0;
		}

		// Returns the first element of the FixedArray.
		reference first()
		{
			return _data[0];
		}

		// Returns the first element of the FixedArray.
		const_reference first() const
		{
			return _data[0];
		}

		// Returns the last element of the FixedArray.
		reference last()
		{
			return _data[N - 1];
		}

		// Returns the last element of the FixedArray.
		const_reference last() const
		{
			return _data[N - 1];
		}

		// Returns the pointer of the FixedArray.
		pointer data() noexcept
		{
			return _data;
		}

		// Returns the pointer of the FixedArray.
		const_pointer data() const noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		iterator begin() noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator begin() const noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator cbegin() const noexcept
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		reverse_iterator rbegin() noexcept
		{
			return std::reverse_iterator<iterator>(_data + N);
		}

		// Returns a reverse iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator rbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + N);
		}

		// Returns a reverse iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator crbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + N);
		}

		// Returns an iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		iterator end() noexcept
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator end() const noexcept
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator cend() const noexcept
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		reverse_iterator rend() noexcept
		{
			return std::reverse_iterator<iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator rend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator crend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns the element at the given index of the FixedArray.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid array index.");
			return _data[index];
		}

		// Returns the element at the given index of the FixedArray.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type index) const
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid array index.");
			return _data[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type index, const_reference value)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid array index.");
			_data[index] = value;
		}

		// Swaps the contents of this FixedArray with another FixedArray.
		void swapWith(FixedArray& other) noexcept
		{
			std::swap(_data, other._data);
		}

		// Returns the element at the given index the FixedArray.
		// Does NOT perform bounds-checking.
		reference operator [] (size_type index)
		{
			return _data[index];
		}

		// Returns the element at the given index the FixedArray.
		// Does NOT perform bounds-checking.
		const_reference operator [] (size_type index) const
		{
			return _data[index];
		}
	};
}

// Overload of binary operator ==
template <typename T, std::size_t N>
bool operator == (const jlib::FixedArray<T, N>& A, const jlib::FixedArray<T, N>& B)
{
	for (std::size_t i = 0; i < N; ++i)
	{
		if (A[i] != B[i])
			return false;
	}

	return true;
}

// Overload of binary operator !=
template <typename T, std::size_t N>
bool operator != (const jlib::FixedArray<T, N>& A, const jlib::FixedArray<T, N>& B)
{
	for (std::size_t i = 0; i < N; ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// ARRAY TEMPLATE CLASS                                                                          //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <typename T> class Array
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = const std::reverse_iterator<iterator>;

		private:

		pointer _data;
		size_type _size;

		// 
		void allocate(size_type size)
		{
			if (size == 0)
			{
				_data = nullptr;
				_size = 0;
			}
			else
			{
				try
				{
					_data = new value_type[size];
					_size = size;
				}
				catch (...)
				{
					_data = nullptr;
					_size = 0;
					throw;
				}
			}
		}

		// 
		void reallocate(size_type size)
		{
			if (size != _size)
			{
				delete[] _data;
				allocate(size);
			}
		}

		public:

		// Default constructor.
		Array()
		{
			allocate(0);
		}

		// Size constructor.
		Array(size_type size)
		{
			allocate(size);
		}

		// Size and value constructor.
		Array(size_type size, const_reference value)
		{
			allocate(size);

			for (size_type i(0); i < _size; ++i)
				_data[i] = value;
		}

		// Constructs the Array with the contents in the range[begin, end).
		// This DOES NOT move the contents from the given range, it simply
		// copies its contents into the new Array.
		Array(const_pointer begin, const_pointer end)
		{
			size_type size = end - begin;
			allocate(size);
			std::copy(begin, end, _data);
		}

		// std::initializer_list constructor.
		Array(std::initializer_list<T> elems)
		{
			allocate(elems.size());
			std::copy(elems.begin(), elems.end(), _data);
		}

		// Copy constructor.
		Array(const Array& other)
		{
			allocate(other._size);
			std::copy(other._data, other._data + _size, _data);
		}

		// Constructs the Array from another type of Array.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <typename U>
		explicit Array(const Array<U>& other)
		{
			allocate(other._size);

			for (size_type i(0); i < _size; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Move constructor.
		Array(Array&& other) noexcept
		{
			_data = other._data;
			_size = other._size;
			other._data = nullptr;
			other._size = 0;
		}

		// std::initializer_list assignment operator.
		Array& operator = (std::initializer_list<T> elems)
		{
			reallocate(elems.size());
			std::copy(elems.begin(), elems.end(), _data);
			return *this;
		}

		// Copy assignment operator.
		Array& operator = (const Array& other)
		{
			reallocate(other._size);
			std::copy(other._data, other._data + _size, _data);
			return *this;
		}

		// Move assignment operator.
		Array& operator = (Array&& other) noexcept
		{
			delete[] _data;
			_data = other._data;
			_size = other._size;
			other._data = nullptr;
			other._size = 0;
			return *this;
		}

		// Destructor.
		~Array() noexcept
		{
			delete[] _data;
		}

		// Returns the size of the Array.
		size_type size() const noexcept
		{
			return _size;
		}

		// Returns true if the Array is empty.
		bool isEmpty() const noexcept
		{
			return _size != 0;
		}

		// Returns the first element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		reference first()
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[0];
		}

		// Returns the first element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		const_reference first() const
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[0];
		}

		// Returns the last element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		reference last()
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[_size - 1];
		}

		// Returns the last element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		const_reference last() const
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[_size - 1];
		}

		// Returns the pointer of the Array.
		pointer data() noexcept
		{
			return _data;
		}

		// Returns the pointer of the Array.
		const_pointer data() const noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		iterator begin() noexcept
		{
			return iterator(_data);
		}

		// Returns an iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator begin() const noexcept
		{
			return const_iterator(_data);
		}

		// Returns an iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator cbegin() const noexcept
		{
			return const_iterator(_data);
		}

		// Returns a reverse iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(_data);
		}

		// Returns a reverse iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(_data);
		}

		// Returns a reverse iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(_data);
		}

		// Returns an iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		iterator end() noexcept
		{
			return iterator(_data + _size);
		}

		// Returns an iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator end() const noexcept
		{
			return const_iterator(_data + _size);
		}

		// Returns an iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator cend() const noexcept
		{
			return const_iterator(_data + _size);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		reverse_iterator rend() noexcept
		{
			return reverse_iterator(_data + _size);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(_data + _size);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(_data + _size);
		}

		// Returns the element at the given index of the Array.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= _size)
				throw std::out_of_range("ERROR: Invalid array index.");

			return _data[index];
		}

		// Returns the element at the given index of the Array.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type index) const
		{
			if (index >= _size)
				throw std::out_of_range("ERROR: Invalid array index.");

			return _data[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type index, const_reference value)
		{
			if (index >= _size)
				throw std::out_of_range("ERROR: Invalid array index.");

			_data[index] = value;
		}

		// Empties the Array.
		void clear() noexcept
		{
			delete[] _data;
			_size = 0;
		}

		// Swaps the contents of this Array with another Array.
		void swapWith(Array& other) noexcept
		{
			std::swap(_data, other._data);
			std::swap(_size, other._size);
		}

		// Returns the element at the given index the Array.
		// Does NOT perform bounds-checking.
		reference operator [] (size_type index)
		{
			return _data[index];
		}

		// Returns the element at the given index the Array.
		// Does NOT perform bounds-checking.
		const_reference operator [] (size_type index) const
		{
			return _data[index];
		}
	};
}

// Overload of binary operator ==
template <typename T>
bool operator == (const jlib::Array<T>& A, const jlib::Array<T>& B)
{
	if (A.size() != B.size())
		return false;

	for (std::size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return false;
	}

	return true;
}

// Overload of binary operator !=
template <typename T>
bool operator != (const jlib::Array<T>& A, const jlib::Array<T>& B)
{
	if (A.size() != B.size())
		return true;

	for (std::size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// ANGLE CLASS                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Returns the convertion from degrees to radians.
	constexpr float to_radians(float degree);

	// Returns the convertion from radians to degrees.
	constexpr float to_degrees(float radian);

	// Restricts the given angle to be between 0 and 360 degrees.
	void restrict_360(float& degree);

	// Returns the sine and cosine of the given degree.
	std::array<float, 2> sincos(float degree);

	class Angle
	{
		public:

		float degree;

		// Default constructor.
		Angle();

		// Float constructor.
		// Sets the Angle to the given degree.
		Angle(float new_degree);

		// Float assignment operator.
		// Sets the Angle to the given degree.
		Angle& operator = (float new_degree);

		// Returns a std::string representation of the Angle.
		std::string toString() const;

		// Returns a std::wstring representation of the Angle.
		std::wstring toWideString() const;
	};

	// Returns the sine of the Angle.
	float sine(Angle angle);

	// Returns the cosine of the Angle.
	float cosine(Angle angle);

	// Returns the tangent of the Angle.
	float tangent(Angle angle);

	// 
	Angle arcsine(float value);

	// 
	Angle arccosine(float value);

	// 
	Angle arctangent(float value);

	// Returns the smallest of the two Angles.
	Angle& least(Angle& A, Angle& B);

	// Returns the largest of the two Angles.
	Angle& greatest(Angle& A, Angle& B);
}

// Overload of binary operator ==
bool operator == (jlib::Angle A, jlib::Angle B);

// Overload of binary operator ==
bool operator == (jlib::Angle A, float degree);

// Overload of binary operator !=
bool operator != (jlib::Angle A, jlib::Angle B);

// Overload of binary operator !=
bool operator != (jlib::Angle A, float degree);

// Overload of binary operator <
bool operator < (jlib::Angle A, jlib::Angle B);

// Overload of binary operator <
bool operator < (jlib::Angle A, float degree);

// Overload of binary operator <=
bool operator <= (jlib::Angle A, jlib::Angle B);

// Overload of binary operator <=
bool operator <= (jlib::Angle A, float degree);

// Overload of binary operator >
bool operator > (jlib::Angle A, jlib::Angle B);

// Overload of binary operator >
bool operator > (jlib::Angle A, float degree);

// Overload of binary operator >=
bool operator >= (jlib::Angle A, jlib::Angle B);

// Overload of binary operator >=
bool operator >= (jlib::Angle A, float degree);

// Overload of binary operator <=>
std::strong_ordering operator <=> (jlib::Angle A, jlib::Angle B);

// Overload of binary operator <=>
std::strong_ordering operator <=> (jlib::Angle A, float degree);

// Overload of unary operator -
jlib::Angle operator - (jlib::Angle A);

// Overload of binary operator +
jlib::Angle operator + (jlib::Angle A, jlib::Angle B);

// Overload of binary operator +
jlib::Angle operator + (jlib::Angle A, float degree);

// Overload of binary operator -
jlib::Angle operator - (jlib::Angle A, jlib::Angle B);

// Overload of binary operator -
jlib::Angle operator - (jlib::Angle A, float degree);

// Overload of binary operator *
jlib::Angle operator * (jlib::Angle A, float scalar);

// Overload of binary operator /
jlib::Angle operator / (jlib::Angle A, float scalar);

// Overload of binary operator +=
jlib::Angle& operator += (jlib::Angle& A, jlib::Angle B);

// Overload of binary operator +=
jlib::Angle& operator += (jlib::Angle& A, float degree);

// Overload of binary operator -=
jlib::Angle& operator -= (jlib::Angle& A, jlib::Angle B);

// Overload of binary operator -=
jlib::Angle& operator -= (jlib::Angle& A, float degree);

// Overload of binary operator *=
jlib::Angle& operator *= (jlib::Angle& A, float scalar);

// Overload of binary operator /=
jlib::Angle& operator /= (jlib::Angle& A, float scalar);

// Overload of std::ostream operator <<
std::ostream& operator << (std::ostream& os, jlib::Angle A);

// Overload of std::wostream operator <<
std::wostream& operator << (std::wostream& wos, jlib::Angle A);

///////////////////////////////////////////////////////////////////////////////////////////////////
// FRACTION TEMPLATE CLASS                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// This class provides an "exact" representation of the quotient of two 
	// integers by storing them and allowing fraction arithmetic with them. 
	// Use the member function result() to obtain the result of the fraction.
	template <std::integral T> class Fraction
	{
		public:

		T numer;
		T denom;

		// Default constructor.
		// Sets the numerator of the Fraction to 0.
		// Sets the denominator of the Fraction to 1.
		Fraction()
		{
			numer = static_cast<T>(0);
			denom = static_cast<T>(1);
		}

		// 1-int constructor.
		// Sets the numerator of the Fraction to new_numer.
		// Sets the denominator of the Fraction to 1.
		Fraction(T new_numer)
		{
			numer = new_numer;
			denom = static_cast<T>(1);
		}

		// 2-int constructor.
		// Sets the numerator of the Fraction to new_numer.
		// Sets the denominator of the Fraction to new_denom.
		Fraction(T new_numer, T new_denom)
		{
			numer = new_numer;
			denom = new_denom;
		}

		// Constructs the Fraction from another type of Fraction.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::integral U>
		explicit Fraction(const Fraction<U>& other)
		{
			numer = static_cast<T>(other.numer);
			denom = static_cast<T>(other.denom);
		}

		// 1-int assignment operator.
		// Sets the numerator of the Fraction to new_numer.
		// Sets the denominator of the Fraction to 1.
		Fraction& operator = (T new_numer)
		{
			numer = new_numer;
			denom = static_cast<T>(1);
			return *this;
		}

		// Sets all the values of the Fraction at once.
		// Sets the numerator of the Fraction to new_numer.
		// Sets the denominator of the Fraction to new_denom.
		void set(T new_numer, T new_denom)
		{
			numer = new_numer;
			denom = new_denom;
		}

		// Raises both the numerator and denominator of the Fraction to the nth power.
		template <std::unsigned_integral U> void pow(U N)
		{
			if (N == 1)
				return;

			if (N == 0)
			{
				numer = static_cast<U>(1);
				denom = static_cast<U>(1);
				return;
			}

			T old_numer = numer;
			T old_denom = denom;

			for (U i = 0; i < N; ++i)
			{
				numer *= old_numer;
				denom *= old_denom;
			}
		}

		// Returns the result of the Fraction as a float.
		// This function may throw if a division by 0 is attempted.
		float result() const
		{
			return static_cast<float>(numer) / static_cast<float>(denom);
		}

		// Returns true if the denominator of the Fraction is NOT 0.
		bool isValid() const
		{
			return (denom != 0);
		}

		// Returns a std::string representation of the Fraction.
		std::string toString() const
		{
			return std::to_string(numer) + " / " + std::to_string(denom);
		}

		// Returns a std::wstring representation of the Fraction.
		std::wstring toWideString() const
		{
			return std::to_wstring(numer) + L" / " + std::to_wstring(denom);
		}

		// Preincrement operator.
		Fraction& operator ++ ()
		{
			numer += denom;
			return *this;
		}

		// Postincrement operator.
		Fraction operator ++ (int)
		{
			Fraction fr(*this);
			++(*this);

			return fr;
		}

		// Predecrement operator.
		Fraction& operator -- ()
		{
			numer -= denom;
			return *this;
		}

		// Postdecrement operator.
		Fraction operator -- (int)
		{
			Fraction fr(*this);
			--(*this);

			return fr;
		}
	};
}

// Overload of binary operator ==
template <std::integral T>
bool operator == (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.result() == B.result();
}

// Overload of binary operator ==
template <std::integral T>
bool operator == (const jlib::Fraction<T>& A, float B)
{
	return A.result() == B;
}

// Overload of binary operator !=
template <std::integral T>
bool operator != (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.result() != B.result();
}

// Overload of binary operator !=
template <std::integral T>
bool operator != (const jlib::Fraction<T>& A, float B)
{
	return A.result() != B;
}

// Overload of binary operator >
template <std::integral T>
bool operator > (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.result() > B.result();
}

// Overload of binary operator >
template <std::integral T>
bool operator > (const jlib::Fraction<T>& A, float B)
{
	return A.result() > B;
}

// Overload of binary operator >=
template <std::integral T>
bool operator >= (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.result() >= B.result();
}

// Overload of binary operator >=
template <std::integral T>
bool operator >= (const jlib::Fraction<T>& A, float B)
{
	return A.result() >= B;
}

// Overload of binary operator <
template <std::integral T>
bool operator < (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.result() < B.result();
}

// Overload of binary operator <
template <std::integral T>
bool operator < (const jlib::Fraction<T>& A, float B)
{
	return A.result() < B;
}

// Overload of binary operator <=
template <std::integral T>
bool operator <= (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.result() <= B.result();
}

// Overload of binary operator <=
template <std::integral T>
bool operator <= (const jlib::Fraction<T>& A, float B)
{
	return A.result() <= B;
}

// Overload of binary operator <=>
template <std::integral T>
std::strong_ordering operator <=> (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	if (A.result() < B.result())
		return std::strong_ordering::less;

	if (A.result() > B.result())
		return std::strong_ordering::greater;

	return std::strong_ordering::equal;
}

// Overload of binary operator <=>
template <std::integral T>
std::strong_ordering operator <=> (const jlib::Fraction<T>& A, float B)
{
	if (A.result() < B)
		return std::strong_ordering::less;

	if (A.result() > B)
		return std::strong_ordering::greater;

	return std::strong_ordering::equivalent;
}

// Overload of unary operator -
template <std::integral T>
jlib::Fraction<T> operator - (const jlib::Fraction<T>& A)
{
	return jlib::Fraction<T>(-A.numer, -A.denom);
}

// Overload of binary operator +
template <std::integral T>
jlib::Fraction<T> operator + (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	if (A.denom == B.denom)
		return jlib::Fraction<T>(A.numer + B.numer, A.denom);
	// else if (A.denom != B.denom)
	return jlib::Fraction<T>(A.numer * B.denom + B.numer * A.denom, A.denom * B.denom);
}

// Overload of binary operator +
template <std::integral T>
jlib::Fraction<T> operator + (const jlib::Fraction<T>& A, T value)
{
	return A + jlib::Fraction<T>(value);
}

// Overload of binary operator -
template <std::integral T>
jlib::Fraction<T> operator - (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	if (A.denom == B.denom)
		return jlib::Fraction<T>(A.numer - B.numer, A.denom);
	// else if (A.denom != B.denom)
	return jlib::Fraction<T>(A.numer * B.denom - B.numer * A.denom, A.denom * B.denom);
}

// Overload of binary operator -
template <std::integral T>
jlib::Fraction<T> operator - (const jlib::Fraction<T>& A, T value)
{
	return A - jlib::Fraction<T>(value);
}

// Overload of binary operator *
template <std::integral T>
jlib::Fraction<T> operator * (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return jlib::Fraction<T>(A.numer * B.numer, A.denom * B.denom);
}

// Overload of binary operator *
template <std::integral T>
jlib::Fraction<T> operator * (const jlib::Fraction<T>& A, T value)
{
	return jlib::Fraction<T>(A.numer * value, A.denom * value);
}

// Overload of binary operator *
template <std::integral T>
jlib::Fraction<T> operator * (T value, const jlib::Fraction<T>& A)
{
	return value * A.result();
}

// Overload of binary operator /
template <std::integral T>
jlib::Fraction<T> operator / (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return jlib::Fraction<T>(A.numer * B.denom, A.denom * B.numer);
}

// Overload of binary operator /
template <std::integral T>
jlib::Fraction<T> operator / (const jlib::Fraction<T>& A, T value)
{
	return jlib::Fraction<T>(A.numer, A.denom * value);
}

// Overload of binary operator /
template <std::integral T>
jlib::Fraction<T> operator / (T value, const jlib::Fraction<T>& A)
{
	return value / A.result();
}

// Overload of binary operator +=
template <std::integral T>
jlib::Fraction<T>& operator += (jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	if (A.denom == B.denom)
	{
		A.numer += B.numer;
		return A;
	}

	// else if (A.denom != B.denom)
	T old_denom = A.denom;

	A.numer *= B.denom;
	A.denom *= B.denom;

	A.numer += B.numer * old_denom;
	return A;
}

// Overload of binary operator +=
template <std::integral T>
jlib::Fraction<T>& operator += (jlib::Fraction<T>& A, T value)
{
	A += jlib::Fraction<T>(value);
	return A;
}

// Overload of binary operator -=
template <std::integral T>
jlib::Fraction<T>& operator -= (jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	if (A.denom == B.denom)
	{
		A.numer -= B.numer;
		return A;
	}

	// else if (A.denom != B.denom)
	T old_denom = A.denom;

	A.numer *= B.denom;
	A.denom *= B.denom;

	A.numer -= B.numer * old_denom;
	return A;
}

// Overload of binary operator -=
template <std::integral T>
jlib::Fraction<T>& operator -= (jlib::Fraction<T>& A, T value)
{
	A -= jlib::Fraction<T>(value);
	return A;
}

// Overload of binary operator *=
template <std::integral T>
jlib::Fraction<T>& operator *= (jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	A.numer *= B.numer;
	A.denom *= B.denom;
	return A;
}

// Overload of binary operator *=
template <std::integral T, std::integral U>
jlib::Fraction<T>& operator *= (jlib::Fraction<T>& A, U value)
{
	A.numer *= value;
	return A;
}

// Overload of binary operator /=
template <std::integral T>
jlib::Fraction<T>& operator /= (jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	A.numer *= B.denom;
	A.denom *= B.numer;
	return A;
}

// Overload of binary operator /=
template <std::integral T, std::integral U>
jlib::Fraction<T>& operator /= (jlib::Fraction<T>& A, U value)
{
	A.denom *= value;
	return A;
}

// Overload of std::ostream operator << 
template <std::integral T>
std::ostream& operator << (std::ostream& os, const jlib::Fraction<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator << 
template <std::integral T>
std::wostream& operator << (std::wostream& wos, const jlib::Fraction<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// VECTOR2 TEMPLATE CLASS                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors in 2-dimensional space.
	template <std_arithmetic T> class Vector2
	{
		public:

		T x;
		T y;

		// Default constructor.
		// Sets the x component of the Vector2 to 0.
		// Sets the y component of the Vector2 to 0.
		Vector2()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
		}

		// Constructs the Vector2 from the given coordinates.
		// Sets the x component of the Vector2 to new_x.
		// Sets the y component of the Vector2 to new_y.
		Vector2(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Constructs the Vector2 from the given Angle and magnitude.
		// Sets the x component of the Vector2 to F * cosine(angle).
		// Sets the y component of the Vector2 to F * sine(angle).
		Vector2(T F, Angle angle)
		{
			x = static_cast<T>(cosine(angle));
			y = static_cast<T>(sine(angle));
		}

		// Constructs the Vector2 as the displacement vector of the two points.
		// Sets the x component of the Vector2 to B.x - A.x.
		// Sets the y component of the Vector2 to B.y - A.y.
		Vector2(const Vector2<T>& A, const Vector2<T>& B)
		{
			x = B.x - A.x;
			y = B.y - A.y;
		}

		// Default copy constructor.
		Vector2(const Vector2& other) = default;

		// Default move constructor.
		Vector2(Vector2&& other) = default;

		// Constructs the Vector2 from another type of Vector2.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Vector2(const Vector2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Default copy assignment operator.
		Vector2& operator = (const Vector2& other) = default;

		// Default move assignment operator.
		Vector2& operator = (Vector2&& other) = default;

		// Destructor.
		~Vector2() = default;

		// Sets all the values of the Vector2 at once.
		// Sets the x component of the Vector2 to new_x.
		// Sets the y component of the Vector2 to new_y.
		void set(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Copies the components of a different type of Vector2.
		template <jlib::std_arithmetic U>
		void copyFrom(const Vector2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Returns the magnitude of the Vector2.
		constexpr float magnitude() const
		{
			return std::sqrtf(std::powf(static_cast<float>(x), 2.0f) + std::powf(static_cast<float>(y), 2.0f));
		}

		// Returns the unit vector of this Vector2.
		Vector2<float> unitVector() const
		{
			constexpr float m = magnitude();
			return Vector2<float>(x / m, y / m);
		}

		// Returns a normal vector of this Vector2.
		Vector2 normal()
		{
			return Vector2(-y, x);
		}

		// Returns a std::string representation of the Vector2.
		std::string toString() const
		{
			return '<' + std::to_string(x) + ", " + std::to_string(y) + '>';
		}

		// Returns a std::wstring representation of the Vector2.
		std::wstring toWideString() const
		{
			return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L'>';
		}
	};

	// Converts the given Vector2 to another type of Vector2.
	template <std_arithmetic T, std_arithmetic U>
	Vector2<T> convert(const Vector2<U>& A)
	{
		T x = static_cast<T>(A.x);
		T y = static_cast<T>(A.y);

		return Vector2<T>(x, y);
	}

	// Returns the distance between the 2 given Vector2s.
	template <std_arithmetic T>
	float distance(const Vector2<T>& A, const Vector2<T>& B)
	{
		Vector2<T> C(A, B);
		return C.magnitude();
	}

	// Returns the horizontal distance between the 2 given Vector2s.
	template <std_arithmetic T>
	float distance_x(const Vector2<T>& A, const Vector2<T>& B)
	{
		float x = B.x - A.x;
		return x;
	}

	// Returns the vertical distance between the 2 given Vector2s.
	template <std_arithmetic T>
	float distance_y(const Vector2<T>& A, const Vector2<T>& B)
	{
		float y = B.y - A.y;
		return y;
	}

	// Returns the dot product of the 2 given Vector2s.
	template <std_arithmetic T>
	float dot_product(const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.x * B.x + A.y * B.y;
	}

	// Returns the scalar projection of A onto B.
	template <std_arithmetic T>
	float scalar_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) / A.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <std_arithmetic T>
	Vector2<float> vector_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		float f = (dot_product(A, B) / dot_product(A, A));
		return Vector2<float>(A.x * f, A.y * f);
	}

	// Returns the angle between the 2 given Vector2s.
	template <std_arithmetic T>
	Angle angle_between(const Vector2<T>& A, const Vector2<T>& B)
	{
		return arccosine(dot_product(A, B) / (A.magnitude() * B.magnitude()));
	}

	// Checks if the 2 given Vector2s are orthogonal to eachother.
	template <std_arithmetic T>
	bool are_normal(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) == 0.0f;
	}

	typedef jlib::Vector2<bool>   Vector2b;
	typedef jlib::Vector2<i8>     Vector2c;
	typedef jlib::Vector2<u8>     Vector2uc;
	typedef jlib::Vector2<i16>    Vector2s;
	typedef jlib::Vector2<u16>    Vector2us;
	typedef jlib::Vector2<i32>    Vector2i;
	typedef jlib::Vector2<u32>    Vector2u;
	typedef jlib::Vector2<float>  Vector2f;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return (A.x == B.x) && (A.y == B.y);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return (A.x != B.x) || (A.y != B.y);
}

// Overload of binary operator <
template <jlib::std_arithmetic T>
bool operator < (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return A.magnitude() < B.magnitude();
}

// Overload of binary operator <=
template <jlib::std_arithmetic T>
bool operator <= (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return A.magnitude() <= B.magnitude();
}

// Overload of binary operator >
template <jlib::std_arithmetic T>
bool operator > (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return A.magnitude() > B.magnitude();
}

// Overload of binary operator >=
template <jlib::std_arithmetic T>
bool operator >= (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return A.magnitude() >= B.magnitude();
}

// Overload of unary operator -
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator - (const jlib::Vector2<T>& A)
{
	return jlib::Vector2<T>(-A.x, -A.y);
}

// Overload of binary operator +
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator + (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return jlib::Vector2<T>(A.x + B.x, A.y + B.y);
}

// Overload of binary operator -
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator - (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return jlib::Vector2<T>(A.x - B.x, A.y - B.y);
}

// Overload of binary operator *
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator * (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return jlib::Vector2<T>(A.x * B.x, A.y * B.y);
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T> operator * (const jlib::Vector2<T>& A, U scalar)
{
	return jlib::Vector2<T>(A.x * scalar, A.y * scalar);
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T> operator * (U scalar, const jlib::Vector2<T>& A)
{
	return jlib::Vector2<T>(A.x * scalar, A.y * scalar);
}

// Overload of binary operator /
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator / (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	return jlib::Vector2<T>(A.x / B.x, A.y / B.y);
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T> operator / (const jlib::Vector2<T>& A, U scalar)
{
	return jlib::Vector2<T>(A.x / scalar, A.y / scalar);
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T> operator / (U scalar, const jlib::Vector2<T>& A)
{
	return jlib::Vector2<T>(scalar / A.x, scalar / A.y);
}

// Overload of binary operator +=
template <jlib::std_arithmetic T>
jlib::Vector2<T>& operator += (jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	A.x += B.x;
	A.y += B.y;

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T>
jlib::Vector2<T>& operator -= (jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
	A.x -= B.x;
	A.y -= B.y;

	return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T>& operator *= (jlib::Vector2<T>& A, U scalar)
{
	A.x *= scalar;
	A.y *= scalar;

	return A;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T>& operator /= (jlib::Vector2<T>& A, U scalar)
{
	A.x /= scalar;
	A.y /= scalar;

	return A;
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Vector2<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator <<
template <jlib::std_arithmetic T>
std::wostream& operator << (std::wostream& wos, const jlib::Vector2<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// VECTOR3 TEMPLATE CLASS                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors in 3-dimensional space.
	template <std_arithmetic T> class Vector3
	{
		public:

		T x;
		T y;
		T z;

		// Default constructor.
		// Sets the x component of the Vector3 to 0.
		// Sets the y component of the Vector3 to 0.
		// Sets the z component of the Vector3 to 0.
		Vector3()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			z = static_cast<T>(0);
		}

		// Constructs the Vector3 from the given coordinates.
		// Sets the x component of the Vector3 to new_x.
		// Sets the y component of the Vector3 to new_y.
		// Sets the z component of the Vector3 to new_z.
		Vector3(T new_x, T new_y, T new_z)
		{
			x = new_x;
			y = new_y;
			z = new_z;
		}

		// Constructs the Vector3 as the displacement vector of the two points.
		// Sets the x component of the Vector3 to B.x - A.x.
		// Sets the y component of the Vector3 to B.y - A.y.
		// Sets the z component of the Vector3 to B.z - A.z.
		Vector3(const Vector3<T>& A, const Vector3<T>& B)
		{
			x = B.x - A.x;
			y = B.y - A.y;
			z = B.z - A.z;
		}

		// Default copy constructor.
		Vector3(const Vector3& other) = default;

		// Default move constructor.
		Vector3(Vector3&& other) = default;

		// Constructs the Vector3 from another type of Vector3.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Vector3(const Vector3<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
		}

		// Default copy assignment operator.
		Vector3& operator = (const Vector3& other) = default;

		// Default move assignment operator.
		Vector3& operator = (Vector3&& other) = default;

		// Destructor.
		~Vector3() = default;

		// Sets all the values of the Vector3 at once.
		// Sets the x component of the Vector3 to new_x.
		// Sets the y component of the Vector3 to new_y.
		// Sets the z component of the Vector3 to new_z.
		void set(T new_x, T new_y, T new_z)
		{
			x = new_x;
			y = new_y;
			z = new_z;
		}

		// Copies the components of a different type of Vector2.
		template <jlib::std_arithmetic U>
		void copyFrom(const Vector3<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
		}

		// Returns the magnitude of the Vector3.
		constexpr float magnitude() const
		{
			return std::sqrtf(std::powf(static_cast<float>(x), 2.0f) + std::powf(static_cast<float>(y), 2.0f) + std::powf(static_cast<float>(z), 2.0f));
		}

		// Returns the unit vector of this Vector3.
		Vector3<float> unitVector() const
		{
			constexpr float m = magnitude();
			return Vector3<float>(x / m, y / m, z / m);
		}

		// Returns a std::string representation of the Vector3.
		std::string toString() const
		{
			return '<' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + '>';
		}

		// Returns a std::wstring representation of the Vector3.
		std::wstring toWideString() const
		{
			return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L", " + std::to_wstring(z) + L'>';
		}
	};

	// Converts the given Vector3 to another type of Vector3.
	template <std_arithmetic T, std_arithmetic U>
	Vector3<T> convert(const Vector3<U>& A)
	{
		T x = static_cast<T>(A.x);
		T y = static_cast<T>(A.y);
		T z = static_cast<T>(A.z);

		return Vector3<T>(x, y, z);
	}

	// Returns the distance between the 2 given Vector3s.
	template <std_arithmetic T>
	float distance(const Vector3<T>& A, const Vector3<T>& B)
	{
		Vector3<T> C(A, B);
		return C.magnitude();
	}

	// Returns the x-distance between the 2 given Vector3s.
	template <std_arithmetic T>
	float distance_x(const Vector3<T>& A, const Vector3<T>& B)
	{
		float x = B.x - A.x;
		return x;
	}

	// Returns the y-distance between the 2 given Vector3s.
	template <std_arithmetic T>
	float distance_y(const Vector3<T>& A, const Vector3<T>& B)
	{
		float y = B.y - A.y;
		return y;
	}

	// Returns the z-distance between the 2 given Vector3s.
	template <std_arithmetic T>
	float distance_z(const Vector3<T>& A, const Vector3<T>& B)
	{
		float z = B.z - A.z;
		return z;
	}

	// Returns the dot product of the 2 given Vector3s.
	template <std_arithmetic T>
	float dot_product(const Vector3<T>& A, const Vector3<T>& B)
	{
		return A.x * B.x + A.y * B.y + A.z * B.z;
	}

	// Returns the cross product of the 2 given Vector3s.
	template <jlib::std_arithmetic T>
	jlib::Vector3<T> cross_product(const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(A.y * B.z - A.z * B.y, -(A.x * B.z - A.z * B.x), A.x * B.y - A.y * B.x);
	}

	// Returns the scalar projection of A onto B.
	template <std_arithmetic T>
	float scalar_proj(const Vector3<T>& A, const Vector3<T>& B)
	{
		return dot_product(A, B) / A.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <std_arithmetic T>
	Vector3<float> vector_proj(const Vector3<T>& A, const Vector3<T>& B)
	{
		float f = (dot_product(A, B) / dot_product(A, A));
		return Vector3<float>(A.x * f, A.y * f, A.z * f);
	}

	// Determines if the 2 given Vector3s are orthogonal to eachother.
	template <std_arithmetic T>
	bool are_normal(const Vector3<T>& A, const Vector3<T>& B)
	{
		return dot_product(A, B) == 0.f;
	}

	typedef jlib::Vector3<bool>   Vector3b;
	typedef jlib::Vector3<i8>     Vector3c;
	typedef jlib::Vector3<u8>     Vector3uc;
	typedef jlib::Vector3<i16>    Vector3s;
	typedef jlib::Vector3<u16>    Vector3us;
	typedef jlib::Vector3<i32>    Vector3i;
	typedef jlib::Vector3<u32>    Vector3u;
	typedef jlib::Vector3<float>  Vector3f;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.z != B.z);
}

// Overload of binary operator <
template <jlib::std_arithmetic T>
bool operator < (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return A.magnitude() < B.magnitude();
}

// Overload of binary operator <=
template <jlib::std_arithmetic T>
bool operator <= (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return A.magnitude() <= B.magnitude();
}

// Overload of binary operator >
template <jlib::std_arithmetic T>
bool operator > (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return A.magnitude() > B.magnitude();
}

// Overload of binary operator >=
template <jlib::std_arithmetic T>
bool operator >= (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return A.magnitude() >= B.magnitude();
}

// Overload of unary operator -
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator - (const jlib::Vector3<T>& A)
{
	return jlib::Vector3<T>(-A.x, -A.y, -A.z);
}

// Overload of binary operator +
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator + (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return jlib::Vector3<T>(A.x + B.x, A.y + B.y, A.z + B.z);
}

// Overload of binary operator -
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator - (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return jlib::Vector3<T>(A.x - B.x, A.y - B.y, A.z - B.z);
}

// Overload of binary operator *
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator * (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return jlib::Vector3<T>(A.x * B.x, A.y * B.y, A.z * B.z);
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T> operator * (const jlib::Vector3<T>& A, U scalar)
{
	return jlib::Vector3<T>(A.x * scalar, A.y * scalar, A.z * scalar);
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T> operator * (U scalar, const jlib::Vector3<T>& A)
{
	return jlib::Vector3<T>(A.x * scalar, A.y * scalar, A.z * scalar);
}

// Overload of binary operator /
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator / (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	return jlib::Vector3<T>(A.x / B.x, A.y / B.y, A.z / B.z);
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T> operator / (const jlib::Vector3<T>& A, U scalar)
{
	return jlib::Vector3<T>(A.x / scalar, A.y / scalar, A.z / scalar);
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T> operator / (U scalar, const jlib::Vector3<T>& A)
{
	return jlib::Vector3<T>(scalar / A.x, scalar / A.y, scalar / A.z);
}

// Overload of binary operator +=
template <jlib::std_arithmetic T>
jlib::Vector3<T>& operator += (jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	A.x += B.x;
	A.y += B.y;
	A.z += B.z;

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T>
jlib::Vector3<T>& operator -= (jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
	A.x -= B.x;
	A.y -= B.y;
	A.z -= B.z;

	return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T>& operator *= (jlib::Vector3<T>& A, U scalar)
{
	A.x *= scalar;
	A.y *= scalar;
	A.z *= scalar;

	return A;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T>& operator /= (jlib::Vector3<T>& A, U scalar)
{
	A.x /= scalar;
	A.y /= scalar;
	A.z /= scalar;

	return A;
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Vector3<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator <<
template <jlib::std_arithmetic T>
std::wostream& operator << (std::wostream& wos, const jlib::Vector3<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// VECTORN TEMPLATE CLASS                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors with N-dimensions.
	template <std_arithmetic T, std::size_t N> class VectorN
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = const std::reverse_iterator<iterator>;

		private:

		FixedArray<T, N> _data;

		public:

		// Default constructor.
		// Sets each component of the VectorN to 0.
		VectorN()
		{
			for (size_type i = 0; i < N; ++i)
				_data[i] = static_cast<T>(0);
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

		// Constructs the VectorN from another type of VectorN.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		VectorN(const VectorN<U, N>& other)
		{
			for (size_type i(0); i < N; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Constructs the VectorN from the given coordinates.
		VectorN& operator = (std::initializer_list<T> elems)
		{
			std::copy(elems.begin(), elems.end(), _data.data());
			return *this;
		}

		// Copies the components of a different type of JVector2.
		template <jlib::std_arithmetic U>
		void copyFrom(const VectorN<U, N>& other)
		{
			std::copy(other._data, other._data + N, _data);
		}

		// Returns the amount of dimensions the VectorN has.
		size_type dimensions() const
		{
			return N;
		}

		// Returns the first element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		reference first()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return _data[0];
		}

		// Returns the first element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		const_reference first() const
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return _data[0];
		}

		// Returns the last element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		reference last()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return _data[N - 1];
		}

		// Returns the last element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		const_reference last() const
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return _data[N - 1];
		}

		// Returns the pointer to the elements of the VectorN.
		pointer data()
		{
			return _data.data();
		}

		// Returns the pointer to the elements of the VectorN.
		const_pointer data() const
		{
			return _data.data();
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		iterator begin()
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator begin() const
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator cbegin() const
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		reverse_iterator rbegin()
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator rbegin() const
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator crbegin() const
		{
			return _data;
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		iterator end()
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator end() const
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator cend() const
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		reverse_iterator rend()
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator rend() const
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator crend() const
		{
			return _data + N;
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid PointN index.");
			return _data[index];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type index) const
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid PointN index.");
			return _data[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type index, const_reference value)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid PointN index.");
			_data[index] = value;
		}

		// Returns the magnitude of the VectorN.
		float magnitude() const
		{
			float value = 0.0f;

			for (size_type i = 0; i < N; ++i)
				value += std::powf(data[i], 2);

			return std::sqrtf(value);
		}

		// Returns a std::string representation of the VectorN.
		std::string toString() const
		{
			if (N == 0)
				return "";
			if (N == 1)
				return '<' + std::to_string(_data[0]) + '>';

			std::string str;

			str += '<';
			for (size_type i = 0; i < N - 1; ++i)
				str += std::to_string(_data[i]) + ", ";
			str += std::to_string(_data[N - 1]) + '>';

			return str;
		}

		// Returns a std::wstring representation of the VectorN.
		std::wstring toWideString() const
		{
			if (N == 0)
				return L"";
			if (N == 1)
				return L'<' + std::to_wstring(_data[0]) + L'>';

			std::wstring str;

			str += L'<';
			for (size_type i = 0; i < N - 1; ++i)
				str += std::to_wstring(_data[i]) + L", ";
			str += std::to_wstring(_data[N - 1]) + L'>';

			return str;
		}

		// Returns the element at the given index.
		reference operator [] (size_type index)
		{
			return _data[index];
		}

		// Returns the element at the given index.
		const_reference operator [] (size_type index) const
		{
			return _data[index];
		}
	};

	// Returns the distance between the 2 given JVectorNs.
	template <std_arithmetic T, std::size_t N>
	float distance(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> C(A, B);
		return C.magnitude();
	}

	// Returns a unit vector in the direction of the VectorN.
	template <std_arithmetic T, std::size_t N>
	VectorN<float, N> unit_vector(const VectorN<T, N>& A)
	{
		return VectorN<T, N>(A) / A.magnitude();
	}

	// Returns the dot product of the 2 given JVectorNs.
	template <std_arithmetic T, std::size_t N>
	float dot_product(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float value = 0.0f;

		for (std::size_t i(0); i < N; ++i)
			value += (A[i] * B[i]);

		return value;
	}

	// Returns the scalar projection of A onto B.
	template <std_arithmetic T, std::size_t N>
	float scalar_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return dot_product(A, B) / A.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <std_arithmetic T, std::size_t N>
	VectorN<float, N> vector_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float f = (dot_product(A, B) / dot_product(A, A));
		VectorN<float, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] *= f;

		return V;
	}

	typedef jlib::VectorN<bool, 4>   JVector4b;
	typedef jlib::VectorN<i8, 4>     JVector4c;
	typedef jlib::VectorN<u8, 4>     JVector4uc;
	typedef jlib::VectorN<i16, 4>    JVector4s;
	typedef jlib::VectorN<u16, 4>    JVector4us;
	typedef jlib::VectorN<i32, 4>    JVector4i;
	typedef jlib::VectorN<u32, 4>    JVector4u;
	typedef jlib::VectorN<float, 4>  JVector4f;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T, std::size_t N>
bool operator == (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	for (std::size_t i = 0; i < N; ++i)
	{
		if (A[i] != B[i])
			return false;
	}

	return true;
}

// Overload of binary operator !=
template <jlib::std_arithmetic T, std::size_t N>
bool operator != (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	for (std::size_t i = 0; i < N; ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

// Overload of binary operator <
template <jlib::std_arithmetic T, std::size_t N>
bool operator < (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.magnitude() < B.magnitude();
}

// Overload of binary operator <=
template <jlib::std_arithmetic T, std::size_t N>
bool operator <= (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.magnitude() <= B.magnitude();
}

// Overload of binary operator >
template <jlib::std_arithmetic T, std::size_t N>
bool operator > (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.magnitude() > B.magnitude();
}

// Overload of binary operator >=
template <jlib::std_arithmetic T, std::size_t N>
bool operator >= (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.magnitude() >= B.magnitude();
}

// Overload of unary operator -
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator - (const jlib::VectorN<T, N>& A)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] * -1;

	return V;
}

// Overload of binary operator +
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator + (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] + B[i];

	return V;
}

// Overload of binary operator -
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator - (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] - B[i];

	return V;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator * (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] * B[i];

	return V;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N> operator * (const jlib::VectorN<T, N>& A, U scalar)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] * scalar;

	return V;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N> operator * (U scalar, const jlib::VectorN<T, N>& A)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] * scalar;

	return V;
}

// Overload of binary operator /
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator / (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] / B[i];

	return V;
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N> operator / (const jlib::VectorN<T, N>& A, U scalar)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] / scalar;

	return V;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N> operator / (U scalar, const jlib::VectorN<T, N>& A)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = scalar / A[i];

	return V;
}

// Overload of binary operator +=
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N>& operator += (jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] += B[i];

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N>& operator -= (jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] -= B[i];

	return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N>& operator *= (jlib::VectorN<T, N>& A, U scalar)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] *= scalar;

	return A;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N>& operator /= (jlib::VectorN<T, N>& A, U scalar)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] /= scalar;

	return A;
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T, std::size_t N>
std::ostream& operator << (std::ostream& os, const jlib::VectorN<T, N>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator <<
template <jlib::std_arithmetic T, std::size_t N>
std::wostream& operator << (std::wostream& wos, const jlib::VectorN<T, N>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// RECT TEMPLATE CLASS                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std_arithmetic T> class Rect
	{
		public:

		T x;
		T y;
		T w;
		T h;

		// Default constructor.
		// Sets the x component of the vertex of the Rect to 0.
		// Sets the y component of the vertex of the Rect to 0.
		// Sets the width of the Rect to 0.
		// Sets the height of the Rect to 0.
		Rect()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			w = static_cast<T>(0);
			h = static_cast<T>(0);
		}

		// 4-parameter constructor.
		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		Rect(T new_x, T new_y, T new_w, T new_h)
		{
			x = new_x;
			y = new_y;
			w = new_w;
			h = new_h;
		}

		// Single Vector2 constructor.
		// Sets the vertex of the Rect to the given point.
		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		Rect(const Vector2<T>& vertex, T new_w, T new_h)
		{
			x = vertex.x;
			y = vertex.y;
			w = new_w;
			h = new_h;
		}

		// Double Vector2 constructor.
		// Sets the vertex of the Rect to the given point.
		// Sets the dimensions of the Rect to the given dimensions.
		Rect(const Vector2<T>& vertex, const Vector2<T>& dimensions)
		{
			x = vertex.x;
			y = vertex.y;
			w = dimensions.x;
			h = dimensions.y;
		}

		// Default copy constructor.
		Rect(const Rect& other) = default;

		// Default move constructor.
		Rect(Rect&& other) = default;

		// Constructs the Rect from another type of Rect.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Rect(const Rect<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			w = static_cast<T>(other.w);
			h = static_cast<T>(other.h);
		}

		// Default copy assignment operator.
		Rect& operator = (const Rect& other) = default;

		// Default move assignment operator.
		Rect& operator = (Rect&& other) = default;

		// Destructor.
		~Rect() = default;

		// Sets all the values of the Rect at once.
		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		void set(T new_x, T new_y, T new_w, T new_h)
		{
			x = new_x;
			y = new_y;
			w = new_w;
			h = new_h;
		}

		// Sets the x component of the vertex of the Rect to new_x.
		// Sets the y component of the vertex of the Rect to new_y.
		void setVertex(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Sets the vertex of the Rect to the given point.
		void setVertex(const Vector2<T>& vertex)
		{
			x = vertex.x;
			y = vertex.y;
		}

		// Sets the width of the Rect to new_w.
		// Sets the height of the Rect to new_h.
		void setDimensions(T new_w, T new_h)
		{
			w = new_w;
			h = new_h;
		}

		// Sets the dimensions of the Rect to the given dimensions.
		void setDimensions(const Vector2<T>& dimensions)
		{
			w = dimensions.x;
			h = dimensions.y;
		}

		// Returns the perimeter of the Rect.
		float perimeter() const
		{
			return 2.0f * (w + h);
		}

		// Returns the area of the Rect.
		float area() const
		{
			return w * h;
		}

		// Returns the top-left vertex of the Rect.
		Vector2<T> topLeft() const
		{
			return Vector2<T>(std::min(x, x + w), std::min(y, y + h));
		}

		// Returns the top-right vertex of the Rect.
		Vector2<T> topRight() const
		{
			return Vector2<T>(std::max(x, x + w), std::min(y, y + h));
		}

		// Returns the bottom-left vertex of the Rect.
		Vector2<T> bottomLeft() const
		{
			return Vector2<T>(std::min(x, x + w), std::max(y, y + h));
		}

		// Returns the bottom-right vertex of the Rect.
		Vector2<T> bottomRight() const
		{
			return Vector2<T>(std::max(x, x + w), std::max(y, y + h));
		}

		// Returns the dimensions of the Rect.
		Vector2<T> dimensions() const
		{
			return Vector2<T>(w, h);
		}

		// Returns a FixedArray containing the vertices of the Rect.
		FixedArray<Vector2<T>, 4> getVertices() const
		{
			FixedArray<Vector2<T>, 4> arr;

			arr[0] = topLeft();
			arr[1] = topRight();
			arr[2] = bottomLeft();
			arr[3] = bottomRight();

			return arr;
		}

		// Checks if the given point lies within or on the Rect.
		template <std_arithmetic U>
		bool contains(U X, U Y)
		{
			T minX = std::min(x, static_cast<T>(x + w));
			T maxX = std::max(x, static_cast<T>(x + w));
			T minY = std::min(y, static_cast<T>(y + h));
			T maxY = std::max(y, static_cast<T>(y + h));

			return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
		}

		// Checks if the given point lies within or on the Rect.
		template <std_arithmetic U>
		bool contains(const Vector2<U>& point)
		{
			return contains(point.x, point.y);
		}

		// Returns a std::string representation of the Rect.
		std::string toString() const
		{
			return Vector2<T>(x, y).toString() + ", [" + std::to_string(w) + " x " + std::to_string(h) + ']';
		}

		// Returns a std::wstring representation of the Rect.
		std::wstring toWideString() const
		{
			return Vector2<T>(x, y).toWideString() + L", [" + std::to_wstring(w) + L" x " + std::to_wstring(h) + L']';
		}
	};

	// Checks if there is an intersection between the given Rects.
	template <std_arithmetic T>
	bool intersection(const Rect<T>& A, const Rect<T>& B)
	{
		Vector2<T> ATL(A.topLeft());
		Vector2<T> BTL(B.topLeft());
		Vector2<T> ABR(A.bottomRight());
		Vector2<T> BBR(B.bottomRight());

		if ((ABR.x < BTL.x) || (ABR.y < BTL.y) || (BBR.x < ATL.x) || (BBR.y < ATL.y))
			return false;
		return true;
	}

	typedef jlib::Rect<i32>       IntRect;
	typedef jlib::Rect<u32>       UIntRect;
	typedef jlib::Rect<float>     FloatRect;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Rect<T>& A, const jlib::Rect<T>& B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.w == B.w) && (A.h == B.h);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Rect<T>& A, const jlib::Rect<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.w != B.w) || (A.h != B.h);
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Rect<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator <<
template <jlib::std_arithmetic T>
std::wostream& operator << (std::wostream& wos, const jlib::Rect<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// SQUARE TEMPLATE CLASS                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std_arithmetic T> class Square
	{
		public:

		T x;
		T y;
		T l;

		// Default constructor.
		// Sets the x component of the vertex of the Square to 0.
		// Sets the y component of the vertex of the Square to 0.
		// Sets the length of the Square to 0.
		Square()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			l = static_cast<T>(0);
		}

		// 3-parameter constructor.
		// Sets the x component of the vertex of the Square to new_x.
		// Sets the y component of the vertex of the Square to new_y.
		// Sets the length of the Square to new_l.
		Square(T new_x, T new_y, T new_l)
		{
			x = new_x;
			y = new_y;
			l = new_l;
		}

		// Single Vector2 constructor.
		// Sets the vertex of the Square to the given point.
		// Sets the length of the Square to new_l.
		Square(const Vector2<T>& vertex, T new_l)
		{
			x = vertex.x;
			y = vertex.y;
			l = new_l;
		}

		// Default copy constructor.
		Square(const Square& other) = default;

		// Default move constructor.
		Square(Square&& other) = default;

		// Constructs the Square from another type of Square.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Square(const Square<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			l = static_cast<T>(other.l);
		}

		// Default copy assignment operator.
		Square& operator = (const Square& other) = default;

		// Default move assignment operator.
		Square& operator = (Square&& other) = default;

		// Destructor.
		~Square() = default;

		// Sets all the values of the Square at once.
		// Sets the x component of the vertex of the Square to new_x.
		// Sets the y component of the vertex of the Square to new_y.
		// Sets the length of the Square to new_l.
		void set(T new_x, T new_y, T new_l)
		{
			x = new_x;
			y = new_y;
			l = new_l;
		}

		// Sets the x component of the vertex of the Square to new_x.
		// Sets the y component of the vertex of the Square to new_y.
		void setVertex(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Sets the vertex of the Square to the given point.
		void setVertex(const Vector2<T>& vertex)
		{
			x = vertex.x;
			y = vertex.y;
		}

		// Returns the perimeter of the Square.
		float perimeter() const
		{
			return 4.0f * l;
		}

		// Returns the area of the Square.
		float area() const
		{
			return l * l;
		}

		// Returns the top-left vertex of the Square.
		Vector2<T> topLeft() const
		{
			return Vector2<T>(std::min(x, x + l), std::min(y, y + l));
		}

		// Returns the top-right vertex of the Square.
		Vector2<T> topRight() const
		{
			return Vector2<T>(std::max(x, x + l), std::min(y, y + l));
		}

		// Returns the bottom-left vertex of the Square.
		Vector2<T> bottomLeft() const
		{
			return Vector2<T>(std::min(x, x + l), std::max(y, y + l));
		}

		// Returns the bottom-right vertex of the Square.
		Vector2<T> bottomRight() const
		{
			return Vector2<T>(std::max(x, x + l), std::max(y, y + l));
		}

		// Returns a FixedArray containing the vertices of the Square.
		FixedArray<Vector2<T>, 4> getVertices() const
		{
			FixedArray<Vector2<T>, 4> arr;

			arr[0] = topLeft();
			arr[1] = topRight();
			arr[2] = bottomLeft();
			arr[3] = bottomRight();

			return arr;
		}

		// Checks if the given point lies within or on the Square.
		template <std_arithmetic U>
		bool contains(U X, U Y)
		{
			T minX = std::min(x, static_cast<T>(x + l));
			T maxX = std::max(x, static_cast<T>(x + l));
			T minY = std::min(y, static_cast<T>(y + l));
			T maxY = std::max(y, static_cast<T>(y + l));

			return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
		}

		// Checks if the given point lies within or on the Square.
		template <std_arithmetic U>
		bool contains(const Vector2<U>& point)
		{
			return contains(point.x, point.y);
		}

		// Returns a std::string representation of the Square.
		std::string toString() const
		{
			return Vector2<T>(x, y).toString() + ", [" + std::to_string(l) + " x " + std::to_string(l) + ']';
		}

		// Returns a std::wstring representation of the Square.
		std::wstring toWideString() const
		{
			return Vector2<T>(x, y).toWideString() + L", [" + std::to_wstring(l) + L" x " + std::to_wstring(l) + L']';
		}

		#ifdef SFML_SYSTEM_WINDOWS

		sf::Rect<T> toSFML() const
		{
			return sf::Rect<T>(x, y, l, l);
		}

		#endif // #ifdef SFML_SYSTEM_WINDOWS
	};

	// Checks if there is an intersection between the given Squares.
	template <std_arithmetic T>
	bool intersection(const Square<T>& A, const Square<T>& B)
	{
		Vector2<T> ATL(A.topLeft());
		Vector2<T> BTL(B.topLeft());
		Vector2<T> ABR(A.bottomRight());
		Vector2<T> BBR(B.bottomRight());

		if ((ABR.x < BTL.x) || (ABR.y < BTL.y) || (BBR.x < ATL.x) || (BBR.y < ATL.y))
			return false;
		return true;
	}

	typedef jlib::Square<i32>       IntSquare;
	typedef jlib::Square<u32>       UIntSquare;
	typedef jlib::Square<float>     FloatSquare;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Square<T>& A, const jlib::Square<T>& B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.l == B.l);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Square<T>& A, const jlib::Square<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.l != B.l);
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Square<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator <<
template <jlib::std_arithmetic T>
std::wostream& operator << (std::wostream& wos, const jlib::Square<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CIRCLE TEMPLATE CLASS                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std_arithmetic T> class Circle
	{
		public:

		T x;
		T y;
		T r;

		// Default constructor.
		// Sets the x component of the center of the Circle to 0.
		// Sets the y component of the center of the Circle to 0.
		// Sets the radius of the Circle to 0.
		Circle()
		{
			r = static_cast<T>(0);
		}

		// 3-parameter constructor.
		// Sets the x component of the center of the Circle to new_x.
		// Sets the y component of the center of the Circle to new_y.
		// Sets the radius of the Circle to new_r.
		Circle(T new_x, T new_y, T new_r)
		{
			x = new_x;
			y = new_y;
			r = new_r;
		}

		// Point constructor.
		// Sets the center of the Circle to the given point.
		// Sets the radius of the Circle to new_r.
		Circle(const Vector2<T>& center, T new_r)
		{
			x = center.x;
			y = center.y;
			r = new_r;
		}

		// Constructs the Circle from another type of Circle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Circle(const Circle<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			r = static_cast<T>(other.r);
		}

		// Sets all the values of the Circle at once.
		// Sets the x component of the center of the Circle to new_x.
		// Sets the y component of the center of the Circle to new_y.
		// Sets the radius of the Circle to new_r.
		void set(T new_x, T new_y, T new_r)
		{
			x = new_x;
			y = new_y;
			r = new_r;
		}

		// Sets all the values of the Circle at once.
		// Sets the center of the Circle to the given point.
		// Sets the radius of the Circle to new_r.
		void set(const Vector2<T>& center, T new_r)
		{
			x = center.x;
			y = center.y;
			r = new_r;
		}

		// Returns the circumference of the Circle.
		float circumference() const
		{
			return JLIB_2PI * std::fabsf(r);
		}

		// Returns the area of the Circle.
		float area() const
		{
			return JLIB_PI * std::powf(std::fabsf(r), 2.0f);
		}

		// Checks if the given point lies within or on the Circle.
		template <std_arithmetic U>
		bool contains(T X, T Y)
		{
			return std::powf(X - x, 2.f) + std::powf(Y - y, 2.0f) <= std::powf(std::fabsf(r), 2.0f);
		}

		// Checks if the given point lies within or on the Circle.
		template <std_arithmetic U>
		bool contains(const Vector2<U>& P)
		{
			return std::powf(P.x - x, 2.0f) + std::powf(P.y - y, 2.0f) <= std::powf(std::fabsf(r), 2.0f);
		}

		// Returns a std::string representation of the Circle.
		std::string toString() const
		{
			return Vector2<T>(x, y).toString() + " @ " + std::to_string(std::fabsf(r));
		}

		// Returns a std::wstring representation of the Circle.
		std::wstring toWideString() const
		{
			return Vector2<T>(x, y).toWideString() + L" @ " + std::to_wstring(std::fabsf(r));
		}
	};

	// Checks if there is an intersection between the given Circles.
	template <std_arithmetic T>
	bool intersection(const Circle<T>& A, const Circle<T>& B)
	{
		return std::powf(std::fabsf(A.r) + std::fabsf(B.r), 2.0f) <= (std::powf(B.x - A.x, 2.0f) + std::powf(B.y - A.y, 2.0f));
	}
}

// Overload of binary operator == 
template <jlib::std_arithmetic T>
bool operator == (const jlib::Circle<T>& A, const jlib::Circle<T>& B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.r == B.r);
}

// Overload of binary operator != 
template <jlib::std_arithmetic T>
bool operator != (const jlib::Circle<T>& A, const jlib::Circle<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.r != B.r);
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Circle<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator <<
template <jlib::std_arithmetic T>
std::wostream& operator << (std::wostream& wos, const jlib::Circle<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std_arithmetic T> class Triangle
	{
		public:

		Vector2<T> A;
		Vector2<T> B;
		Vector2<T> C;

		// Default constructor.
		// Sets each vertex of the Triangle to (0, 0).
		Triangle() = default;

		// Sets the A vertex to the point given by (Ax, Ay).
		// Sets the B vertex to the point given by (Bx, By).
		// Sets the C vertex to the point given by (Cx, Cy).
		Triangle(T Ax, T Ay, T Bx, T By, T Cx, T Cy)
		{
			A = Vector2<T>(Ax, Ay);
			B = Vector2<T>(Bx, By);
			C = Vector2<T>(Cx, Cy);
		}

		// Sets the A vertex to the point given by a.
		// Sets the B vertex to the point given by b.
		// Sets the C vertex to the point given by c.
		Triangle(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c)
		{
			A = a;
			B = b;
			C = c;
		}

		// Constructs the Triangle from another type of Triangle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Triangle(const Triangle<U>& other)
		{
			A.x = static_cast<T>(other.A.x);
			A.y = static_cast<T>(other.A.y);
			B.x = static_cast<T>(other.B.x);
			B.y = static_cast<T>(other.B.y);
			C.x = static_cast<T>(other.C.x);
			C.y = static_cast<T>(other.C.y);
		}

		// Sets all the values of the Triangle at once.
		// Sets the A vertex to the point given by (Ax, Ay).
		// Sets the B vertex to the point given by (Bx, By).
		// Sets the C vertex to the point given by (Cx, Cy).
		void set(T Ax, T Ay, T Bx, T By, T Cx, T Cy)
		{
			A = Vector2<T>(Ax, Ay);
			B = Vector2<T>(Bx, By);
			C = Vector2<T>(Cx, Cy);
		}

		// Sets all the values of the Triangle at once.
		// Sets the A vertex to the point given by a.
		// Sets the B vertex to the point given by b.
		// Sets the C vertex to the point given by c.
		void set(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c)
		{
			A = a;
			B = b;
			C = c;
		}

		// Returns a std::string representation of the Triangle.
		std::string toString() const
		{
			return "A: " + A.toString() + ", B: " + B.toString() + ", C: " + C.toString();
		}

		// Returns a std::wstring representation of the Triangle.
		std::wstring toWideString() const
		{
			return L"A: " + A.toWideString() + L", B: " + B.toWideString() + L", C: " + C.toWideString();
		}
	};
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Triangle<T>& T1, const jlib::Triangle<T>& T2)
{
	return (T1.A == T2.A) && (T1.B == T2.B) && (T1.C == T2.C);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Triangle<T>& T1, const jlib::Triangle<T>& T2)
{
	return (T1.A != T2.A) || (T1.B != T2.B) || (T1.C != T2.C);
}

// Overload of std::ostream operator << 
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Triangle<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator << 
template <jlib::std_arithmetic T>
std::wostream& operator << (std::wostream& wos, const jlib::Triangle<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std_arithmetic T> class LineSegment
	{
		public:

		Vector2<T> start;
		Vector2<T> end;

		// 
		LineSegment() = default;

		// 
		LineSegment(T Ax, T Ay, T Bx, T By)
		{
			start.set(Ax, Ay);
			end.set(Bx, By);
		}

		// 
		LineSegment(const Vector2<T>& A, const Vector2<T>& B)
		{
			start = A;
			end = B;
		}

		//
		template <std_arithmetic U>
		LineSegment(const LineSegment<U>& other)
		{
			start = static_cast<Vector2<T>>(other.start);
			end = static_cast<Vector2<T>>(other.end);
		}

		// 
		LineSegment(std::initializer_list<T> list)
		{
			start.set(*(list.begin() + 0), *(list.begin() + 1));
			end.set(*(list.begin() + 2), *(list.begin() + 3));
		}

		// 
		LineSegment& operator = (std::initializer_list<T> list)
		{
			start.set(*(list.begin() + 0), *(list.begin() + 1));
			end.set(*(list.begin() + 2), *(list.begin() + 3));

			return *this;
		}

		// 
		void set(T Ax, T Ay, T Bx, T By)
		{
			start.set(Ax, Ay);
			end.set(Bx, By);
		}

		// 
		Vector2<T> displacementVector() const
		{
			return Vector2<T>(start, end);
		}

		// 
		std::string toString() const
		{
			return start.toString() + " -> " + end.toString();
		}

		// 
		std::wstring toWideString() const
		{
			return start.toWideString() + L" -> " + end.toWideString();
		}
	};
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::LineSegment<T>& A, const jlib::LineSegment<T>& B)
{
	return (A.start == B.start) && (A.end == B.end);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::LineSegment<T>& A, const jlib::LineSegment<T>& B)
{
	return (A.start != B.start) || (A.end != B.end);
}

// Overload of std::ostream operator << 
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::LineSegment<T>& A)
{
	os << A.toString();
	return os;
}

// Overload of std::wostream operator << 
template <jlib::std_arithmetic T>
std::wostream& operator << (std::wostream& wos, const jlib::LineSegment<T>& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// MATRIX TEMPLATE CLASS                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A Matrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <typename T> class Matrix
	{
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = Array<T>::iterator;
		using const_iterator = Array<T>::const_iterator;
		using reverse_iterator = Array<T>::reverse_iterator;
		using const_reverse_iterator = Array<T>::const_reverse_iterator;

		private:

		Array<T> _data;
		size_type _rows;
		size_type _cols;

		// 
		void allocate(size_type rows, size_type cols)
		{
			if (rows != 0 && cols != 0)
			{
				_rows = rows;
				_cols = cols;

				_data = Array<T>(_rows * _cols);
			}
			else
			{
				_rows = 0;
				_cols = 0;
			}
		}

		// 
		void reallocate(size_type rows, size_type cols)
		{
			Array<T> newarr(rows * cols);
			size_type size = std::min(_data.size(), newarr.size());
			std::copy(newarr.begin(), newarr.end(), _data.begin());
			_data = std::move(newarr);
		}

		public:

		// Default constructor.
		Matrix()
		{
			allocate(0, 0);
		}

		// Size constructor.
		Matrix(size_type rows, size_type cols)
		{
			allocate(rows, cols);
		}

		// Size and value constructor.
		// Sets every element of the Matrix to value.
		Matrix(size_type rows, size_type cols, const_reference value)
		{
			allocate(rows, cols);

			for (size_type i = 0; i < _rows * _cols; ++i)
				_data[i] = value;
		}

		// 2-dimensional std::initializer_list constructor.
		Matrix(std::initializer_list<std::initializer_list<T>> list)
		{
			auto iter = list.begin();
			size_type cols = 0;

			while (iter != list.end())
			{
				if (cols < iter->size())
					cols = iter->size();

				++iter;
			}

			allocate(list.size(), cols);
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + _cols, &(_data[row_i * _cols]));
				++row_i;
			}
		}

		// Copy constructor.
		Matrix(const Matrix& other) = default;

		// Constructs the Matrix from another type of Matrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <typename U>
		explicit Matrix(const Matrix<U>& other)
		{
			allocate(other._rows, other._cols);

			for (size_type i = 0; i < _rows * _cols; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Move constructor.
		Matrix(Matrix&& other) = default;

		// 2-dimensional std::initializer_list assignment operator.
		Matrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			auto iter = list.begin();
			size_type cols = 0;

			while (iter != list.end())
			{
				if (cols < iter->size())
					cols = iter->size();

				++iter;
			}

			allocate(list.size(), cols);
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + _cols, &(_data[row_i * _cols]));
				++row_i;
			}

			return *this;
		}

		// Copy assignment operator.
		Matrix& operator = (const Matrix& other) = default;

		// Move assignment operator.
		Matrix& operator = (Matrix&& other) = default;

		// Destructor.
		~Matrix() = default;

		// Returns the number of rows in the Matrix.
		size_type rowCount() const noexcept
		{
			return _rows;
		}

		// Returns the number of columns in the Matrix.
		size_type colCount() const noexcept
		{
			return _cols;
		}

		// Returns the number of elements in the Matrix.
		size_type size() const noexcept
		{
			return _data.size();
		}

		// 
		pointer data() noexcept
		{
			return _data.data();
		}

		// 
		const_pointer data() const noexcept
		{
			return _data.data();
		}

		// 
		iterator begin() noexcept
		{
			return _data.begin();
		}

		// 
		const_iterator begin() const noexcept
		{
			return _data.cbegin();
		}

		// 
		const_iterator cbegin() const noexcept
		{
			return _data.cbegin();
		}

		// 
		iterator end() noexcept
		{
			return _data.end();
		}

		// 
		const_iterator end() const noexcept
		{
			return _data.cend();
		}

		// 
		const_iterator cend() const noexcept
		{
			return _data.cend();
		}

		// 
		iterator rowBegin(size_type row) noexcept
		{
			return _data.begin() + (_cols * row);
		}

		// 
		const_iterator rowBegin(size_type row) const noexcept
		{
			return _data.cbegin() + (_cols * row);
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		reference at(size_type n)
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid Matrix index.");
			return _data[n];
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		const_reference at(size_type n) const
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid Matrix index.");
			return _data[n];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		reference at(size_type row, size_type col)
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(row * _cols) + col];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		const_reference at(size_type row, size_type col) const
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(row * _cols) + col];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		template <std_arithmetic U>
		reference at(const Vector2<std::size_t>& pos)
		{
			if (pos.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (pos.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		template <std_arithmetic U>
		reference at(const Vector2<U>& pos)
		{
			if (static_cast<size_t>(pos.y) >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (static_cast<size_t>(pos.x) >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		const_reference at(const Vector2<size_type>& pos) const
		{
			if (pos.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (pos.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		template <std_arithmetic U>
		const_reference at(const Vector2<U>& pos) const
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));

			if (v.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (v.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(v.y * _cols) + v.x];
		}

		// Sets the nth element of the Matrix to value.
		// Performs bounds-checking.
		void set(size_type n, const_reference value)
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid table index.");
			_data[n] = value;
		}

		// Sets the element at [row][col] to value.
		// Performs bounds-checking.
		void set(size_type row, size_type col, const_reference value)
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			_data[(row * _cols) + col] = value;
		}

		// Sets the element at [pos.y][pos.x] to value.
		// Performs bounds-checking.
		void set(const Vector2<size_type>& pos, const_reference value)
		{
			if (pos.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (pos.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			_data[(pos.y * _cols) + pos.x] = value;
		}

		// Sets the element at [pos.y][pos.x] to value.
		// Performs bounds-checking.
		template <std_arithmetic U>
		void set(const Vector2<U>& pos, const_reference value)
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));

			if (v.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (v.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			_data[(v.y * _cols) + v.x] = value;
		}

		// 
		void clear() noexcept
		{
			_data.clear();
		}

		// 
		void resize(size_type rows, size_type cols)
		{
			reallocate(rows, cols);
		}

		// Returns a copy of the given row.
		Array<T> getRow(size_type row) const
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");

			Array<T> arr;
			for (size_type col_i(0); col_i < _cols; ++col_i)
				arr[col_i] = _data[row][col_i];

			return arr;
		}

		// Returns a copy of the given column.
		Array<T> getCol(size_type col) const
		{
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			Array<T> arr;
			for (size_type row_i(0); row_i < _rows; ++row_i)
				arr[row_i] = _data[row_i][col];

			return arr;
		}

		// Swaps the contents of this Matrix with another Matrix.
		void swapWith(Matrix& other) noexcept
		{
			_data.swapWith(other._data);
			std::swap(_rows, other._rows);
			std::swap(_cols, other._cols);
		}

		// Returns the nth element of the Matrix.
		reference operator [] (size_type n)
		{
			return _data[n];
		}

		// Returns the nth element of the Matrix.
		const_reference operator [] (size_type n) const
		{
			return _data[n];
		}

		// Returns the element at [row][col].
		reference operator () (size_type row, size_type col)
		{
			return _data[(row * _cols) + col];
		}

		// Returns the element at [row][col].
		const_reference operator () (size_type row, size_type col) const
		{
			return _data[(row * _cols) + col];
		}

		// Returns the element at [pos.y][pos.x].
		reference operator () (const Vector2<size_type>& pos)
		{
			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		template <std_arithmetic U>
		reference operator () (const Vector2<U>& pos)
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));
			return _data[(v.y * _cols) + v.x];
		}

		// Returns the element at [pos.y][pos.x].
		const_reference operator () (const Vector2<size_type>& pos) const
		{
			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		template <std_arithmetic U>
		const_reference operator () (const Vector2<U>& pos) const
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));
			return _data[(v.y * _cols) + v.x];
		}
	};
}

// Overload of binary operator == 
template <typename T>
bool operator == (const jlib::Matrix<T>& A, const jlib::Matrix<T>& B)
{
	if (A.rowCount() != B.rowCount() || A.colCount() != B.colCount())
		return false;

	for (std::size_t i(0); i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return false;
	}

	return true;
}

// Overload of binary operator == 
template <typename T>
bool operator != (const jlib::Matrix<T>& A, const jlib::Matrix<T>& B)
{
	if (A.rowCount() != B.rowCount() || A.colCount() != B.colCount())
		return true;

	for (std::size_t i(0); i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// FIXEDMATRIX TEMPLATE CLASS                                                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A FixedMatrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <typename T, std::size_t R, std::size_t C> class FixedMatrix
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = FixedArray<T, R* C>::iterator;
		using const_iterator = FixedArray<T, R* C>::const_iterator;
		using reverse_iterator = FixedArray<T, R* C>::reverse_iterator;
		using const_reverse_iterator = FixedArray<T, R* C>::const_reverse_iterator;

		private:

		FixedArray<T, R* C> _data;

		public:

		// Default constructor.
		FixedMatrix() = default;

		// 1-parameter constructor.
		// Sets every element of the FixedMatrix to value.
		FixedMatrix(const_reference value)
		{
			for (size_type i(0); i < R * C; ++i)
				_data[i] = value;
		}

		// 2-dimensional std::initializer_list constructor.
		FixedMatrix(std::initializer_list<std::initializer_list<T>> list)
		{
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + C, _data.begin() + (row_i * C));
				++row_i;
			}
		}

		// Constructs the FixedMatrix from another type of FixedMatrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <typename U>
		explicit FixedMatrix(const FixedMatrix<U, R, C>& other)
		{
			for (size_type i(0); i < R * C; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// 2-dimensional std::initializer_list assignment operator.
		FixedMatrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + C, _data.begin() + (row_i * C));
				++row_i;
			}

			return *this;
		}

		// Returns the number of rows in the FixedMatrix.
		constexpr size_type rowCount() const noexcept
		{
			return R;
		}

		// Returns the number of columns in the FixedMatrix.
		constexpr size_type colCount() const noexcept
		{
			return C;
		}

		// Returns the number of elements in the FixedMatrix.
		constexpr size_type size() const noexcept
		{
			return R * C;
		}

		// 
		pointer data()
		{
			return _data.data();
		}

		// 
		const_pointer data() const
		{
			return _data.data();
		}

		// 
		iterator begin()
		{
			return _data.begin();
		}

		// 
		const_iterator begin() const
		{
			return _data.cbegin();
		}

		// 
		const_iterator cbegin() const
		{
			return _data.cbegin();
		}

		// 
		iterator end()
		{
			return _data.end();
		}

		// 
		const_iterator end() const
		{
			return _data.cend();
		}

		// 
		const_iterator cend() const
		{
			return _data.cend();
		}

		// 
		iterator rowBegin(size_type row)
		{
			return _data.begin() + (C * row);
		}

		// 
		const_iterator rowBegin(size_type row) const
		{
			return _data.cbegin() + (C * row);
		}

		// Returns the nth element of the FixedMatrix.
		// Performs bounds-checking.
		reference at(size_type n)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return _data[n];
		}

		// Returns the nth element of the FixedMatrix.
		// Performs bounds-checking.
		const_reference at(size_type n) const
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return _data[n];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		reference at(size_type row, size_type col)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		const_reference at(size_type row, size_type col) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		reference at(const Vector2<size_type>& pos)
		{
			if (pos.y >= R)
				throw std::out_of_range("Invalid row index");
			if (pos.x >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(pos.y * C) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		template <std_arithmetic U>
		reference at(const Vector2<U>& pos)
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));

			if (v.y >= R)
				throw std::out_of_range("Invalid row index");
			if (v.x >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(v.y * C) + v.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		const_reference at(const Vector2<size_type>& pos) const
		{
			if (pos.y >= R)
				throw std::out_of_range("Invalid row index");
			if (pos.x >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(pos.y * C) + pos.x];
		}

		// Sets the nth element of the FixedMatrix to value.
		// Performs bounds-checking.
		void set(size_type n, const_reference value)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			_data[n] = value;
		}

		// Sets the element at [row][col] to value.
		// Performs bounds-checking.
		void set(size_type row, size_type col, const_reference value)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			_data[(row * C) + col] = value;
		}

		// Sets the element at [pos.y][pos.x] to value.
		// Performs bounds-checking.
		void set(const Vector2<size_type>& pos, const_reference value)
		{
			if (pos.y >= R)
				throw std::out_of_range("Invalid row index");
			if (pos.x >= C)
				throw std::out_of_range("Invalid column index");

			_data[(pos.y * C) + pos.x] = value;
		}

		// Sets the element at [pos.y][pos.x] to value.
		// Performs bounds-checking.
		template <std_arithmetic U>
		void set(const Vector2<U>& pos, const_reference value)
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));

			if (v.y >= R)
				throw std::out_of_range("Invalid row index");
			if (v.x >= C)
				throw std::out_of_range("Invalid column index");

			_data[(v.y * C) + v.x] = value;
		}

		// Returns a copy of the given row.
		std::array<T, C> getRow(size_type row) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index.");

			std::array<T, C> arr;

			for (size_type col_i(0); col_i < C; ++col_i)
				arr[col_i] = _data[(C * row) + col_i];

			return arr;
		}

		// Returns a copy of the given column.
		std::array<T, R> getCol(size_type col) const
		{
			if (col >= C)
				throw std::out_of_range("Invalid column index.");

			std::array<T, R> arr;

			for (size_type row_i(0); row_i < C; ++row_i)
				arr[row_i] = _data[(C * row_i) + col];

			return arr;
		}

		// Returns the submatrix formed by the row and col indices.
		template <size_type R2, size_type C2>
		FixedMatrix<T, R2, C2> submatrix(size_type row_begin, size_type col_begin) const
		{
			if (row_begin >= R || row_begin + R2)
				throw std::out_of_range("Invalid row index.");
			if (col_begin >= C || col_begin + C >= C2)
				throw std::out_of_range("Invalid column index.");

			FixedMatrix<T, R2, C2> M;

			for (size_type row_i(0); row_i < R2; ++row_i)
			{
				for (size_type col_i(0); col_i < C2; ++col_i)
					M._data[(row_i * C) + col_i] = _data[(row_i * C) + col_i];
			}

			return M;
		}

		// Swaps the contents of this FixedMatrix with another FixedMatrix.
		void swapWith(FixedMatrix& other) noexcept
		{
			_data.swapWith(other._data);
		}

		// Returns the nth element of the FixedMatrix.
		reference operator [] (size_type n)
		{
			return _data[n];
		}

		// Returns the nth element of the FixedMatrix.
		const_reference operator [] (size_type n) const
		{
			return _data[n];
		}

		// Returns the element at [row][col].
		reference operator () (size_type row, size_type col)
		{
			return _data[(row * C) + col];
		}

		// Returns the element at [row][col].
		const_reference operator () (size_type row, size_type col) const
		{
			return _data[(row * C) + col];
		}

		// Returns the element at [pos.y][pos.x].
		reference operator () (const Vector2<size_type>& pos)
		{
			return _data[(pos.y * C) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		template <std_arithmetic U>
		reference operator () (const Vector2<U>& pos)
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));
			return _data[(v.y * C) + v.x];
		}

		// Returns the element at [pos.y][pos.x].
		const_reference operator () (const Vector2<size_type>& pos) const
		{
			return _data[(pos.y * C) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		template <std_arithmetic U>
		const_reference operator () (const Vector2<U>& pos) const
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));
			return _data[(v.y * C) + v.x];
		}
	};

	// Returns the determinant of the 2x2 FixedMatrix formed as
	// {  a,  b  }
	// {  c,  d  }
	template <std_arithmetic T>
	inline T determinant(T a, T b, T c, T d)
	{
		return (a * d) - (b * c);
	}

	// Returns the determinant of the 2x2 FixedMatrix.
	template <std_arithmetic T>
	inline T determinant(const FixedMatrix<T, 2, 2>& M)
	{
		return (M(0, 0) * M(1, 1)) - (M(1, 0) * M(0, 1));
	}

	// Returns the determinant of the 3x3 FixedMatrix.
	template <std_arithmetic T>
	T determinant(const FixedMatrix<T, 3, 3>& M)
	{
		T A = M(0, 0) * determinant(M(1, 1), M(1, 2), M(2, 1), M(2, 2));
		T B = M(0, 1) * determinant(M(1, 0), M(1, 2), M(2, 0), M(2, 2));
		T C = M(0, 2) * determinant(M(1, 0), M(1, 1), M(2, 0), M(2, 1));

		return A - B + C;
	}

	// Returns the determinant of the 4x4 FixedMatrix.
	template <std_arithmetic T>
	T determinant(const FixedMatrix<T, 4, 4>& M)
	{
		FixedMatrix<T, 3, 3> A =
		{
			{ M(1, 1), M(1, 2), M(1, 3) },
			{ M(2, 1), M(2, 2), M(2, 3) },
			{ M(3, 1), M(3, 2), M(3, 3) }
		};

		FixedMatrix<T, 3, 3> B =
		{
			{ M(1, 0), M(1, 2), M(1, 3) },
			{ M(2, 0), M(2, 2), M(2, 3) },
			{ M(3, 0), M(3, 2), M(3, 3) }
		};

		FixedMatrix<T, 3, 3> C =
		{
			{ M(1, 0), M(1, 1), M(1, 3) },
			{ M(2, 0), M(2, 1), M(2, 3) },
			{ M(3, 0), M(3, 1), M(3, 3) }
		};

		FixedMatrix<T, 3, 3> D =
		{
			{ M(1, 0), M(1, 1), M(1, 2) },
			{ M(2, 0), M(2, 1), M(2, 2) },
			{ M(3, 0), M(3, 1), M(3, 2) }
		};

		return M(0, 0) * determinant(A) - M(0, 1) * determinant(B) + M(0, 2) * determinant(C) - M(0, 3) * determinant(D);
	}

	// Returns the dot product of the given Matrices.
	template <std_arithmetic T, std::size_t R, std::size_t C, std::size_t S>
	FixedMatrix<T, R, S> dot_product(const FixedMatrix<T, R, C>& A, const FixedMatrix<T, C, S>& B)
	{
		FixedMatrix<T, R, S> M;
		T value;

		for (std::size_t r(0); r < R; ++r)
		{
			std::array<T, C> row(A.getRow(r));

			for (std::size_t s(0); s < S; ++s)
			{
				value = 0;
				std::array<R, C> col(B.getCol(s));

				for (std::size_t c(0); c < C; ++c)
					value += row[c] * col[c];

				M(r, s) = value;
			}
		}

		return M;
	}
}

// Overload of binary operator == 
template <typename T, std::size_t R, std::size_t C>
bool operator == (const jlib::FixedMatrix<T, R, C>& A, const jlib::FixedMatrix<T, R, C>& B)
{
	for (std::size_t i(0); i < R * C; ++i)
	{
		if (A[i] != B[i])
			return false;
	}

	return true;
}

// Overload of binary operator != 
template <typename T, std::size_t R, std::size_t C>
bool operator != (const jlib::FixedMatrix<T, R, C>& A, const jlib::FixedMatrix<T, R, C>& B)
{
	for (std::size_t i(0); i < R * C; ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}

// Overload of unary operator -
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C> operator - (const jlib::FixedMatrix<T, R, C>& A)
{
	jlib::FixedMatrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * static_cast<T>(-1);
	}

	return M;
}

// Overload of binary operator +
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C> operator + (const jlib::FixedMatrix<T, R, C>& A, const jlib::FixedMatrix<T, R, C>& B)
{
	jlib::FixedMatrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) + B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator -
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C> operator - (const jlib::FixedMatrix<T, R, C>& A, const jlib::FixedMatrix<T, R, C>& B)
{
	jlib::FixedMatrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) - B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C> operator * (const jlib::FixedMatrix<T, R, C>& A, U scalar)
{
	jlib::FixedMatrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * scalar;
	}

	return M;
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C> operator / (const jlib::FixedMatrix<T, R, C>& A, U scalar)
{
	jlib::FixedMatrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) / scalar;
	}

	return M;
}

// Overload of binary operator +=
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C>& operator += (jlib::FixedMatrix<T, R, C>& A, const jlib::FixedMatrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			A(row_i, col_i) += B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C>& operator -= (jlib::FixedMatrix<T, R, C>& A, const jlib::FixedMatrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			A(row_i, col_i) -= B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C>& operator *= (jlib::FixedMatrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) *= scalar;
	}

	return M;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::FixedMatrix<T, R, C>& operator /= (jlib::FixedMatrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) /= scalar;
	}

	return M;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// DIRECTION STRUCT                                                                              //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	struct Direction
	{
		public:

		u8 id;
		Vector2f unitVector;
		Angle angle;

		enum : u8
		{
			UP = 0,
			RIGHT = 1,
			DOWN = 2,
			LEFT = 3,
		};
	};

	extern const Direction UP;
	extern const Direction RIGHT;
	extern const Direction DOWN;
	extern const Direction LEFT;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// JOYSTICK CLASS                                                                                //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	class Joystick
	{
		public:

		Vector2f position;
		float xDeadzone, yDeadzone;

		// Default constructor.
		// Sets the position of the Joystick to (0, 0).
		// Sets the deadzones of the Joystick to 0.1f.
		Joystick();

		// 3-float constructor.
		// Sets the position of the Joystick to (X, Y).
		// Sets the horizontal deadzone of the Joystick to x_dz.
		// Sets the vertical deadzone of the Joysticl to y_dz.
		Joystick(float X, float Y, float x_dz, float y_dz);

		// Vector2f& float constructor.
		// Sets the position of the Joystick to Position.
		// Sets the horizontal deadzone of the Joystick to x_dz.
		// Sets the vertical deadzone of the Joysticl to y_dz.
		Joystick(const Vector2f& Position, float x_dz, float y_dz);

		// Sets the horizontal deadzone of the Joystick to x_dz.
		void setHorizontalDeadzone(float x_dz);

		// Sets the vertical deadzone of the Joysticl to y_dz.
		void setVerticalDeadzone(float y_dz);

		// Sets the horizontal deadzone of the Joystick to x_dz.
		// Sets the vertical deadzone of the Joysticl to y_dz.
		void setDeadzones(float x_dz, float y_dz);

		// Returns true if the Joystick's position is within its deadzone.
		bool isStickInDeadZone() const;

		// Returns the angle of the Joystick.
		Angle getAngle() const;

		// Returns the direction of the Joystick's angle.
		const Direction* getDirection() const;
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// GAMEPAD CLASS                                                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	class Gamepad
	{
		public:

		enum Button
		{
			A = XINPUT_GAMEPAD_A,
			B = XINPUT_GAMEPAD_B,
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y,
			DPadUp = XINPUT_GAMEPAD_DPAD_UP,
			DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
			DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
			DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
			LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			LThumbstick = XINPUT_GAMEPAD_LEFT_THUMB,
			RThumbstick = XINPUT_GAMEPAD_RIGHT_THUMB,
			Start = XINPUT_GAMEPAD_START,
			Back = XINPUT_GAMEPAD_BACK,
			Count = 14
		};

		private:

		u8 _port;
		XINPUT_STATE _state;
		WORD _oldButtonStates;

		public:

		Joystick leftStick, rightStick;
		float leftTrigger, rightTrigger;

		// Default constructor.
		// Sets the horizontal and vertical deadzones of each Joystick to 0.1f.
		// Sets the values of each Trigger to 0.0f.
		Gamepad();

		// 1-unsigned char, 4-float constructor.
		// Sets the port of the Gamepad to Port.
		// Sets the horizontal deadzone for the left Joystick to lx_dz.
		// Sets the vertical deadzone for the left Joystick to ly_dz.
		// Sets the horizontal deadzone for the right Joystick to rx_dz.
		// Sets the vertical deadzone for the right Joystick to ry_dz.
		// Sets the values of each Trigger to 0.0f.
		Gamepad(u8 Port, float lx_dz, float ly_dz, float rx_dz, float ry_dz);

		// 
		bool isConnected();

		// 
		u8 getPort() const;

		// 
		XINPUT_STATE getState() const;

		// 
		bool isButtonPressed(Button button) const;

		// 
		bool isButtonHeld(Button button) const;

		// 
		bool isButtonReleased(Button button) const;

		// 
		void update();
	};
}

// Overload of binary operator ==
bool operator == (const jlib::Gamepad& A, const jlib::Gamepad& B);

// Overload of binary operator !=
bool operator != (const jlib::Gamepad& A, const jlib::Gamepad& B);

///////////////////////////////////////////////////////////////////////////////////////////////////
// CLOCK CLASS                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Shorthand for std::chrono::time_point<std::chrono::system_clock>.
	typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
	// Shorthand for std::chrono::duration<float>.
	typedef std::chrono::duration<float> Duration;

	extern const Duration TimeZero;

	// 
	class Clock
	{
		TimePoint _start;

		public:

		// Default constructor.
		//
		Clock();

		// Copy constructor.
		Clock(const Clock& other) = delete;

		// Move constructor.
		Clock(Clock&& other) = delete;

		// Copy assignment operator.
		Clock& operator = (const Clock& other) = delete;

		// Move assignment operator.
		Clock& operator = (Clock&& other) = delete;

		// Destructor.
		~Clock() = default;

		// 
		TimePoint startTime() const;

		// 
		TimePoint now() const;

		// 
		Duration restart();

		// 
		Duration timeElapsed() const;
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// HEXADECIMAL FUNCTIONS                                                                         //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Returns a hexadecimal std::string representation of the integer.
	template <std::integral T>
	std::string to_hex_string(T number, bool prepend = false, bool fill = false)
	{
		std::stringstream str_stream;

		if (prepend)
			str_stream << "0x";

		if (fill)
			str_stream << std::setfill('0') << std::setw(sizeof(T) * 2);

		str_stream << std::hex << number;
		return str_stream.str();
	}

	// Returns a hexadecimal std::wstring representation of the integer.
	template <std::integral T>
	std::wstring to_hex_wstring(T number, bool prepend = false, bool fill = false)
	{
		std::wstringstream wstr_stream;

		if (prepend)
			wstr_stream << L"0x";

		if (fill)
			wstr_stream << std::setfill(L'0') << std::setw(sizeof(T) * 2);

		wstr_stream << std::hex << number;
		return wstr_stream.str();
	}

	// Returns a hexadecimal std::string representation of the float.
	std::string to_hex_string(float number, bool prepend = false, bool fill = false);

	// Returns a hexadecimal std::wstring representation of the float.
	std::wstring to_hex_wstring(float number, bool prepend = false, bool fill = false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// COLOR CLASS                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	class Color
	{
		public:

		static const u8 MAX = 0xff;

		enum : u32
		{
			Black = 0x000000ff,
			White = 0xffffffff,
			Red = 0xff0000ff,
			Green = 0x00ff00ff,
			Blue = 0x0000ffff,
			Cyan = 0x00ffffff,
			Magenta = 0xff00ffff,
			Yellow = 0xffff00ff,
			Silver = 0xc0c0c0ff,
			Gray = 0x808080ff,
			Maroon = 0x800000ff,
			Olive = 0x808000ff,
			DarkGreen = 0x008000ff,
			Purple = 0x800080ff,
			Teal = 0x008080ff,
			Navy = 0x000080ff,
			Clear = 0x00000000
		};

		u8 r, g, b, a;

		// Default constructor.
		// Sets each component of the Color to 0.
		Color();

		// Primary constructor.
		// Sets the red component of the Color to new_r.
		// Sets the green component of the Color to new_g.
		// Sets the blue component of the Color to new_b.
		// Sets the alpha component of the Color to new_a.
		Color(u8 new_r, u8 new_g, u8 new_b, u8 new_a = MAX);

		// Secondary constructor.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color(u32 color);

		// FixedArray constructor.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color(const FixedArray<u8, 4>& arr);

		// std::initializer_list constructor.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color(std::initializer_list<u8> list);

		// Default copy constructor.
		Color(const Color& other) = default;

		// Default move constructor.
		Color(Color&& other) = default;

		// unsigned int assignment operator.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color& operator = (u32 color);

		// FixedArray assignment operator.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color& operator = (const FixedArray<u8, 4>& arr);

		// std::initializer_list assignment operator.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color& operator = (std::initializer_list<u8> list);

		// Default copy assignment operator.
		Color& operator = (const Color& other) = default;

		// Default move assignment operator.
		Color& operator = (Color&& other) = default;

		// Destructor.
		~Color() = default;

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to new_r.
		// Sets the green component of the Color to new_g.
		// Sets the blue component of the Color to new_b.
		// Sets the alpha component of the Color to new_a.
		void set(u8 new_r, u8 new_g, u8 new_b, u8 new_a);

		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		void set(u32 color);

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		void set(const FixedArray<u8, 4>& arr);

		// Returns a 32-but unsigned integer representation of the Color.
		u32 toInt() const;

		// Returns a std::array copy of the Color's components.
		FixedArray<u8, 4> toArray() const;

		// Returns a std::string representation of the Color.
		std::string toString() const;

		// Returns a std::wstring representation of the Color.
		std::wstring toWideString() const;
	};

	// Returns the individual bytes of the unsigned int.
	FixedArray<u8, 4> to_bytes(u32 i);

	// Returns a hexadecimal std::string representation of the byte.
	std::string to_hex_str(u8 cbyte);

	// Returns a hexadecimal std::wstring representation of the byte.
	std::wstring to_hex_wstr(u8 cbyte);

	// Copies the color bytes into the given destination.
	void copy_color_data(const Color* src, u8* dst, std::size_t bytes);
}

// Overload of binary operator ==
bool operator == (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator !=
bool operator != (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator +
jlib::Color operator + (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator -
jlib::Color operator - (const jlib::Color& A, const jlib::Color& B);

// Overload of binary operator +=
jlib::Color& operator += (jlib::Color& A, const jlib::Color& B);

// Overload of binary operator -=
jlib::Color& operator -= (jlib::Color& A, const jlib::Color& B);

// Overload of binary operator *
jlib::Color operator * (const jlib::Color& A, float f);

// Overload of binary operator /
jlib::Color operator / (const jlib::Color& A, float f);

// Overload of binary operator *=
jlib::Color& operator *= (jlib::Color& A, float f);

// Overload of binary operator /=
jlib::Color& operator /= (jlib::Color& A, float f);

// Overload of std::ostream operator <<
std::ostream& operator << (std::ostream& os, const jlib::Color& A);

// Overload of std::wostream operator <<
std::wostream& operator << (std::wostream& os, const jlib::Color& A);

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	#ifdef SFML_SYSTEM_WINDOWS

	template <std_arithmetic T>
	constexpr float magnitude(const sf::Vector2<T>& v)
	{
		return std::sqrtf(std::powf(static_cast<float>(v.x), 2.0f) + std::powf(static_cast<float>(v.y), 2.0f));
	}

	template <std_arithmetic T>
	constexpr float magnitude(const sf::Vector3<T>& v)
	{
		return std::sqrtf(std::powf(static_cast<float>(v.x), 2.0f) + std::powf(static_cast<float>(v.y), 2.0f) + std::powf(static_cast<float>(v.z), 2.0f));
	}

	template <std_arithmetic T>
	sf::Vector2<T> unit_vector(const sf::Vector2<T>& v)
	{
		constexpr float m = magnitude(v);
		return sf::Vector2<float>(v.x / m, v.y / m);
	}

	template <std_arithmetic T>
	sf::Vector3<T> unit_vector(const sf::Vector3<T>& v)
	{
		constexpr float m = magnitude();
		return sf::Vector3<float>(v.x / m, v.y / m, v.z / m);
	}
	
	template <std_arithmetic T>
	std::string to_string(const sf::Vector2<T>& v)
	{
		return '<' + std::to_string(v.x) + ", " + std::to_string(v.y) + '>';
	}

	template <std_arithmetic T>
	std::string to_string(const sf::Vector3<T>& v)
	{
		return '<' + std::to_string(v.x) + ", " + std::to_string(v.y) + +", " + std::to_string(v.z) '>';
	}

	template <std_arithmetic T>
	std::wstring to_wstring(const sf::Vector2<T>& v)
	{
		return L'<' + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L'>';
	}

	template <std_arithmetic T>
	std::wstring to_wstring(const sf::Vector3<T>& v)
	{
		return L'<' + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L", " + std::to_wstring(v.z) + L'>';
	}

	template <std_arithmetic T>
	sf::Vector2<T> to_sfml(const Vector2<T>& v)
	{
		return sf::Vector2<T>(v.x, v.y);
	}

	template <std_arithmetic T>
	sf::Vector3<T> to_sfml(const Vector3<T>& v)
	{
		return sf::Vector3<T>(v.x, v.y, v.z);
	}

	sf::Color to_sfml(const Color& c);

	template <std_arithmetic T>
	Vector2<T> to_jlib(const sf::Vector2<T>& v)
	{
		return Vector2<T>(v.x, v.y);
	}

	template <std_arithmetic T>
	Vector3<T> to_jlib(const sf::Vector3<T>& v)
	{
		return Vector3<T>(v.x, v.y, v.z);
	}

	Color to_jlib(const sf::Color& c);

	#endif // #ifdef SFML_SYSTEM_WINDOWS
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRINT FUNCTIONS                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	template <std_arithmetic T>
	void println(T val)
	{
		std::cout << std::to_string(val) << '\n';
	}

	void println(const std::string& str);

	void println(const std::wstring& wstr);

	void println(Angle ang);

	template <std::integral T>
	void println(const Fraction<T>& fr)
	{
		std::cout << fr.toString() << '\n';
	}

	template <std_arithmetic T>
	void println(const Vector2<T>& vec)
	{
		std::cout << vec.toString() << '\n';
	}

	template <std_arithmetic T>
	void println(const Vector3<T>& vec)
	{
		std::cout << vec.toString() << '\n';
	}

	template <std_arithmetic T, std::size_t N>
	void println(const VectorN<T, N>& vec)
	{
		std::cout << vec.toString() << '\n';
	}

	template <std_arithmetic T>
	void println(const Rect<T>& rect)
	{
		std::cout << rect.toString() << '\n';
	}

	template <std_arithmetic T>
	void println(const Square<T>& sq)
	{
		std::cout << sq.toString() << '\n';
	}

	template <std_arithmetic T>
	void println(const Circle<T>& cir)
	{
		std::cout << cir.toString() << '\n';
	}

	template <std_arithmetic T>
	void println(const Triangle<T>& tri)
	{
		std::cout << tri.toString() << '\n';
	}

	template <std_arithmetic T>
	void println(const LineSegment<T>& line)
	{
		std::cout << line.toString() << '\n';
	}

	void println(const Color& color);
}