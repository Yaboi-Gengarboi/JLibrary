// JLibrary
// Arithmetic.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the arithmetic concept.

module;

#include <concepts>

export module Arithmetic;

export namespace jlib
{
	template <typename T> concept arithmetic = std::is_arithmetic_v<T>;
}