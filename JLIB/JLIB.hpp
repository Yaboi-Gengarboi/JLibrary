// JLIB
// JLIB.hpp
// Created on 2021-08-06 by Justyn Durnford
// Last modified on 2021-08-16 by Justyn Durnford

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NOMINMAX
	#define NOMINMAX
#endif // #ifndef NOMINMAX

#pragma warning(disable : 4996)

#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <locale>
#include <numbers>
#include <stdexcept>
#include <string>
#include <utility>
#include <windows.h>
#include <xinput.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
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
	#endif // _WIN64

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
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	#ifndef JLIB_STD_ARITHMETIC
		#define JLIB_STD_ARITHMETIC
		template <typename T> concept std_arithmetic = std::is_arithmetic_v<T>;
	#endif // JLIBRARY_STD_ARITHMETIC
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	constexpr float JLIB_PI     = std::numbers::pi_v<float>;
	constexpr float JLIB_PI_2   = std::numbers::pi_v<float> / 2.0F;
	constexpr float JLIB_PI_3   = std::numbers::pi_v<float> / 3.0F;
	constexpr float JLIB_PI_4   = std::numbers::pi_v<float> / 4.0F;
	constexpr float JLIB_PI_6   = std::numbers::pi_v<float> / 6.0F;
	constexpr float JLIB_TO_RAD = std::numbers::pi_v<float> / 180.0F;
	constexpr float JLIB_TO_DEG = 180.F / std::numbers::pi_v<float>;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	enum rcode : u8
	{
		FAIL    = 0,
		OK      = 1,
		NO_FILE = 2
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
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

	std::string wstr2str(const std::wstring& wstr);

	std::wstring str2wstr(const std::string& str);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility string class that automatically handles conversions between types and encodings.
	class String
	{
		public:

		using value_type = wchar_t;
		using traits_type = std::wstring::traits_type;
		using allocator_type = std::wstring::allocator_type;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = wchar_t&;
		using const_reference = const wchar_t&;
		using pointer = wchar_t*;
		using const_pointer = const wchar_t*;
		using iterator = std::wstring::iterator;
		using const_iterator = std::wstring::const_iterator;
		using reverse_iterator = std::wstring::reverse_iterator;
		using const_reverse_iterator = std::wstring::const_reverse_iterator;

		static const size_type npos = -1;

		private:

		std::wstring _data;

		public:

		// Default constructor.
		String() = default;

		// Size constructor.
		String(size_type len);

		// Constructs the String from a char.
		String(char c, size_type count = 1);

		// Constructs the String from a wchar_t.
		String(wchar_t c, size_type count = 1);

		// Constructs the String from a null-terminated C-style string.
		String(const char* cstr);

		// Constructs the String from a null-terminated C-style wide string.
		String(const wchar_t* wcstr);

		// Constructs the String from a std::string.
		String(const std::string& str);

		// Constructs the String from a std::wstring.
		String(const std::wstring& wstr);

		// Constructs the String from a null-terminated C-style string.
		String& operator = (const char* cstr);

		// Constructs the String from a null-terminated C-style wide string.
		String& operator = (const wchar_t* wcstr);

		// Constructs the String from a std::string.
		String& operator = (const std::string& str);

		// Constructs the String from a std::wstring.
		String& operator = (const std::wstring& wstr);

		// Returns the character at the given index.
		// Throws an exception if given an invalid index.
		reference at(size_type index);

		// Returns the character at the given index.
		// Throws an exception if given an invalid index.
		const_reference at(size_type index) const;

		// Returns the first character of the String.
		reference front();

		// Returns the first character of the String.
		const_reference front() const;

		// Returns the last character of the String.
		reference back();

		// Returns the last character of the String.
		const_reference back() const;

		// Returns the size of the String.
		constexpr size_type size() const noexcept;

		// Returns the capacity of the String.
		constexpr size_type capacity() const noexcept;

		// Returns true if the String is empty.
		constexpr bool isEmpty() const noexcept;

		// Returns a pointer to the first character of the String.
		constexpr pointer data() noexcept;

		// Returns a pointer to the first character of the String.
		constexpr const_pointer data() const noexcept;

		// Returns an iterator to the begining of the String.
		constexpr iterator begin() noexcept;

		// Returns an iterator to the begining of the String.
		constexpr const_iterator begin() const noexcept;

		// Returns an iterator to the begining of the String.
		constexpr const_iterator cbegin() const noexcept;

		// Returns an iterator to the end of the String.
		constexpr iterator end() noexcept;

		// Returns an iterator to the end of the String.
		constexpr const_iterator end() const noexcept;

		// Returns an iterator to the end of the String.
		constexpr const_iterator cend() const noexcept;

		// Returns a reverse iterator to the begining of the String.
		constexpr reverse_iterator rbegin() noexcept;

		// Returns a reverse iterator to the begining of the String.
		constexpr const_reverse_iterator rbegin() const noexcept;

		// Returns a reverse iterator to the begining of the String.
		constexpr const_reverse_iterator crbegin() const noexcept;

		// Returns a reverse iterator to the end of the String.
		constexpr reverse_iterator rend() noexcept;

		// Returns a reverse iterator to the end of the String.
		constexpr const_reverse_iterator rend() const noexcept;

		// Returns a reverse iterator to the end of the String.
		constexpr const_reverse_iterator crend() const noexcept;

		// Finds a sequence of one or more characters in the string.
		// Returns -1 if the sequence cannot be found.
		size_type find(const String& str, size_type start = 0) const noexcept;

		// Reduces the size of the String to 0.
		constexpr void clear() noexcept;

		// Requests the removal of unused capacity.
		void shrink_to_fit();

		// Appends characters to the String.
		void append(char c, size_type count);

		// Appends characters to the String.
		void append(wchar_t c, size_type count);

		// Appends the given String to this String.
		void append(const String& str);

		// Resizes the String.
		void resize(size_type len);

		// Resizes the String.
		void resize(size_type len, char c);

		// Resizes the String.
		void resize(size_type len, wchar_t c);

		// Inserts the sequence of character into the String.
		void insert(const String& str, size_type pos);

		// Erases characters from the String.
		void erase(size_type pos, size_type count = 1);

		// Erases characters from the String.
		void erase(const_iterator first, const_iterator last);

		// Replace a portion of the String with another String.
		void replace(size_type pos, size_type len, const String& str);

		// Replace all occurrences of a substring of the String with another String.
		void replace(const String& oldstr, const String& newstr);

		// Returns a part of the String.
		String substr(size_type pos, size_type len = npos) const;

		// Returns a part of the String.
		String substr(const_iterator first, const_iterator last) const;

		// Compares the given Strimg to this String.
		constexpr int compareWith(const String& other) const;

		// Converts the String to a std::string.
		std::string toString() const;

		// Converts the String to a std::wstring.
		std::wstring toWideString() const;

		// Returns the character at the given index.
		reference operator [] (size_type index);

		// Returns the character at the given index.
		const_reference operator [] (size_type index) const;

		// Appends the given character to the String.
		String& operator += (char c);

		// Appends the given character to the String.
		String& operator += (wchar_t c);

		// Appends the given String to this String.
		String& operator += (const String& str);

		// Implicit conversion operator to std::string.
		operator std::string() const;

		// Implicit conversion operator to std::wstring.
		operator std::wstring() const;
	};
}

