// JLibrary
// LinearEquation1.ixx
// Created on 2022-02-11 by Justyn Durnford
// Last modified on 2022-02-11 by Justyn Durnford
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
		T coefficient;
		T offset;

		public:

		// Default constructor.
		LinearEquation1()
		{
			coefficient = static_cast<T>(0);
			offset = static_cast<T>(0);
		}

		// 
		LinearEquation1(T new_coefficient, T new_offset)
		{
			coefficient = new_coefficient;
			offset = new_offset;
		}

		// Destructor.
		~LinearEquation1() = default;

		// 
		T function(T x) const
		{
			return coefficient * x - offset;
		}

		//
		T function(std::initializer_list<T> args) const
		{
			return coefficient * *(args.begin()) - offset;
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
			std::string str;

			str += std::to_string(coefficient) + "(x ";
			if (offset > 0)
				str += "- " + std::to_string(offset) + ") ";
			else
				str += "+ " + std::to_string(std::abs(offset)) + ") ";

			return str;
		}

		// 
		std::wstring toWideString() const
		{
			std::wstring wstr;

			wstr += std::to_wstring(coefficient) + L"(x ";
			if (offset > 0)
				wstr += L"- " + std::to_wstring(offset) + L") ";
			else
				wstr += L"+ " + std::to_wstring(std::abs(offset)) + L") ";

			return wstr;
		}
	};
}