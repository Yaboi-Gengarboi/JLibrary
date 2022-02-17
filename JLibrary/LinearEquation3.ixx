// JLibrary
// LinearEquation3.ixx
// Created on 2022-01-19 by Justyn Durnford
// Last modified on 2022-02-11 by Justyn Durnford
// Module file for the LinearEquation3 template class.

module;

#include "Arithmetic.hpp"

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <string>

export module LinearEquation3;

import FixedArray;

export namespace jlib
{
	// 
	template <arithmetic T> class LinearEquation3
	{
		public:

		FixedArray<T, 3> coefficients;
		FixedArray<T, 3> offsets;

		// 
		LinearEquation3()
		{
			coefficients = { static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
			offsets = { static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
		}

		//
		LinearEquation3(T x_coeff, T y_coeff, T z_coeff, T x_off, T y_off, T z_off)
		{
			coefficients = { x_coeff, y_coeff, z_coeff };
			offsets = { x_off, y_off, z_off };
		}

		// 
		LinearEquation3(std::initializer_list<T> new_coefficients, std::initializer_list<T> new_offsets)
		{
			for (int i = 0; i < 3; ++i)
			{
				coefficients[i] = *(new_coefficients.begin() + i);
				offsets[i] = *(new_offsets.begin() + i);
			}
		}

		// 
		LinearEquation3(const FixedArray<T, 3>& new_coefficients, const FixedArray<T, 3>& new_offsets)
		{
			for (int i = 0; i < 3; ++i)
			{
				coefficients[i] = new_coefficients[i];
				offsets[i] = new_offsets[i];
			}
		}

		// 
		LinearEquation3(const LinearEquation3& other) = default;

		// 
		LinearEquation3(LinearEquation3&& other) = default;

		// Constructs the LinearEquation from another type of LinearEquation.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit LinearEquation3(const LinearEquation3<U>& other)
		{
			for (int i = 0; i < 3; ++i)
			{
				coefficients[i] = static_cast<T>(other.coefficients[i]);
				offsets[i] = static_cast<T>(other.offsets[i]);
			}
		}

		// 
		LinearEquation3& operator = (const LinearEquation3& other) = default;

		// 
		LinearEquation3& operator = (LinearEquation3&& other) = default;

		// 
		~LinearEquation3() = default;

		// 
		void setCoefficients(T x_coeff, T y_coeff, T z_coeff)
		{
			coefficients = { x_coeff, y_coeff, z_coeff };
		}

		// 
		void setOffsets(T x_off, T y_off, T z_off)
		{
			offsets = { x_off, y_off, z_off };
		}

		// 
		void set(T x_coeff, T y_coeff, T z_coeff, T x_off, T y_off, T z_off)
		{
			coefficients = { x_coeff, y_coeff, z_coeff };
			offsets = { x_off, y_off, z_off };
		}

		// 
		void reset()
		{
			coefficients = { static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
			offsets = { static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
		}

		// 
		T function(T x, T y, T z) const
		{
			T result = static_cast<T>(0);

			result += (x - offsets[0]) * coefficients[0];
			result += (y - offsets[1]) * coefficients[1];
			result += (z - offsets[2]) * coefficients[2];

			return result;
		}

		//
		T operator () (T x, T y, T z) const
		{
			return function(x, y, z);
		}

		// 
		std::string toString() const
		{
			std::string str;

			str += std::to_string(coefficients[0]) + "(x ";
			if (offsets[0] > 0)
				str += "- " + std::to_string(offsets[0]) + ") ";
			else
				str += "+ " + std::to_string(std::abs(offsets[0])) + ") ";

			if (coefficients[1] > 0)
				str += "+ " + std::to_string(coefficients[1]) + "(y ";
			else
				str += "- " + std::to_string(std::abs(coefficients[1])) + "(y ";
			if (offsets[1] > 0)
				str += "- " + std::to_string(offsets[1]) + ") ";
			else
				str += "+ " + std::to_string(std::abs(offsets[1])) + ") ";

			if (coefficients[2] > 0)
				str += "+ " + std::to_string(coefficients[2]) + "(z ";
			else
				str += "- " + std::to_string(std::abs(coefficients[2])) + "(z ";
			if (offsets[2] > 0)
				str += "- " + std::to_string(offsets[2]) + ") = 0";
			else
				str += "+ " + std::to_string(std::abs(offsets[2])) + ") = 0";

			return str;
		}

		// 
		std::wstring toWideString() const
		{
			std::wstring wstr;

			wstr += std::to_wstring(coefficients[0]) + L"(x ";
			if (offsets[0] > 0)
				wstr += L"- " + std::to_wstring(offsets[0]) + L") ";
			else
				wstr += L"+ " + std::to_wstring(std::abs(offsets[0])) + L") ";

			if (coefficients[1] > 0)
				wstr += L"+ " + std::to_wstring(coefficients[1]) + L"(y ";
			else
				wstr += L"- " + std::to_wstring(std::abs(coefficients[1])) + L"(y ";
			if (offsets[1] > 0)
				wstr += L"- " + std::to_wstring(offsets[1]) + L") ";
			else
				wstr += L"+ " + std::to_wstring(std::abs(offsets[1])) + L") ";

			if (coefficients[2] > 0)
				wstr += L"+ " + std::to_wstring(coefficients[2]) + L"(z ";
			else
				wstr += L"- " + std::to_wstring(std::abs(coefficients[2])) + L"(z ";
			if (offsets[2] > 0)
				wstr += L"- " + std::to_wstring(offsets[2]) + L") = 0";
			else
				wstr += L"+ " + std::to_wstring(std::abs(offsets[2])) + L") = 0";

			return wstr;
		}
	};

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const LinearEquation3<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const LinearEquation3<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}