// Overload of binary operator +
jlib::String operator + (const jlib::String& A, const jlib::String& B);

// Overload of binary operator ==
bool operator == (const jlib::String& A, const jlib::String& B);

// Overload of binary operator ==
bool operator != (const jlib::String& A, const jlib::String& B);

// Overload of binary operator <
bool operator < (const jlib::String& A, const jlib::String& B);

// Overload of binary operator <=
bool operator <= (const jlib::String& A, const jlib::String& B);

// Overload of binary operator >
bool operator > (const jlib::String& A, const jlib::String& B);

// Overload of binary operator >=
bool operator >= (const jlib::String& A, const jlib::String& B);

// Overload of binary operator <=
std::strong_ordering operator <=> (const jlib::String& A, const jlib::String& B);

// Overload of std::ostream operator <<
std::ostream& operator << (std::ostream& os, const jlib::String& A);

// Overload of std::wostream operator <<
std::wostream& operator << (std::wostream& wos, const jlib::String& A);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	class Angle
	{
		public:

		float degree;

		// Default constructor.
		Angle();

		// Float constructor.
		// Sets the Angle to the given degree.
		Angle(float Degree);

		// Float assignment operator.
		// Sets the Angle to the given degree.
		Angle& operator = (float Degree);

		// Returns a std::string representation of the Angle.
		std::string toString() const;
	};

	// Returns the convertion from degrees to radians.
	constexpr float to_radians(float degree);

	// Returns the convertion from radians to degrees.
	constexpr float to_degrees(float radian);

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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// This class provides an "exact" representation of the quotient of two 
	// integers by storing them and allowing fraction arithmetic with them. 
	// Use the member function evaluate() to obtain the result of the fraction.
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
		// Sets the numerator of the Fraction to Numer.
		// Sets the denominator of the Fraction to 1.
		Fraction(T Numer)
		{
			numer = Numer;
			denom = static_cast<T>(1);
		}

		// 2-int constructor.
		// Sets the numerator of the Fraction to numer.
		// Sets the denominator of the Fraction to denom.
		Fraction(T Numer, T Denom)
		{
			numer = Numer;
			denom = Denom;
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

		Fraction(std::initializer_list<T> list)
		{
			numer = *(list.begin() + 0);
			denom = *(list.begin() + 1);
		}

		// 1-int assignment operator.
		// Sets the numerator of the Fraction to Numer.
		// Sets the denominator of the Fraction to 1.
		Fraction& operator = (T Numer)
		{
			numer = Numer;
			denom = static_cast<T>(1);
			return *this;
		}

		Fraction& operator = (std::initializer_list<T> list)
		{
			numer = *(list.begin() + 0);
			denom = *(list.begin() + 1);

			return *this;
		}

		// Sets all the values of the Fraction at once.
		// Sets the numerator of the Fraction to Numer.
		// Sets the denominator of the Fraction to Denom.
		void set(T Numer, T Denom)
		{
			numer = Numer;
			denom = Denom;
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
		float evaluate() const
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
	return A.evaluate() == B.evaluate();
}

// Overload of binary operator ==
template <std::integral T>
bool operator == (const jlib::Fraction<T>& A, float B)
{
	return A.evaluate() == B;
}

// Overload of binary operator !=
template <std::integral T>
bool operator != (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.evaluate() != B.evaluate();
}

// Overload of binary operator !=
template <std::integral T>
bool operator != (const jlib::Fraction<T>& A, float B)
{
	return A.evaluate() != B;
}

// Overload of binary operator >
template <std::integral T>
bool operator > (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.evaluate() > B.evaluate();
}

// Overload of binary operator >
template <std::integral T>
bool operator > (const jlib::Fraction<T>& A, float B)
{
	return A.evaluate() > B;
}

// Overload of binary operator >=
template <std::integral T>
bool operator >= (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.evaluate() >= B.evaluate();
}

// Overload of binary operator >=
template <std::integral T>
bool operator >= (const jlib::Fraction<T>& A, float B)
{
	return A.evaluate() >= B;
}

// Overload of binary operator <
template <std::integral T>
bool operator < (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.evaluate() < B.evaluate();
}

// Overload of binary operator <
template <std::integral T>
bool operator < (const jlib::Fraction<T>& A, float B)
{
	return A.evaluate() < B;
}

// Overload of binary operator <=
template <std::integral T>
bool operator <= (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	return A.evaluate() <= B.evaluate();
}

// Overload of binary operator <=
template <std::integral T>
bool operator <= (const jlib::Fraction<T>& A, float B)
{
	return A.evaluate() <= B;
}

// Overload of binary operator <=>
template <std::integral T>
std::strong_ordering operator <=> (const jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	if (A.evaluate() < B.evaluate())
		return std::strong_ordering::less;

	if (A.evaluate() > B.evaluate())
		return std::strong_ordering::greater;

	return std::strong_ordering::equal;
}

// Overload of binary operator <=>
template <std::integral T>
std::strong_ordering operator <=> (const jlib::Fraction<T>& A, float B)
{
	if (A.evaluate() < B)
		return std::strong_ordering::less;

	if (A.evaluate() > B)
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
	return value * A.evaluate();
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
	return value / A.evaluate();
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

///////////////////////////////////////////////////////////////////////////////////////////////////
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
		// Sets the x component of the Vector2 to X.
		// Sets the y component of the Vector2 to Y.
		Vector2(T X, T Y)
		{
			x = X;
			y = Y;
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

		// Constructs the Vector2 from another type of Vector2.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Vector2(const Vector2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Sets all the values of the Vector2 at once.
		// Sets the x component of the Vector2 to X.
		// Sets the y component of the Vector2 to Y.
		void set(T X, T Y)
		{
			x = X;
			y = Y;
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
			return std::sqrtf(std::powf(x, 2.f) + std::powf(y, 2.f));
		}

		// Returns the unit vector of this Vector2.
		Vector2<float> unitVector() const
		{
			float m = magnitude();
			return Vector2<float>(x / m, y / m);
		}

		// Returns a normal vector of this Vector2.
		Vector2 normal_vector()
		{
			return Vector2(-y, x);
		}

		// Returns a std::string representation of the Vector2.
		std::string toString() const
		{
			return '<' + std::to_string(x) + ", " + std::to_string(y) + '>';
		}
	};

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

///////////////////////////////////////////////////////////////////////////////////////////////////
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
		// Sets the x component of the Vector3 to X.
		// Sets the y component of the Vector3 to Y.
		// Sets the z component of the Vector3 to Z.
		Vector3(T X, T Y, T Z)
		{
			x = X;
			y = Y;
			z = Z;
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

		Vector3(std::initializer_list<T> elems)
		{
			x = *(elems.begin() + 0);
			y = *(elems.begin() + 1);
			z = *(elems.begin() + 2);
		}

		Vector3& operator = (std::initializer_list<T> elems)
		{
			x = *(elems.begin() + 0);
			y = *(elems.begin() + 1);
			z = *(elems.begin() + 2);

			return *this;
		}

		// Sets all the values of the Vector3 at once.
		// Sets the x component of the Vector3 to X.
		// Sets the y component of the Vector3 to Y.
		// Sets the z component of the Vector3 to Z.
		void set(T X, T Y, T Z)
		{
			x = X;
			y = Y;
			z = Z;
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
		float magnitude() const
		{
			return std::sqrtf(std::powf(x, 2.f) + std::powf(y, 2.f) + std::powf(z, 2.f));
		}

		// Returns a std::string representation of the Vector3.
		std::string toString() const
		{
			return '<' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + '>';
		}
	};

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

	// Returns a unit vector in the direction of the Vector3.
	template <std_arithmetic T>
	Vector3<T> unit_vector(const Vector3<T>& A)
	{
		return Vector3<T>(A) / A.magnitude();
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors with N-dimensions.
	template <std_arithmetic T, std::size_t N> class VectorN
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
		// Sets each component of the VectorN to 0.
		VectorN()
		{
			for (T& elem : data)
				elem = static_cast<T>(0);
		}

		// Constructs the VectorN from the given coordinates.
		VectorN(std::initializer_list<T> elems)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = *(elems.begin() + i);
		}

		// Constructs the VectorN as the displacement vector of the two points.
		VectorN(const VectorN& A, const VectorN& B)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = B[i] - A[i];
		}

		// Constructs the VectorN from another type of VectorN.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		VectorN(const VectorN<U, N>& other)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = static_cast<T>(other.data[i]);
		}

		// Constructs the VectorN from the given coordinates.
		VectorN& operator = (std::initializer_list<T> elems)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = *(elems.begin() + i);
			return *this;
		}

		// Copies the components of a different type of Vector2.
		template <jlib::std_arithmetic U>
		void copyFrom(const VectorN<U, N>& other)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = static_cast<T>(other.data[i]);
		}

		// Returns the amount of dimensions the VectorN has.
		std::size_t dimensions() const
		{
			return N;
		}

		// Returns the first element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		T& first()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[0];
		}

		// Returns the first element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		const T& first() const
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[0];
		}

		// Returns the last element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		T& last()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[N - 1];
		}

		// Returns the last element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
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

		// Returns the magnitude of the VectorN.
		float magnitude() const
		{
			float value = 0.f;

			for (std::size_t i(0); i < N; ++i)
				value += std::pow(data[i], 2);

			return std::sqrt(value);
		}

		// Returns a std::string representation of the VectorN.
		std::string toString() const
		{
			if (N == 0)
				return "";
			if (N == 1)
				return '<' + std::to_string(data[0]) + '>';

			std::string str;

			str += '<';
			for (std::size_t i(0); i < N - 1; ++i)
				str += std::to_string(data[i]) + ", ";
			str += std::to_string(data[N - 1]) + '>';

			return str;
		}
	};

	// Returns the distance between the 2 given VectorNs.
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

	// Returns the dot product of the 2 given VectorNs.
	template <std_arithmetic T, std::size_t N>
	float dot_product(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float value = 0.f;

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

	typedef jlib::VectorN<bool, 4>   Vector4b;
	typedef jlib::VectorN<i8, 4>     Vector4c;
	typedef jlib::VectorN<u8, 4>     Vector4uc;
	typedef jlib::VectorN<i16, 4>    Vector4s;
	typedef jlib::VectorN<u16, 4>    Vector4us;
	typedef jlib::VectorN<i32, 4>    Vector4i;
	typedef jlib::VectorN<u32, 4>    Vector4u;
	typedef jlib::VectorN<float, 4>  Vector4f;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T, std::size_t N>
bool operator == (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.data == B.data;
}

// Overload of binary operator !=
template <jlib::std_arithmetic T, std::size_t N>
bool operator != (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.data != B.data;
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
jlib::VectorN<T, N>& operator += (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] += B[i];

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N>& operator -= (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std_arithmetic T> class Rect
	{
		public:

		T x;
		T y;
		T width;
		T height;

		// Default constructor.
		// Sets the x component of the vertex of the Rect to 0.
		// Sets the y component of the vertex of the Rect to 0.
		// Sets the width of the Rect to 0.
		// Sets the height of the Rect to 0.
		Rect()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
			width = static_cast<T>(0);
			height = static_cast<T>(0);
		}

		// 4-parameter constructor.
		// Sets the x component of the vertex of the Rect to X.
		// Sets the y component of the vertex of the Rect to Y.
		// Sets the width of the Rect to Width.
		// Sets the height of the Rect to Height.
		Rect(T X, T Y, T Width, T Height)
		{
			x = X;
			y = Y;
			width = Width;
			height = Height;
		}

		// Vector2 constructor.
		// Sets the vertex of the Rect to the given point.
		// Sets the width of the Rect to Width.
		// Sets the height of the Rect to Height.
		Rect(const Vector2<T>& P, T Width, T Height)
		{
			x = P.x;
			y = P.y;
			width = Width;
			height = Height;
		}

		// Constructs the Rect from another type of Rect.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Rect(const Rect<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			width = static_cast<T>(other.width);
			height = static_cast<T>(other.height);
		}

		// Sets all the values of the Rect at once.
		// Sets the x component of the vertex of the Rect to X.
		// Sets the y component of the vertex of the Rect to Y.
		// Sets the width of the Rect to Width.
		// Sets the height of the Rect to Height.
		void set(T X, T Y, T Width, T Height)
		{
			x = X;
			y = Y;
			width = Width;
			height = Height;
		}

		// 
		void setVertex(T X, T Y)
		{
			x = X;
			y = Y;
		}

		// 
		void setVertex(const Vector2<T>& pos)
		{
			x = pos.x;
			y = pos.y;
		}

		// 
		void setDimensions(T Width, T Height)
		{
			width = Width;
			height = Height;
		}

		// 
		void setDimensions(const Vector2<T>& size)
		{
			width = size.x;
			height = size.y;
		}

		// Returns the perimeter of the Rect.
		float perimeter() const
		{
			return 2.f * (width + height);
		}

		// Returns the area of the Rect.
		float area() const
		{
			return width * height;
		}

		// Returns the top-left vertex of the Rect.
		Vector2<T> topLeft() const
		{
			return Vector2<T>(std::min(x, x + width), std::min(y, y + height));
		}

		// Returns the top-right vertex of the Rect.
		Vector2<T> topRight() const
		{
			return Vector2<T>(std::max(x, x + width), std::min(y, y + height));
		}

		// Returns the bottom-left vertex of the Rect.
		Vector2<T> bottomLeft() const
		{
			return Vector2<T>(std::min(x, x + width), std::max(y, y + height));
		}

		// Returns the bottom-right vertex of the Rect.
		Vector2<T> bottomRight() const
		{
			return Vector2<T>(std::max(x, x + width), std::max(y, y + height));
		}

		// Returns the dimensions of the Rect.
		Vector2<T> dimensions() const
		{
			return Vector2<T>(width, height);
		}

		// Returns a std::array containing the vertices of the Rect.
		std::array<Vector2<T>, 4> getVertices() const
		{
			std::array<Vector2<T>, 4> arr;

			arr[0] = topLeft();
			arr[1] = topRight();
			arr[2] = bottomLeft();
			arr[3] = bottomRight();

			return arr;
		}

		// Checks if the given Point2 lies within or on the Rect.
		template <std_arithmetic U>
		bool contains(T X, T Y)
		{
			Vector2<T> A(topLeft());
			Vector2<T> B(bottomRight());

			return (X <= B.x) && (X >= A.x) && (Y <= B.y) && (Y >= A.y);
		}

		// Checks if the given Point2 lies within or on the Rect.
		template <std_arithmetic U>
		bool contains(const Vector2<U>& P)
		{
			Vector2<T> A(topLeft());
			Vector2<T> B(bottomRight());

			return (P.x <= B.x) && (P.x >= A.x) && (P.y <= B.y) && (P.y >= A.y);
		}

		// Returns a std::string representation of the Rect.
		std::string toString() const
		{
			return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(width) + ", " + std::to_string(height);
		}
	};

	// Checks if there is an intersection between the given Rectangles.
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
	return (A.x == B.x) && (A.y == B.y) && (A.width == B.width) && (A.height == B.height);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Rect<T>& A, const jlib::Rect<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.width != B.width) || (A.height != B.height);
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Rect<T>& A)
{
	os << A.toString();
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std_arithmetic T> class Circle
	{
		public:

		T x;
		T y;
		T radius;

		// Default constructor.
		// Sets the x component of the center of the Circle to 0.
		// Sets the y component of the center of the Circle to 0.
		// Sets the radius of the Circle to 0.
		Circle()
		{
			radius = static_cast<T>(0);
		}

		// 3-parameter constructor.
		// Sets the x component of the center of the Circle to X.
		// Sets the y component of the center of the Circle to Y.
		// Sets the radius of the Circle to Radius.
		Circle(T X, T Y, T Radius)
		{
			x = X;
			y = Y;
			radius = Radius;
		}

		// Point constructor.
		// Sets the center of the Circle to the given point.
		// Sets the radius of the Circle to Radius.
		Circle(const Vector2<T>& Center, T Radius)
		{
			x = Center.x;
			y = Center.y;
			radius = Radius;
		}

		// Constructs the Circle from another type of Circle.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		explicit Circle(const Circle<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			radius = static_cast<T>(other.radius);
		}

		// Sets all the values of the Circle at once.
		// Sets the x component of the center of the Circle to X.
		// Sets the y component of the center of the Circle to Y.
		// Sets the radius of the Circle to Radius.
		void set(T X, T Y, T Radius)
		{
			x = X;
			y = Y;
			radius = Radius;
		}

		// Sets all the values of the Circle at once.
		// Sets the center of the Circle to the given point.
		// Sets the radius of the Circle to Radius.
		void set(const Vector2<T>& Center, T Radius)
		{
			x = Center.x;
			y = Center.y;
			radius = Radius;
		}

		// Returns the circumference of the Circle.
		float circumference() const
		{
			return 2.f * 3.1415927f * std::fabsf(radius);
		}

		// Returns the area of the Circle.
		float area() const
		{
			return 3.1415927f * std::powf(std::fabsf(radius), 2.f);
		}

		// Checks if the given point lies within or on the Circle.
		template <std_arithmetic U>
		bool contains(T X, T Y)
		{
			return std::powf(X - x, 2.f) + std::powf(Y - y, 2.f) <= std::powf(std::fabsf(radius), 2.f);
		}

		// Checks if the given point lies within or on the Circle.
		template <std_arithmetic U>
		bool contains(const Vector2<U>& P)
		{
			return std::powf(P.x - x, 2.f) + std::powf(P.y - y, 2.f) <= std::powf(std::fabsf(radius), 2.f);
		}

		// Returns a std::string representation of the Circle.
		std::string toString() const
		{
			return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(std::fabsf(radius));
		}
	};

	// Checks if there is an intersection between the given Circles.
	template <std_arithmetic T>
	bool intersection(const Circle<T>& A, const Circle<T>& B)
	{
		return std::powf(std::fabsf(A.radius) + std::fabsf(B.radius), 2.f) <= (std::powf(B.x - A.x, 2.f) + std::powf(B.y - A.y, 2.f));
	}
}

