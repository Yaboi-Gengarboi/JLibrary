////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Fraction.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-07-03 by Justyn Durnford
// Header file for the Fraction template class.

#pragma once

#include <JLibrary/System/StringConvert.hpp>
#include <compare>

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

		// 1-int assignment operator.
		// Sets the numerator of the Fraction to Numer.
		// Sets the denominator of the Fraction to 1.
		Fraction& operator = (T Numer)
		{
			numer = Numer;
			denom = static_cast<T>(1);
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

		// Returns a std::wstring representation of the Fraction.
		std::wstring toWideString() const
		{
			return str_to_wstr(toString());
		}

		// Returns a std::u32string representation of the Fraction.
		std::u32string toU32String() const
		{
			return str_to_u32str(toString());
		}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

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

	return std::strong_ordering::equal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

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

// Overloaf of binary operator *=
template <std::integral T>
jlib::Fraction<T>& operator *= (jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	A.numer *= B.numer;
	A.denom *= B.denom;
	return A;
}

// Overloaf of binary operator *=
template <std::integral T, std::integral U>
jlib::Fraction<T>& operator *= (jlib::Fraction<T>& A, U value)
{
	A.numer *= value;
	return A;
}

// Overloaf of binary operator /=
template <std::integral T>
jlib::Fraction<T>& operator /= (jlib::Fraction<T>& A, const jlib::Fraction<T>& B)
{
	A.numer *= B.denom;
	A.denom *= B.numer;
	return A;
}

// Overloaf of binary operator /=
template <std::integral T, std::integral U>
jlib::Fraction<T>& operator /= (jlib::Fraction<T>& A, U value)
{
	A.denom *= value;
	return A;
}