// JLibrary
// Fraction.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-04-19 by Justyn Durnford
// Module file for the Fraction template struct.

module;

#include "Arithmetic.hpp"

#include <cmath>
#include <compare>
#include <concepts>
#include <iostream>
#include <string>

export module Fraction;

export namespace jlib
{
	// This struct provides an "exact" representation of the quotient of two 
	// integers by storing them and allowing fraction arithmetic with them. 
	// Use the member function result() to obtain the result of the fraction.
	template <std::integral T> struct Fraction
	{
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

		// Copies the components of a different type of Fraction.
		template <std::integral U>
		void copyFrom(const Fraction<U>& other)
		{
			numer = static_cast<T>(other.numer);
			denom = static_cast<T>(other.denom);
		}

		// Adds the given Fraction onto this one.
		void add(const Fraction& other)
		{
			if (denom == other.denom)
				numer += other.numer;
			else
			{
				T old_denom = denom;

				numer *= other.denom;
				denom *= other.denom;

				numer += other.numer * old_denom;
			}
		}

		// Subtracts the given Fraction onto this one.
		void subtract(const Fraction& other)
		{
			if (denom == other.denom)
				numer -= other.numer;
			else
			{
				T old_denom = denom;

				numer *= other.denom;
				denom *= other.denom;

				numer -= other.numer * old_denom;
			}
		}

		// Multiplies the given Fraction onto this one.
		void multiply(const Fraction& other)
		{
			numer *= other.numer;
			denom *= other.denom;
		}

		// Divides the given Fraction onto this one.
		void divide(const Fraction& other)
		{
			numer *= other.denom;
			denom *= other.numer;
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

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Returns a Fraction whose elements are the absolute values of 
	// each of the specified Fraction elements.
	template <arithmetic T>
	inline Fraction<T> abs(const Fraction<T>& frac)
	{
		return Fraction<T>(std::abs(frac.numer), std::abs(frac.denom));
	}

	// Compares the given Fractions and returns a std::strong_ordering 
	// describing the comparison.
	template <arithmetic T>
	inline std::strong_ordering compare(const Fraction<T>& A, const Fraction<T>& B)
	{
		return result(A) <=> result(B);
	}

	// Returns true if the denominator of the Fraction is NOT 0.
	template <arithmetic T>
	constexpr bool is_valid(const Fraction<T>& frac)
	{
		return frac.denom != 0;
	}

	// Returns the given Fraction raised to the given power.
	template <std::integral T, std::unsigned_integral U>
	inline Fraction<T> pow(const Fraction<T>& frac, U power)
	{
		return Fraction<T>(std::pow(frac.numer, power), std::pow(frac.denom, power));
	}

	// Prints the given Fraction to the std::cout ostream.
	template <std::integral T>
	inline void print(const Fraction<T>& frac)
	{
		std::cout << to_string(frac);
	}

	// Prints the given Fraction to the std::cout ostream with a newline.
	template <std::integral T>
	inline void println(const Fraction<T>& frac)
	{
		std::cout << to_string(frac) << '\n';
	}

	// Returns the result of the given Fraction as a float.
	// This function may throw if a division by 0 is attempted.
	template <std::integral T>
	constexpr float result(const Fraction<T>& frac)
	{
		return static_cast<float>(frac.numer) / static_cast<float>(frac.denom);
	}

	// Returns a std::string representation of the given Fraction.
	template <arithmetic T>
	inline std::string to_string(const Fraction<T>& frac)
	{
		return std::to_string(frac.numer) + " / " + std::to_string(frac.denom);
	}

	// Returns a std::wstring representation of the given Fraction.
	template <arithmetic T>
	inline std::wstring to_wstring(const Fraction<T>& frac)
	{
		return std::to_wstring(frac.numer) + L" / " + std::to_wstring(frac.denom);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <std::integral T>
	bool operator == (const Fraction<T>& A, const Fraction<T>& B)
	{
		return A.result() == B.result();
	}

	// Overload of binary operator ==
	template <std::integral T>
	bool operator == (const Fraction<T>& A, float B)
	{
		return A.result() == B;
	}

	// Overload of binary operator !=
	template <std::integral T>
	bool operator != (const Fraction<T>& A, const Fraction<T>& B)
	{
		return A.result() != B.result();
	}

	// Overload of binary operator !=
	template <std::integral T>
	bool operator != (const Fraction<T>& A, float B)
	{
		return A.result() != B;
	}

	// Overload of binary operator >
	template <std::integral T>
	bool operator > (const Fraction<T>& A, const Fraction<T>& B)
	{
		return A.result() > B.result();
	}

	// Overload of binary operator >
	template <std::integral T>
	bool operator > (const Fraction<T>& A, float B)
	{
		return A.result() > B;
	}

	// Overload of binary operator >=
	template <std::integral T>
	bool operator >= (const Fraction<T>& A, const Fraction<T>& B)
	{
		return A.result() >= B.result();
	}

	// Overload of binary operator >=
	template <std::integral T>
	bool operator >= (const Fraction<T>& A, float B)
	{
		return A.result() >= B;
	}

	// Overload of binary operator <
	template <std::integral T>
	bool operator < (const Fraction<T>& A, const Fraction<T>& B)
	{
		return A.result() < B.result();
	}

	// Overload of binary operator <
	template <std::integral T>
	bool operator < (const Fraction<T>& A, float B)
	{
		return A.result() < B;
	}

	// Overload of binary operator <=
	template <std::integral T>
	bool operator <= (const Fraction<T>& A, const Fraction<T>& B)
	{
		return A.result() <= B.result();
	}

	// Overload of binary operator <=
	template <std::integral T>
	bool operator <= (const Fraction<T>& A, float B)
	{
		return A.result() <= B;
	}

	// Overload of binary operator <=>
	template <std::integral T>
	std::strong_ordering operator <=> (const Fraction<T>& A, const Fraction<T>& B)
	{
		return result(A) <=> result(B);
	}

	// Overload of binary operator <=>
	template <std::integral T>
	std::strong_ordering operator <=> (const Fraction<T>& A, float B)
	{
		return result(A) <=> B;
	}

	// Overload of unary operator -
	template <std::integral T>
	Fraction<T> operator - (const Fraction<T>& A)
	{
		return Fraction<T>(-A.numer, -A.denom);
	}

	// Overload of binary operator +
	template <std::integral T>
	Fraction<T> operator + (const Fraction<T>& A, const Fraction<T>& B)
	{
		if (A.denom == B.denom)
			return Fraction<T>(A.numer + B.numer, A.denom);
		// else if (A.denom != B.denom)
		return Fraction<T>(A.numer * B.denom + B.numer * A.denom, A.denom * B.denom);
	}

	// Overload of binary operator +
	template <std::integral T>
	Fraction<T> operator + (const Fraction<T>& A, T value)
	{
		return A + Fraction<T>(value);
	}

	// Overload of binary operator -
	template <std::integral T>
	Fraction<T> operator - (const Fraction<T>& A, const Fraction<T>& B)
	{
		if (A.denom == B.denom)
			return Fraction<T>(A.numer - B.numer, A.denom);
		// else if (A.denom != B.denom)
		return Fraction<T>(A.numer * B.denom - B.numer * A.denom, A.denom * B.denom);
	}

	// Overload of binary operator -
	template <std::integral T>
	Fraction<T> operator - (const Fraction<T>& A, T value)
	{
		return A - Fraction<T>(value);
	}

	// Overload of binary operator *
	template <std::integral T>
	Fraction<T> operator * (const Fraction<T>& A, const Fraction<T>& B)
	{
		return Fraction<T>(A.numer * B.numer, A.denom * B.denom);
	}

	// Overload of binary operator *
	template <std::integral T>
	Fraction<T> operator * (const Fraction<T>& A, T value)
	{
		return Fraction<T>(A.numer * value, A.denom * value);
	}

	// Overload of binary operator *
	template <std::integral T>
	Fraction<T> operator * (T value, const Fraction<T>& A)
	{
		return value * A.result();
	}

	// Overload of binary operator /
	template <std::integral T>
	Fraction<T> operator / (const Fraction<T>& A, const Fraction<T>& B)
	{
		return Fraction<T>(A.numer * B.denom, A.denom * B.numer);
	}

	// Overload of binary operator /
	template <std::integral T>
	Fraction<T> operator / (const Fraction<T>& A, T value)
	{
		return Fraction<T>(A.numer, A.denom * value);
	}

	// Overload of binary operator /
	template <std::integral T>
	Fraction<T> operator / (T value, const Fraction<T>& A)
	{
		return value / A.result();
	}

	// Overload of binary operator +=
	template <std::integral T>
	Fraction<T>& operator += (Fraction<T>& A, const Fraction<T>& B)
	{
		A.add(B);
		return A;
	}

	// Overload of binary operator +=
	template <std::integral T>
	Fraction<T>& operator += (Fraction<T>& A, T value)
	{
		A += Fraction<T>(value);
		return A;
	}

	// Overload of binary operator -=
	template <std::integral T>
	Fraction<T>& operator -= (Fraction<T>& A, const Fraction<T>& B)
	{
		A.subtract(B);
		return A;
	}

	// Overload of binary operator -=
	template <std::integral T>
	Fraction<T>& operator -= (Fraction<T>& A, T value)
	{
		A -= Fraction<T>(value);
		return A;
	}

	// Overload of binary operator *=
	template <std::integral T>
	Fraction<T>& operator *= (Fraction<T>& A, const Fraction<T>& B)
	{
		A.multiply(B);
		return A;
	}

	// Overload of binary operator *=
	template <std::integral T, std::integral U>
	Fraction<T>& operator *= (Fraction<T>& A, U value)
	{
		A.numer *= value;
		return A;
	}

	// Overload of binary operator /=
	template <std::integral T>
	Fraction<T>& operator /= (Fraction<T>& A, const Fraction<T>& B)
	{
		A.divide(B);
		return A;
	}

	// Overload of binary operator /=
	template <std::integral T, std::integral U>
	Fraction<T>& operator /= (Fraction<T>& A, U value)
	{
		A.denom *= value;
		return A;
	}

	// Overload of std::ostream operator << 
	template <std::integral T>
	std::ostream& operator << (std::ostream& os, const Fraction<T>& frac)
	{
		os << to_string(frac);
		return os;
	}

	// Overload of std::wostream operator << 
	template <std::integral T>
	std::wostream& operator << (std::wostream& wos, const Fraction<T>& frac)
	{
		wos << to_wstring(frac);
		return wos;
	}
}