// Overload of binary operator == 
template <jlib::std_arithmetic T>
bool operator == (const jlib::Circle<T>& A, const jlib::Circle<T>& B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.radius == B.radius);
}

// Overload of binary operator != 
template <jlib::std_arithmetic T>
bool operator != (const jlib::Circle<T>& A, const jlib::Circle<T>& B)
{
	return (A.x != B.x) || (A.y != B.y) || (A.radius != B.radius);
}

// Overload of std::ostream operator <<
template <jlib::std_arithmetic T>
std::ostream& operator << (std::ostream& os, const jlib::Circle<T>& A)
{
	os << A.toString();
	return os;
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
	};

	// Overload of binary operator ==
	template <std_arithmetic T>
	bool operator == (const Triangle<T>& T1, const Triangle<T>& T2)
	{
		return (T1.A == T2.A) && (T1.B == T2.B) && (T1.C == T2.C);
	}

	// Overload of binary operator !=
	template <std_arithmetic T>
	bool operator != (const Triangle<T>& T1, const Triangle<T>& T2)
	{
		return (T1.A != T2.A) || (T1.B != T2.B) || (T1.C != T2.C);
	}

	// Overload of std::ostream operator << 
	template <std_arithmetic T>
	std::ostream& operator << (std::ostream& os, const Triangle<T>& A)
	{
		os << A.toString();
		return os;
	}
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

