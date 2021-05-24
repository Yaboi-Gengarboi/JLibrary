// JLibraryDevelopment
// Arithmetic.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last updated on 2021-05-23 by Justyn Durnford
// Header file defining the std_arithmetic and jl_arithmetic concepts.

#pragma once

#include <concepts>

namespace jl
{
	#ifndef JLIBRARY_STD_ARITHMETIC
	#define JLIBRARY_STD_ARITHMETIC

	template <typename T> concept std_arithmetic = std::is_arithmetic_v<T>;

	#endif // JLIBRARY_STD_ARITHMETIC


}