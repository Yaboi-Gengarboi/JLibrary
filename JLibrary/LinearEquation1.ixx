// JLibrary
// LinearEquation1.ixx
// Created on 2022-02-11 by Justyn Durnford
// Last modified on 2022-03-04 by Justyn Durnford
// Module file for the LinearEquation1 template class.

module;

#include "Arithmetic.hpp"

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <string>

export module LinearEquation1;

import Equation;

export namespace jlib
{
	// 
	template <arithmetic T> class LinearEquation1 : public Equation<T>
	{
		public:

		T coefficient;
		T offset;
		T y_offset;

		// Default constructor.
		LinearEquation1()
		{
			coefficient = static_cast<T>(0);
			offset = static_cast<T>(0);
			y_offset = static_cast<T>(0);
		}

		// 
		LinearEquation1(T new_coefficient, T new_offset, T new_y_offset)
		{
			coefficient = new_coefficient;
			offset = new_offset;
			y_offset = new_y_offset;
		}

		// Destructor.
		~LinearEquation1() = default;

		// 
		T function(T x) const
		{
			return coefficient * (x - offset) + y_offset;
		}

		//
		T function(std::initializer_list<T> args) const
		{
			return function(*args.begin());
		}

		//
		T operator () (T x) const
		{
			return function(x);
		}

		//
		T operator () (std::initializer_list<T> args) const
		{
			return function(args);
		}

		// 
		std::string toString() const
		{
			std::string str("y = ");

			if (coefficient == 0)
			{
				if (y_offset == 0)
					str += "0";
				else 
					str += std::to_string(y_offset);

				return str;
			}

			if (offset == 0)
				str += std::to_string(coefficient) + "x";
			else
			{
				str += std::to_string(coefficient) + "(x ";

				if (offset > 0)
					str += "- " + std::to_string(offset) + ")";
				else
					str += "+ " + std::to_string(std::abs(offset)) + ")";
			}

			if (y_offset == 0)
				return str;
			
			if (y_offset > 0)
				str += " + " + std::to_string(y_offset);
			else
				str += " - " + std::to_string(std::abs(y_offset));

			return str;
		}

		// 
		std::wstring toWideString() const
		{
			std::wstring wstr(L"y = ");

			if (coefficient == 0)
			{
				if (y_offset == 0)
					wstr += L"0";
				else
					wstr += std::to_wstring(y_offset);

				return wstr;
			}

			if (offset == 0)
				wstr += std::to_wstring(coefficient) + L"x";
			else
			{
				wstr += std::to_wstring(coefficient) + L"(x ";

				if (offset > 0)
					wstr += L"- " + std::to_wstring(offset) + L")";
				else
					wstr += L"+ " + std::to_wstring(std::abs(offset)) + L")";
			}

			if (y_offset == 0)
				return wstr;
			else
			{
				if (y_offset > 0)
					wstr += L" + " + std::to_wstring(y_offset);
				else
					wstr += L" - " + std::to_wstring(std::abs(y_offset));
			}

			return wstr;
		}
	};
}