///////////////////////////////////////////////////////////////////////////////////////////////////
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

		// Overload of binary operator +
		Ptr operator + (std::ptrdiff_t offset)
		{
			return Ptr(_ptr + offset);
		}

		// Overload of binary operator -
		Ptr operator - (std::ptrdiff_t offset)
		{
			return Ptr(_ptr - offset);
		}

		// Overload of binary operator -
		std::ptrdiff_t operator - (const Ptr& other)
		{
			return _ptr - other._ptr;
		}

		// Overload of binary operator -
		std::ptrdiff_t operator - (const T* ptr)
		{
			return _ptr - ptr;
		}

		// Overload of binary operator +=
		Ptr& operator += (std::ptrdiff_t offset)
		{
			_ptr += offset;
			return *this;
		}

		// Overload of binary operator -=
		Ptr& operator -= (std::ptrdiff_t offset)
		{
			_ptr -= offset;
			return *this;
		}

		// Overload of binary operator ==
		bool operator == (const Ptr& other)
		{
			return _ptr == other._ptr;
		}

		// Overload of binary operator ==
		bool operator == (const T* ptr)
		{
			return _ptr == ptr;
		}

		// Overload of binary operator ==
		bool operator == (std::nullptr_t)
		{
			return _ptr == nullptr;
		}

		// Overload of binary operator !=
		bool operator != (const Ptr& other)
		{
			return _ptr != other._ptr;
		}

		// Overload of binary operator !=
		bool operator != (const T* ptr)
		{
			return _ptr != ptr;
		}

		// Overload of binary operator !=
		bool operator != (std::nullptr_t)
		{
			return _ptr != nullptr;
		}

		// Overload of binary operator <
		bool operator < (const Ptr& other)
		{
			return _ptr < other._ptr;
		}

		// Overload of binary operator <
		bool operator < (const T* ptr)
		{
			return _ptr < ptr;
		}

		// Overload of binary operator <=
		bool operator <= (const Ptr& other)
		{
			return _ptr <= other._ptr;
		}

		// Overload of binary operator <=
		bool operator <= (const T* ptr)
		{
			return _ptr <= ptr;
		}

		// Overload of binary operator >
		bool operator > (const Ptr& other)
		{
			return _ptr > other._ptr;
		}

		// Overload of binary operator >
		bool operator > (const T* ptr)
		{
			return _ptr > ptr;
		}

		// Overload of binary operator >=
		bool operator >= (const Ptr& other)
		{
			return _ptr >= other._ptr;
		}

		// Overload of binary operator >=
		bool operator >= (const T* ptr)
		{
			return _ptr >= ptr;
		}

		// Overload of binary operator <=>
		std::strong_ordering operator <=> (const Ptr& other)
		{
			return _ptr <=> other._ptr;
		}

		// Overload of binary operator <=>
		std::strong_ordering operator <=> (const T* ptr)
		{
			return _ptr <=> ptr;
		}
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	template <std::semiregular T> class Array
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using iterator = T*;
		using const_iterator = const T*;

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

		// 
		void copyFrom(const_pointer src_begin, size_type count)
		{
			std::memcpy(_data, src_begin, count);
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
			copyFrom(begin, size);
		}

		// std::initializer_list constructor.
		Array(std::initializer_list<T> elems)
		{
			allocate(elems.size());

			size_type i(0);
			for (const value_type& elem : elems)
				_data[i++] = elem;
		}

		// Copy constructor.
		Array(const Array& other)
		{
			allocate(other._size);
			copyFrom(other._data, _size);
		}

		// Constructs the Array from another type of Array.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::semiregular U>
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

			size_type i(0);
			for (const value_type& elem : elems)
				_data[i++] = elem;
		}

		// Copy assignment operator.
		Array& operator = (const Array& other)
		{
			reallocate(other._size);
			copyFrom(other._data, _size);
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
		constexpr size_type size() const noexcept
		{
			return _size;
		}

		// Returns true if the Array is empty.
		constexpr bool isEmpty() const noexcept
		{
			return _size != 0;
		}

		// Returns the underlying array pointer.
		pointer data() noexcept
		{
			return _data;
		}

		// Returns the underlying array pointer.
		const_pointer data() const noexcept
		{
			return _data;
		}

		// 
		iterator begin() noexcept
		{
			return iterator(_data);
		}

		// 
		const_iterator begin() const noexcept
		{
			return const_iterator(_data);
		}

		// 
		const_iterator cbegin() const noexcept
		{
			return const_iterator(_data);
		}

		// 
		iterator end() noexcept
		{
			return iterator(_data + _size);
		}

		// 
		const_iterator end() const noexcept
		{
			return const_iterator(_data + _size);
		}

		// 
		const_iterator cend() const noexcept
		{
			return const_iterator(_data + _size);
		}

		// Empties the Array.
		void clear() noexcept
		{
			delete[] _data;
			_size = 0;
		}

		// Swaps the contents of this Array buffer with those of another.
		void swapWith(Array& other) noexcept
		{
			pointer this_data = _data;
			size_type this_size = _size;

			_data = other._data;
			_size = other._size;

			other._data = this_data;
			other._size = this_size;
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

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= _size)
				throw std::out_of_range("ERROR: Invalid array index.");

			return _data[index];
		}

		// Returns the element at the given index.
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

		// Returns the element at the given index.
		reference operator [] (size_type index) noexcept
		{
			return _data[index];
		}

		// Returns the element at the given index.
		const_reference operator [] (size_type index) const noexcept
		{
			return _data[index];
		}
	};
}

