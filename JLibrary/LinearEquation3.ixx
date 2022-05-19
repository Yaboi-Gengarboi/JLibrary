// JLibrary
// LinearEquation3.ixx
// Created on 2022-01-19 by Justyn Durnford
// Last modified on 2022-03-04 by Justyn Durnford
// Module file for the LinearEquation3 template class.

module;

#include "Arithmetic.hpp"

#include <array>
#include <cmath>
#include <initializer_list>
#include <ostream>
#include <string>

export module LinearEquation3;

import Equation;

export namespace jlib
{
	// 
	template <arithmetic T> class LinearEquation3 : public Equation<T>
	{
		public:

		std::array<T, 3> coefficients;
		std::array<T, 3> offsets;
		T w_offset;

		// 
		LinearEquation3()
		{
			coefficients[0] = static_cast<T>(0);
			coefficients[1] = static_cast<T>(0);
			coefficients[2] = static_cast<T>(0);
			offsets[0] = static_cast<T>(0);
			offsets[1] = static_cast<T>(0);
			offsets[2] = static_cast<T>(0);
			w_offset = static_cast<T>(0);
		}

		//
		LinearEquation3(T x_coeff, T y_coeff, T z_coeff, T x_off, T y_off, T z_off, T w_off)
		{
			coefficients[0] = x_coeff;
			coefficients[1] = y_coeff;
			coefficients[2] = z_coeff;
			offsets[0] = x_off;
			offsets[1] = y_off;
			offsets[2] = z_off;
			w_offset = w_off;
		}

		// 
		LinearEquation3(std::initializer_list<T> new_coefficients, std::initializer_list<T> new_offsets, T w_off)
		{
			for (int i = 0; i < 3; ++i)
			{
				coefficients[i] = *(new_coefficients.begin() + i);
				offsets[i] = *(new_offsets.begin() + i);
			}

			w_offset = w_off;
		}

		// 
		LinearEquation3(const std::array<T, 3>& new_coefficients, const std::array<T, 3>& new_offsets, T w_off)
		{
			for (int i = 0; i < 3; ++i)
			{
				coefficients[i] = new_coefficients[i];
				offsets[i] = new_offsets[i];
			}

			w_offset = w_off;
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
			std::string str("w = ");

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
				str += "+ " + std::to_string(std::abs(offsets[2])) + ") ";

			if (w_offset > 0)
				str += "+ " + std::to_string(w_offset);
			else
				str += "- " + std::to_string(std::abs(w_offset));

			return str;
		}

		// 
		std::wstring toWideString() const
		{
			std::wstring wstr(L"w = ");

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
				wstr += L"+ " + std::to_wstring(std::abs(offsets[2])) + L") ";

			if (w_offset > 0)
				wstr += L"+ " + std::to_wstring(w_offset);
			else
				wstr += L"- " + std::to_wstring(std::abs(w_offset));

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