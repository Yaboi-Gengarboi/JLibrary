// JLibrary
// Equation.ixx
// Created on 2022-02-11 by Justyn Durnford
// Last modified on 2022-02-11 by Justyn Durnford
// Module file for the abstract Equation template class.

module;

#include "Arithmetic.hpp"

#include <initializer_list>

export module Equation;

export namespace jlib
{
	// 
	template <arithmetic T> class Equation
	{
		public:

		// Default constructor.
		Equation() = default;

		// Virtual destructor.
		virtual ~Equation() = default;

		// 
		virtual T function(std::initializer_list<T> args) const = 0;

		// 
		virtual T operator () (std::initializer_list<T> args) const = 0;
	};
}