// Overload of binary operator ==
template <std::regular T>
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
template <std::regular T>
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
	template <std::semiregular T> class Matrix
	{
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
		using iterator = Array<T>::iterator;
		using const_iterator = Array<T>::const_iterator;

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
			std::memcpy(newarr.data(), _data.data(), size);
			_data = std::move(newarr);
		}

		// 
		void copyElements(const_pointer src_begin, pointer dst_begin, size_type count)
		{
			std::memcpy(dst_begin, src_begin, count);
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
				copyElements(elem.begin(), &(_data[row_i * _cols]), _cols);
				++row_i;
			}
		}

		// Copy constructor.
		Matrix(const Matrix& other) = default;

		// Constructs the Matrix from another type of Matrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::semiregular U>
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
				copyElements(elem.begin(), &(_data[row_i * _cols]), _cols);
				++row_i;
			}
		}

		// Copy assignment operator.
		Matrix& operator = (const Matrix& other) = default;

		// Move assignment operator.
		Matrix& operator = (Matrix&& other) = default;

		// Destructor.
		~Matrix() = default;

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		reference at(size_type n)
		{
			if (n >= _data.size())
				throw std::out_of_range("Invalid table index");

			return _data[n];
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		const_reference at(size_type n) const
		{
			if (n >= _data.size())
				throw std::out_of_range("Invalid table index");

			return _data[n];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		reference at(size_type row, size_type col)
		{
			if (row >= _rows)
				throw std::out_of_range("Invalid row index");
			if (col >= _cols)
				throw std::out_of_range("Invalid column index");

			return _data[(row * _cols) + col];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		const_reference at(size_type row, size_type col) const
		{
			if (row >= _rows)
				throw std::out_of_range("Invalid row index");
			if (col >= _cols)
				throw std::out_of_range("Invalid column index");

			return _data[(row * _cols) + col];
		}

		// Sets the nth element of the Matrix to value.
		// Performs bounds-checking.
		void set(size_type n, const_reference value)
		{
			if (n >= _data.size())
				throw std::out_of_range("Invalid table index");

			_data[n] = value;
		}

		// Sets the element at [row][col] to value.
		// Performs bounds-checking.
		void set(size_type row, size_type col, const_reference value)
		{
			if (row >= _rows)
				throw std::out_of_range("Invalid row index");
			if (col >= _cols)
				throw std::out_of_range("Invalid column index");

			_data[(row * _cols) + col] = value;
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

		// Returns the number of rows in the Matrix.
		constexpr size_type rowCount() const noexcept
		{
			return _rows;
		}

		// Returns the number of columns in the Matrix.
		constexpr size_type colCount() const noexcept
		{
			return _cols;
		}

		// Returns the number of elements in the Matrix.
		constexpr size_type size() const noexcept
		{
			return _data.size();
		}

		// Returns a copy of the given row.
		Array<T> getRow(size_type row) const
		{
			if (row >= _rows)
				throw std::out_of_range("Invalid row index");

			Array<T> arr;
			for (size_type col_i(0); col_i < _cols; ++col_i)
				arr[col_i] = _data[row][col_i];

			return arr;
		}

		// Returns a copy of the given column.
		Array<T> getCol(size_type col) const
		{
			if (col >= _cols)
				throw std::out_of_range("Invalid column index");

			Array<T> arr;
			for (size_type row_i(0); row_i < _rows; ++row_i)
				arr[row_i] = _data[row_i][col];

			return arr;
		}

		// 
		constexpr pointer data() noexcept
		{
			return _data.data();
		}

		// 
		constexpr const_pointer data() const noexcept
		{
			return _data.data();
		}

		// 
		constexpr iterator begin() noexcept
		{
			return _data.begin();
		}

		// 
		constexpr const_iterator begin() const noexcept
		{
			return _data.cbegin();
		}

		// 
		constexpr const_iterator cbegin() const noexcept
		{
			return _data.cbegin();
		}

		// 
		constexpr iterator end() noexcept
		{
			return _data.end();
		}

		// 
		constexpr const_iterator end() const noexcept
		{
			return _data.cend();
		}

		// 
		constexpr const_iterator cend() const noexcept
		{
			return _data.cend();
		}

		// 
		constexpr iterator rowBegin(size_type row) noexcept
		{
			return _data.begin() + (_cols * row);
		}

		// 
		constexpr const_iterator rowBegin(size_type row) const noexcept
		{
			return _data.cbegin() + (_cols * row);
		}

		// 
		constexpr void clear() noexcept
		{
			_data.clear();
		}

		// 
		void resize(size_type rows, size_type cols)
		{
			reallocate(rows, cols);
		}
	};
}

// Overload of binary operator == 
template <std::regular T>
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
template <std::regular T>
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
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A CMatrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <std::semiregular T, std::size_t R, std::size_t C> class CMatrix
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
		using iterator = std::array<T, R* C>::iterator;
		using const_iterator = std::array<T, R* C>::const_iterator;

		private:

		std::array<T, R * C> _data;

		// 
		void copyElements(pointer dst_begin, const_pointer src_begin, size_type count)
		{
			for (size_type i(0); i < count; ++i)
				dst_begin[i] = src_begin[i];
		}

		public:

		// Default constructor.
		CMatrix() = default;

		// 1-parameter constructor.
		// Sets every element of the CMatrix to value.
		CMatrix(const_reference value)
		{
			for (size_type i(0); i < R * C; ++i)
				_data[i] = value;
		}

		// 2-dimensional std::initializer_list constructor.
		CMatrix(std::initializer_list<std::initializer_list<T>> list)
		{
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				copyElements(&_data[row_i * C], elem.begin(), C);
				++row_i;
			}
		}

		// Copy constructor.
		CMatrix(const CMatrix& other)
		{
			copyElements(_data, other._data, R * C);
		}

		// Constructs the CMatrix from another type of CMatrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::semiregular U>
		explicit CMatrix(const CMatrix<U, R, C>& other)
		{
			for (size_type i(0); i < R * C; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Move constructor.
		CMatrix(CMatrix&& other) noexcept
		{
			_data = std::move(other._data);
		}

		// 2-dimensional std::initializer_list assignment operator.
		CMatrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				copyElements(&_data[row_i * C], elem.begin(), C);
				++row_i;
			}

			return *this;
		}

		// Copy assignment operator.
		CMatrix& operator = (const CMatrix& other)
		{
			copyElements(_data, other._data, R * C);
			return *this;
		}

		// Move assignment operator.
		CMatrix& operator = (CMatrix&& other) noexcept
		{
			_data = std::move(other._data);
		}

		// Returns the nth element of the CMatrix.
		// Performs bounds-checking.
		reference at(size_type n)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return _data[n];
		}

		// Returns the nth element of the CMatrix.
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

		// Sets the nth element of the CMatrix to value.
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

		// Returns the nth element of the CMatrix.
		reference operator [] (size_type n)
		{
			return _data[n];
		}

		// Returns the nth element of the CMatrix.
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

		// Returns the number of rows in the CMatrix.
		size_type rowCount() const
		{
			return R;
		}

		// Returns the number of columns in the CMatrix.
		size_type colCount() const
		{
			return C;
		}

		// Returns the number of elements in the CMatrix.
		size_type size() const
		{
			return R * C;
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
		CMatrix<T, R2, C2> submatrix(size_type row_begin, size_type col_begin) const
		{
			if (row_begin >= R || row_begin + R2)
				throw std::out_of_range("Invalid row index.");
			if (col_begin >= C || col_begin + C >= C2)
				throw std::out_of_range("Invalid column index.");

			CMatrix<T, R2, C2> M;

			for (size_type row_i(0); row_i < R2; ++row_i)
			{
				for (size_type col_i(0); col_i < C2; ++col_i)
					M._data[(row_i * C) + col_i] = _data[(row_i * C) + col_i];
			}

			return M;
		}

		// 
		pointer data()
		{
			return &(_data[0]);
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
	};

	// Returns the determinant of the 2x2 CMatrix formed as
	// {  a,  b  }
	// {  c,  d  }
	template <std_arithmetic T>
	inline T determinant(T a, T b, T c, T d)
	{
		return (a * d) - (b * c);
	}

	// Returns the determinant of the 2x2 CMatrix.
	template <std_arithmetic T>
	inline T determinant(const CMatrix<T, 2, 2>& M)
	{
		return (M(0, 0) * M(1, 1)) - (M(1, 0) * M(0, 1));
	}

	// Returns the determinant of the 3x3 CMatrix.
	template <std_arithmetic T>
	T determinant(const CMatrix<T, 3, 3>& M)
	{
		T A = M(0, 0) * determinant(M(1, 1), M(1, 2), M(2, 1), M(2, 2));
		T B = M(0, 1) * determinant(M(1, 0), M(1, 2), M(2, 0), M(2, 2));
		T C = M(0, 2) * determinant(M(1, 0), M(1, 1), M(2, 0), M(2, 1));

		return A - B + C;
	}

	// Returns the determinant of the 4x4 CMatrix.
	template <std_arithmetic T>
	T determinant(const CMatrix<T, 4, 4>& M)
	{
		CMatrix<T, 3, 3> A =
		{
			{ M(1, 1), M(1, 2), M(1, 3) },
			{ M(2, 1), M(2, 2), M(2, 3) },
			{ M(3, 1), M(3, 2), M(3, 3) }
		};

		CMatrix<T, 3, 3> B =
		{
			{ M(1, 0), M(1, 2), M(1, 3) },
			{ M(2, 0), M(2, 2), M(2, 3) },
			{ M(3, 0), M(3, 2), M(3, 3) }
		};

		CMatrix<T, 3, 3> C =
		{
			{ M(1, 0), M(1, 1), M(1, 3) },
			{ M(2, 0), M(2, 1), M(2, 3) },
			{ M(3, 0), M(3, 1), M(3, 3) }
		};

		CMatrix<T, 3, 3> D =
		{
			{ M(1, 0), M(1, 1), M(1, 2) },
			{ M(2, 0), M(2, 1), M(2, 2) },
			{ M(3, 0), M(3, 1), M(3, 2) }
		};

		return M(0, 0) * determinant(A) - M(0, 1) * determinant(B) + M(0, 2) * determinant(C) - M(0, 3) * determinant(D);
	}

	// Returns the dot product of the given Matrices.
	template <std_arithmetic T, std::size_t R, std::size_t C, std::size_t S>
	CMatrix<T, R, S> dot_product(const CMatrix<T, R, C>& A, const CMatrix<T, C, S>& B)
	{
		CMatrix<T, R, S> M;
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
template <std::regular T, std::size_t R, std::size_t C>
bool operator == (const jlib::CMatrix<T, R, C>& A, const jlib::CMatrix<T, R, C>& B)
{
	for (std::size_t i(0); i < R * C; ++i)
	{
		if (A[i] != B[i])
			return false;
	}

	return true;
}

// Overload of binary operator != 
template <std::regular T, std::size_t R, std::size_t C>
bool operator != (const jlib::CMatrix<T, R, C>& A, const jlib::CMatrix<T, R, C>& B)
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
jlib::CMatrix<T, R, C> operator - (const jlib::CMatrix<T, R, C>& A)
{
	jlib::CMatrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * static_cast<T>(-1);
	}

	return M;
}

// Overload of binary operator +
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::CMatrix<T, R, C> operator + (const jlib::CMatrix<T, R, C>& A, const jlib::CMatrix<T, R, C>& B)
{
	jlib::CMatrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) + B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator -
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::CMatrix<T, R, C> operator - (const jlib::CMatrix<T, R, C>& A, const jlib::CMatrix<T, R, C>& B)
{
	jlib::CMatrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) - B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::CMatrix<T, R, C> operator * (const jlib::CMatrix<T, R, C>& A, U scalar)
{
	jlib::CMatrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * scalar;
	}

	return M;
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::CMatrix<T, R, C> operator / (const jlib::CMatrix<T, R, C>& A, U scalar)
{
	jlib::CMatrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) / scalar;
	}

	return M;
}

