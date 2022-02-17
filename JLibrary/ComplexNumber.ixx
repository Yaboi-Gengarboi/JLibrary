// JLibrary
// ComplexNumber.ixx
// Created on 2022-02-02 by Justyn Durnford
// Last modified on 2022-02-03 by Justyn Durnford
// Module file for the ComplexNumber template class.

module;

#include "Arithmetic.hpp"

#include <cmath>
#include <compare>
#include <concepts>
#include <ostream>
#include <string>

export module ComplexNumber;

export namespace jlib
{
	// 
	template <arithmetic T> class ComplexNumber
	{
		public:

		T real;
		T imag;

		// Default constructor.
		// Sets the real component of the ComplexNumber to 0.
		// Sets the imaginary component of the ComplexNumber to 0.
		ComplexNumber()
		{
			real = static_cast<T>(0);
			imag = static_cast<T>(0);
		}

		// Constructs the ComplexNumber from the given real component.
		// Sets the real component of the ComplexNumber to new_real.
		// Sets the imaginary component of the ComplexNumber to 0.
		ComplexNumber(T new_real)
		{
			real = new_real;
			imag = static_cast<T>(0);
		}

		// Constructs the ComplexNumber from the given components.
		// Sets the real component of the ComplexNumber to new_real.
		// Sets the imaginary component of the ComplexNumber to new_imag.
		ComplexNumber(T new_real, T new_imag)
		{
			real = new_real;
			imag = new_imag;
		}

		// Default copy constructor.
		ComplexNumber(const ComplexNumber& other) = default;

		// Default move constructor.
		ComplexNumber(ComplexNumber&& other) = default;

		// Constructs the ComplexNumber from another type of ComplexNumber.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit ComplexNumber(const ComplexNumber<U>& other)
		{
			real = static_cast<T>(other.real);
			imag = static_cast<T>(other.imag);
		}

		// Default copy assignment operator.
		ComplexNumber& operator = (const ComplexNumber& other) = default;

		// Default move assignment operator.
		ComplexNumber& operator = (ComplexNumber&& other) = default;

		// Assigns the ComplexNumber to the given real component.
		// Sets the real component of the ComplexNumber to new_real.
		// Sets the imaginary component of the ComplexNumber to 0.
		ComplexNumber& operator = (T new_real)
		{
			real = new_real;
			imag = static_cast<T>(0);
		}

		// Destructor.
		~ComplexNumber() = default;

		// Sets all the values of the ComplexNumber at once.
		// Sets the real component of the ComplexNumber to new_real.
		// Sets the imaginary component of the ComplexNumber to new_imag.
		void set(T new_real, T new_imag)
		{
			real = new_real;
			imag = new_imag;
		}

		// Copies the components of another ComplexNumber.
		void copyFrom(const ComplexNumber& other)
		{
			real = other.real;
			imag = other.imag;
		}

		// Copies the components of a different type of ComplexNumber.
		template <arithmetic U>
		void copyFrom(const ComplexNumber<U>& other)
		{
			real = static_cast<T>(other.real);
			imag = static_cast<T>(other.imag);
		}

		// Returns a std::string representation of the ComplexNumber.
		std::string toString() const
		{
			return std::to_string(real) + " + " + std::to_string(imag) + "i";
		}

		// Returns a std::wstring representation of the ComplexNumber.
		std::wstring toWideString() const
		{
			return std::to_wstring(real) + L" + " + std::to_wstring(imag) + L"i";
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	template <arithmetic T>
	ComplexNumber<T> complex_sqrt(T value)
	{
		if (value >= 0)
			return ComplexNumber<T>(std::sqrt(value));
		return ComplexNumber<T>(0, std::sqrt(std::abs(value)));
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const ComplexNumber<T>& A, const ComplexNumber<T>& B)
	{
		return (A.real == B.real) && (A.imag == B.imag);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const ComplexNumber<T>& A, const ComplexNumber<T>& B)
	{
		return (A.real != B.real) || (A.y != B.imag);
	}

	// Overload of unary operator -
	template <arithmetic T>
	ComplexNumber<T> operator - (const ComplexNumber<T>& A)
	{
		return ComplexNumber<T>(-A.real, -A.imag);
	}

	// Overload of binary operator +
	template <arithmetic T>
	ComplexNumber<T> operator + (const ComplexNumber<T>& A, const ComplexNumber<T>& B)
	{
		return ComplexNumber<T>(A.real + B.real, A.imag + B.imag);
	}

	// Overload of binary operator +
	template <arithmetic T>
	ComplexNumber<T> operator + (const ComplexNumber<T>& A, T B)
	{
		return ComplexNumber<T>(A.real + B, A.imag);
	}

	// Overload of binary operator +
	template <arithmetic T>
	ComplexNumber<T> operator + (T A, const ComplexNumber<T>& B)
	{
		return ComplexNumber<T>(B.real + A, B.imag);
	}

	// Overload of binary operator -
	template <arithmetic T>
	ComplexNumber<T> operator - (const ComplexNumber<T>& A, const ComplexNumber<T>& B)
	{
		return ComplexNumber<T>(A.real - B.real, A.imag - B.imag);
	}

	// Overload of binary operator -
	template <arithmetic T>
	ComplexNumber<T> operator - (const ComplexNumber<T>& A, T B)
	{
		return ComplexNumber<T>(A.real - B, A.imag);
	}

	// Overload of binary operator -
	template <arithmetic T>
	ComplexNumber<T> operator - (T A, const ComplexNumber<T>& B)
	{
		return ComplexNumber<T>(A - B.real, B.imag);
	}

	// Overload of binary operator *
	template <arithmetic T>
	ComplexNumber<T> operator * (const ComplexNumber<T>& A, const ComplexNumber<T>& B)
	{
		return ComplexNumber<T>((A.real * B.real) - (A.imag * B.imag), (A.real * B.imag) + (B.real * A.imag));
	}

	// Overload of binary operator *
	template <arithmetic T>
	ComplexNumber<T> operator * (const ComplexNumber<T>& A, T B)
	{
		return ComplexNumber<T>(A.real * B, A.imag * B);
	}

	// Overload of binary operator /
	template <arithmetic T>
	ComplexNumber<T> operator / (const ComplexNumber<T>& A, const ComplexNumber<T>& B)
	{
		T denom = std::pow(B.real, 2) + std::pow(B.imag, 2);
		T real = (A.real * B.real + A.imag * B.imag) / denom;
		T imag = (A.imag * B.real - A.real * B.imag) / denom;

		return ComplexNumber<T>(real, imag);
	}

	// Overload of binary operator /
	template <arithmetic T>
	ComplexNumber<T> operator / (const ComplexNumber<T>& A, T B)
	{
		return ComplexNumber<T>(A.real / B, A.imag / B);
	}
}