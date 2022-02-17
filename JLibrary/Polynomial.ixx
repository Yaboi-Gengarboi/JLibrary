// JLibrary
// Polynomial.ixx
// Created on 2022-01-25 by Justyn Durnford
// Last modified on 2022-01-28 by Justyn Durnford
// Module file for the Polynomial template class.

module;

#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <ostream>
#include <string>
#include <vector>

export module Polynomial;

import Array;
import MiscTemplateFunctions;

export namespace jlib
{
	// 
	template <arithmetic T> struct PolynomialNode
	{
		u32 power;
		T coefficient;
	};

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const PolynomialNode<T>& A, const PolynomialNode<T>& B)
	{
		return A.power == B.power;
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const PolynomialNode<T>& A, const PolynomialNode<T>& B)
	{
		return A.power != B.power;
	}

	// Overload of binary operator <
	template <arithmetic T>
	bool operator < (const PolynomialNode<T>& A, const PolynomialNode<T>& B)
	{
		return A.power < B.power;
	}

	// Overload of binary operator <=
	template <arithmetic T>
	bool operator <= (const PolynomialNode<T>& A, const PolynomialNode<T>& B)
	{
		return A.power <= B.power;
	}

	// Overload of binary operator >
	template <arithmetic T>
	bool operator > (const PolynomialNode<T>& A, const PolynomialNode<T>& B)
	{
		return A.power > B.power;
	}

	// Overload of binary operator >=
	template <arithmetic T>
	bool operator >= (const PolynomialNode<T>& A, const PolynomialNode<T>& B)
	{
		return A.power >= B.power;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	template <arithmetic T> class Polynomial
	{
		public:

		std::vector<PolynomialNode<T>> _data;

		public:

		// 
		Polynomial() = default;

		// 
		Polynomial(u32 power)
		{
			_data.resize(power + 1);
			
			for (u32 i = 0; i < _data.size(); ++i)
			{
				_data[i].power = i;
				_data[i].coefficient = static_cast<T>(0);
			}
		}

		// 
		Polynomial(u32 power, T coefficient)
		{
			_data.resize(power + 1);

			for (u32 i = 0; i < _data.size(); ++i)
			{
				_data[i].power = i;
				_data[i].coefficient = coefficient;
			}
		}

		// 
		Polynomial(const Polynomial& other) = default;

		// 
		Polynomial(Polynomial&& other) = default;

		// Constructs the Polynomial from another type of Polynomial.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Polynomial(const Polynomial<U>& other)
		{
			_data.resize(other._data.size());

			for (u32 i = 0; i < _data.size(); ++i)
			{
				_data[i].power = other._data[i].power;
				_data[i].coefficient = other._data[i].coefficient;
			}
		}

		// 
		Polynomial& operator = (const Polynomial& other) = default;

		// 
		Polynomial& operator = (Polynomial&& other) = default;

		// 
		~Polynomial() = default;

		//
		void addNode(T power, T coefficient)
		{
			PolynomialNode<T> node(power, coefficient);
			auto iter = std::find(_data.begin(), _data.end(), node);

			if (iter == _data.end())
			{
				_data.push_back(node);
				std::sort(_data.begin(), _data.end());
			}
			else
				iter->coefficient = node.coefficient;
		}

		// 
		T function(T x) const
		{
			T result = static_cast<T>(0);

			for (u32 i = 0; i < _data.size(); ++i)
				result += _data[i].coefficient * std::pow(x, _data[i].power);

			return result;
		}

		//
		T operator () (T x) const
		{
			return function(x);
		}
	};
}