// Overload of binary operator +=
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::CMatrix<T, R, C>& operator += (jlib::CMatrix<T, R, C>& A, const jlib::CMatrix<T, R, C>& B)
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
jlib::CMatrix<T, R, C>& operator -= (jlib::CMatrix<T, R, C>& A, const jlib::CMatrix<T, R, C>& B)
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
jlib::CMatrix<T, R, C>& operator *= (jlib::CMatrix<T, R, C>& M, U scalar)
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
jlib::CMatrix<T, R, C>& operator /= (jlib::CMatrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) /= scalar;
	}

	return M;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	class Transformation
	{
		CMatrix<float, 4, 4> _matrix;

		public:

		static const Transformation Identity;

		// Default constructor.
		Transformation();

		// Constructs a transformation from a 3x3 matrix.
		Transformation(float a, float b, float c, float d, float e, float f, float g, float h, float i);

		// Returns the transformation as a 4x4 matrix.
		const CMatrix<float, 4, 4>& getMatrix() const;

		// Returns the inverse of the transformation.
		Transformation getInverse() const;

		// Transforms a 2D point.
		Vector2f transformPoint(float x, float y) const;

		// Transforms a 2D point.
		Vector2f transformPoint(const Vector2f& point) const;

		// Transforms a rectangle.
		FloatRect transformRect(const FloatRect& rectangle) const;

		// Combines the current transformation with another one.
		Transformation& combine(const Transformation& other);

		// Combines the current transformation with a translation.
		Transformation& translate(float offset_x, float offset_y);

		// Combines the current transformation with a translation.
		Transformation& translate(const Vector2f& offset);

		// Combines the current transformation with a rotation.
		Transformation& rotate(Angle angle);

		// Combines the current transformation with a rotation.
		Transformation& rotate(Angle angle, float center_x, float center_y);

		// Combines the current transformation with a rotation.
		Transformation& rotate(Angle angle, const Vector2f& center);

		// Combines the current transformation with a scaling.
		Transformation& scale(float scale_x, float scale_y);

		// Combines the current transformation with a scaling.
		Transformation& scale(float scale_x, float scale_y, float center_x, float center_y);

		// Combines the current transformation with a scaling.
		Transformation& scale(const Vector2f& scalar);

		// Combines the current transformation with a scaling.
		Transformation& scale(const Vector2f& scalar, const Vector2f& center);
	};
}

