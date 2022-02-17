// JLibrary
// ArithmeticType.hpp
// Created on 2022-01-28 by Justyn Durnford
// Last modified on 2022-01-28 by Justyn Durnford
// Header file for the abstract ArithmeticType class.

#pragma once

#include <concepts>

namespace jlib
{
	template <typename T> concept arithmetic = std::is_arithmetic_v<T>;
}