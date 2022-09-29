// JLibrary
// LinearEquation1.ixx
// Created on 2022-02-11 by Justyn Durnford
// Last modified on 2022-09-14 by Justyn Durnford
// Module file for the LinearEquation1 template class.

module;

#include "Arithmetic.hpp"
#include "String.hpp"

#include <cmath>

export module LinearEquation1;

import Equation;

export namespace jlib
{
	// 
	template <arithmetic T> class LinearEquation1 : public Equation<T>
	{
		public:

		T coefficient;
		T constant;

		// Default constructor.
		LinearEquation1()
		{
			coefficient = static_cast<T>(0);
			constant = static_cast<T>(0);
		}

		// 
		LinearEquation1(T new_coefficient, T new_constant)
		{
			coefficient = new_coefficient;
			constant = new_constant;
		}

		// 
		T function(T x) const
		{
			return coefficient * x + constant;
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
			std::string str("f(x) = ");
			
			if (coefficient == 1)
				str += "x";
			else if (coefficient != 0)
				str += std::to_string(coefficient) + "x";
			else
			{
				str += std::to_string(constant);
				return str;
			}

			if (constant < 0)
				str += " - " + std::to_string(std::abs(constant));
			else if (constant > 0)
				str += " + " + std::to_string(constant);

			return str;
		}

		// 
		std::wstring toWideString() const
		{
			return str_to_wstr(toString());
		}
	};
}