// Overload of binary operator *
jlib::Transformation operator * (const jlib::Transformation& A, const jlib::Transformation& B);

// Overload of binary operator *=
jlib::Transformation& operator *= (const jlib::Transformation& A, const jlib::Transformation& B);

// Overload of binary operator *
jlib::Vector2f operator * (const jlib::Transformation& A, const jlib::Vector2f& B);

// Overload of binary operator ==
bool operator == (const jlib::Transformation& A, const jlib::Transformation& B);

// Overload of binary operator !=
bool operator != (const jlib::Transformation& A, const jlib::Transformation& B);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	class Keyboard
    {
        public:

        enum Key : u8
        {
			NONE       = 0,
			A          = 1, 
			B          = 2, 
			C          = 3, 
			D          = 4, 
			E          = 5, 
			F          = 6, 
			G          = 7, 
			H          = 8, 
			I          = 9, 
			J          = 10, 
			K          = 11,
			L          = 12, 
			M          = 13, 
			N          = 14, 
			O          = 15,
			P          = 16, 
			Q          = 17, 
			R          = 18, 
			S          = 19, 
			T          = 20, 
			U          = 21, 
			V          = 22, 
			W          = 23,
			X          = 24, 
			Y          = 25, 
			Z          = 26,
			Num0       = 27,
			Num1       = 28,
			Num2       = 29,
			Num3       = 30,
			Num4       = 31,
			Num5       = 32,
			Num6       = 33,
			Num7       = 34,
			Num8       = 35,
			Num9       = 36,
			F1         = 37, 
			F2         = 38, 
			F3         = 39, 
			F4         = 40, 
			F5         = 41, 
			F6         = 42, 
			F7         = 43, 
			F8         = 44, 
			F9         = 45, 
			F10        = 46, 
			F11        = 47, 
			F12        = 48,
			F13        = 49,
			F14        = 50,
			F15        = 51,
			Escape     = 52,
			LControl   = 53,
			LShift     = 54,
			LAlt       = 55,
			LWindow    = 56,
			RControl   = 57,
			RShift     = 58,
			RAlt       = 59,
			RWindow    = 60,
			Menu       = 61,
			LBracket   = 62,
			RBracket   = 63,
			Semicolon  = 64,
			Comma      = 65,
			Period     = 66,
			Quote      = 67,
			Slash      = 68,
			Backslash  = 69,
			Tilde      = 70,
			Equal      = 71,
			Hyphen     = 72,
			Space      = 73,
			Enter      = 74,
			Backspace  = 75,
			Tab        = 76,
			PageUp     = 77,
			PageDown   = 78,
			End        = 79,
			Home       = 80,
			Insert     = 81,
			Delete     = 82,
			Add        = 83,
			Subtract   = 84,
			Multiply   = 85,
			Divide     = 86,
			Left       = 87,
			Right      = 88,
			Up         = 89,
			Down       = 90,
			Numpad0    = 91,
			Numpad1    = 92,
			Numpad2    = 93,
			Numpad3    = 94,
			Numpad4    = 95,
			Numpad5    = 96,
			Numpad6    = 97,
			Numpad7    = 98,
			Numpad8    = 99,
			Numpad9    = 100,
			Pause      = 101,
			Count      = 102
		};

		// 
		static bool isKeyPressed(Key key);
	};
}	

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	class Mouse
	{
		static bool _isVisible;

		public:

		enum Button : u8
		{
			Left   = 0,
			Right  = 1,
			Middle = 2
		};

		enum Wheel : u8
		{
			Vertical   = 0,
			Horizontal = 1
		};

		//
		static bool isCursorVisible();

		// 
		static void hide();

		// 
		static void show();

		// 
		static bool isButtonPressed(Button button);

		// 
		static Vector2i getPosition();

		// 
		static void setPosition(const Vector2i& pos);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
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

		// Copy constructor.
		Joystick(const Joystick& other) = delete;

		// Move constructor.
		Joystick(Joystick&& other) = delete;

		// Copy assignment operator.
		Joystick& operator = (const Joystick& other) = delete;

		// Move assignment operator.
		Joystick& operator = (Joystick&& other) = delete;

		// Sets the horizontal deadzone of the Joystick to x_dz.
		void setHorizontalDeadzone(float x_dz);

		// Sets the vertical deadzone of the Joysticl to y_dz.
		void setVerticalDeadzone(float y_dz);

		// Sets the horizontal deadzone of the Joystick to x_dz.
		// Sets the vertical deadzone of the Joysticl to y_dz.
		void setDeadzones(float x_dz, float y_dz);

		// Returns true if the Joystick's position is within its deadzone.
		bool isStickInDeadZone() const;
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	class Gamepad
	{
		public:

		enum Button
		{
			A           = XINPUT_GAMEPAD_A,
			B           = XINPUT_GAMEPAD_B,
			X           = XINPUT_GAMEPAD_X,
			Y           = XINPUT_GAMEPAD_Y,
			DPadUp      = XINPUT_GAMEPAD_DPAD_UP,
			DPadDown    = XINPUT_GAMEPAD_DPAD_DOWN,
			DPadLeft    = XINPUT_GAMEPAD_DPAD_LEFT,
			DPadRight   = XINPUT_GAMEPAD_DPAD_RIGHT,
			LShoulder   = XINPUT_GAMEPAD_LEFT_SHOULDER,
			RShoulder   = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			LThumbstick = XINPUT_GAMEPAD_LEFT_THUMB,
			RThumbstick = XINPUT_GAMEPAD_RIGHT_THUMB,
			Start       = XINPUT_GAMEPAD_START,
			Back        = XINPUT_GAMEPAD_BACK,
			Count       = 14
		};

		private:

		u8 _port;
		XINPUT_STATE _state;

		int getXInputValue(Button button);

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

		// Copy constructor.
		Gamepad(const Gamepad& other) = delete;

		// Move constructor.
		Gamepad(Gamepad&& other) = delete;

		// Copy assignment operator.
		Gamepad& operator = (const Gamepad& other) = delete;

		// Move assignment operator.
		Gamepad& operator = (Gamepad&& other) = delete;

		// 
		bool isConnected();

		// 
		u8 getPort() const;

		// 
		XINPUT_STATE getState() const;

		// 
		bool isButtonPressed(Button button) const;

		// 
		void update();
	};
}

