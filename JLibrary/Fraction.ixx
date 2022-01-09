// JLibrary
// Fraction.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the Fraction template class.

module;

#include <cmath>
#include <compare>
#include <concepts>
#include <ostream>
#include <string>

export module Fraction;

export namespace jlib
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

			numer = std::pow(numer, N);
			denom = std::pow(denom, N);
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
		if (A.result() < B.result())
			return std::strong_ordering::less;

		if (A.result() > B.result())
			return std::strong_ordering::greater;

		return std::strong_ordering::equal;
	}

	// Overload of binary operator <=>
	template <std::integral T>
	std::strong_ordering operator <=> (const Fraction<T>& A, float B)
	{
		if (A.result() < B)
			return std::strong_ordering::less;

		if (A.result() > B)
			return std::strong_ordering::greater;

		return std::strong_ordering::equivalent;
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
	Fraction<T>& operator += (Fraction<T>& A, T value)
	{
		A += Fraction<T>(value);
		return A;
	}

	// Overload of binary operator -=
	template <std::integral T>
	Fraction<T>& operator -= (Fraction<T>& A, const Fraction<T>& B)
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
	Fraction<T>& operator -= (Fraction<T>& A, T value)
	{
		A -= Fraction<T>(value);
		return A;
	}

	// Overload of binary operator *=
	template <std::integral T>
	Fraction<T>& operator *= (Fraction<T>& A, const Fraction<T>& B)
	{
		A.numer *= B.numer;
		A.denom *= B.denom;
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
		A.numer *= B.denom;
		A.denom *= B.numer;
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
	std::ostream& operator << (std::ostream& os, const Fraction<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator << 
	template <std::integral T>
	std::wostream& operator << (std::wostream& wos, const Fraction<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}