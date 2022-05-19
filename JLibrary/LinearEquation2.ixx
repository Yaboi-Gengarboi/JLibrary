// JLibrary
// LinearEquation2.ixx
// Created on 2022-03-02 by Justyn Durnford
// Last modified on 2022-03-04 by Justyn Durnford
// Module file for the LinearEquation2 template class.

module;

#include "Arithmetic.hpp"

#include <array>
#include <cmath>
#include <initializer_list>
#include <ostream>
#include <string>

export module LinearEquation2;

import Equation;

export namespace jlib
{
	// 
	template <arithmetic T> class LinearEquation2 : public Equation<T>
	{
		public:

		std::array<T, 2> coefficients;
		std::array<T, 2> offsets;
		T z_offset;

		// Default constructor.
		LinearEquation2()
		{
			coefficients[0] = static_cast<T>(0);
			coefficients[1] = static_cast<T>(0);
			offsets[0] = static_cast<T>(0);
			offsets[1] = static_cast<T>(0);
			z_offset = static_cast<T>(0);
		}

		// 
		LinearEquation2(T x_coeff, T y_coeff, T x_off, T y_off, T z_off)
		{
			coefficients[0] = x_coeff;
			coefficients[1] = y_coeff;
			offsets[0] = x_off;
			offsets[1] = y_off;
			z_offset = z_off;
		}

		// Destructor.
		~LinearEquation2() = default;

		// 
		void setCoefficients(T x_coeff, T y_coeff)
		{
			coefficients[0] = x_coeff;
			coefficients[1] = y_coeff;
		}

		// 
		void setOffsets(T x_off, T y_off)
		{
			offsets[0] = x_off;
			offsets[1] = y_off;
		}

		// 
		void set(T x_coeff, T y_coeff, T x_off, T y_off)
		{
			coefficients[0] = x_coeff;
			coefficients[1] = y_coeff;
			offsets[0] = x_off;
			offsets[1] = y_off;
		}

		// 
		void reset()
		{
			coefficients[0] = static_cast<T>(0);
			coefficients[1] = static_cast<T>(0);
			offsets[0] = static_cast<T>(0);
			offsets[1] = static_cast<T>(0);
		}

		// 
		T function(T x, T y) const
		{
			return coefficients[0] * (x - offsets[0]) + coefficients[1] * (y - offsets[1]) + z_offset;
		}

		//
		T function(std::initializer_list<T> args) const
		{
			return function(*(args.begin() + 0), *(args.begin() + 1));
		}

		//
		T operator () (T x, T y) const
		{
			return function(x, y);
		}

		//
		T operator () (std::initializer_list<T> args) const
		{
			return function(args);
		}

		// 
		std::string toString() const
		{
			std::string str("z = ");

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

			if (z_offset > 0)
				str += "+ " + std::to_string(z_offset);
			else
				str += "- " + std::to_string(std::abs(z_offset));

			return str;
		}

		// 
		std::wstring toWideString() const
		{
			std::wstring wstr(L"z = ");

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

			if (z_offset > 0)
				wstr += L"+ " + std::to_wstring(z_offset);
			else
				wstr += L"- " + std::to_wstring(std::abs(z_offset));

			return wstr;
		}
	};
}