// Overload of binary operator ==
bool operator == (const jlib::Gamepad& A, const jlib::Gamepad& B);

// Overload of binary operator !=
bool operator != (const jlib::Gamepad& A, const jlib::Gamepad& B);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// Gives access to the system clipboard.
	class Clipboard
	{
		public:

		// Gets the content of the clipboard as std::string data.
		// This function returns the content of the clipboard
		// as a string. If the clipboard does not contain string
		// it returns an empty std::string object.
		static std::string getString();

		// Gets the content of the clipboard as std::wstring data.
		// This function returns the content of the clipboard
		// as a string. If the clipboard does not contain string
		// it returns an empty std::wstring object.
		static std::wstring getWideString();

		// Sets the content of the clipboard as std::string data.
		// This function sets the content of the clipboard as a std::string.
		static void setString(const std::string& text);

		// Sets the content of the clipboard as std::wstring data.
		// This function sets the content of the clipboard as a std::wstring.
		static void setWideString(const std::wstring& text);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	class Color
	{
		public:

		static const u8 MAX = 0xff;

		enum : u32
		{
			Black     = 0x000000ff,
			White     = 0xffffffff,
			Red       = 0xff0000ff,
			Green     = 0x00ff00ff,
			Blue      = 0x0000ffff,
			Cyan      = 0x00ffffff,
			Magenta   = 0xff00ffff,
			Yellow    = 0xffff00ff,
			Silver    = 0xc0c0c0ff,
			Gray      = 0x808080ff,
			Maroon    = 0x800000ff,
			Olive     = 0x808000ff,
			DarkGreen = 0x008000ff,
			Purple    = 0x800080ff,
			Teal      = 0x008080ff,
			Navy      = 0x000080ff,
			Clear     = 0x00000000
		};

		enum Mode
		{
			Normal = 0,
			Mask   = 1,
			Alpha  = 2,
			Custom = 3
		};

		u8 r, g, b, a;

		// Default constructor.
		// Sets each component of the Color to 0.
		Color();

		// Primary constructor.
		// Sets the red component of the Color to R.
		// Sets the green component of the Color to G.
		// Sets the blue component of the Color to B.
		// Sets the alpha component of the Color to A.
		Color(u8 R, u8 G, u8 B, u8 A = MAX);

		// Secondary constructor.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color(u32 color);

		// std::array constructor.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color(const std::array<u8, 4>& arr);

		// std::initializer_list constructor.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color(std::initializer_list<u8> list);

		// unsigned int assignment operator.
		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		Color& operator = (u32 color);

		// std::array assignment operator.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color& operator = (const std::array<u8, 4>& arr);

		// std::initializer_list assignment operator.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		Color& operator = (std::initializer_list<u8> list);

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to R.
		// Sets the green component of the Color to G.
		// Sets the blue component of the Color to B.
		// Sets the alpha component of the Color to A.
		void set(u8 R, u8 G, u8 B, u8 A);

		// Calculates each byte of the given color and sets
		// this color to the corresponding values.
		void set(u32 color);

		// Sets all the values of the Color at once.
		// Sets the red component of the Color to the 1st element.
		// Sets the green component of the Color to the 2nd element.
		// Sets the blue component of the Color to the 3rd element.
		// Sets the alpha component of the Color to the 4th element.
		void set(const std::array<u8, 4>& arr);

		// Returns a 32-but unsigned integer representation of the Color.
		u32 toInt() const;

		// Returns a std::array copy of the Color's components.
		std::array<u8, 4> toArray() const;

		// Returns a std::string representation of the Color.
		std::string toString() const;
	};

	// Returns the individual bytes of the unsigned int.
	std::array<u8, 4> to_bytes(u32 i);

	// Returns a hexadecimal std::string representation of the byte.
	std::string to_hex_str(u8 byte);

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