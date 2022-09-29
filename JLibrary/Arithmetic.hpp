// JLibrary
// ArithmeticType.hpp
// Created on 2022-01-28 by Justyn Durnford
// Last modified on 2022-09-18 by Justyn Durnford
// Header file for the abstract ArithmeticType class.

#pragma once

#include <concepts>

namespace jlib
{
	// This concept encompasses all integral or floating-point types
	// that satisfy the std::is_arithmetic boolean function.
	template <typename T> concept arithmetic = std::is_arithmetic_v<T>;
}