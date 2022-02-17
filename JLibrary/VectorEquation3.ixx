// JLibrary
// VectorEquation3.ixx
// Created on 2022-02-11 by Justyn Durnford
// Last modified on 2022-02-11 by Justyn Durnford
// Module file for the VectorEquation3 template class.

module;

#include "Arithmetic.hpp"

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <string>

export module VectorEquation3;

import Equation;
import Vector3;

export namespace jlib
{
	// 
	template <arithmetic T> class VectorEquation3
	{
		public:

		Equation<T> x_equation;
		Equation<T> y_equation;
		Equation<T> z_equation;

		// Default constructor.
		VectorEquation3() = default;

		// 
		VectorEquation3(const Equation<T>& new_x_equation, const Equation<T>& new_y_equation, const Equation<T>& new_z_equation)
		{
			x_equation = new_x_equation;
			y_equation = new_y_equation;
			z_equation = new_z_equation;
		}

		// 
		Vector3<T> function(T t)
		{
			return Vector3<T>(x_equation(t), y_equation(t), z_equation(t));
		}

		// 
		Vector3<T> operator () (T t)
		{
			return function(T);
		}
	};
}