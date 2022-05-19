// JLibrary
// Literals.hpp
// Created on 2022-04-18 by Justyn Durnford
// Last modified on 2022-04-27 by Justyn Durnford
// Header file for the Literals namespace.

#pragma once

#include "IntegerTypedefs.hpp"

#include <cstddef>

namespace jlib
{
	namespace literals
	{
		constexpr u64 operator "" _KB(u64 x)
		{
			return 1024ULL * x;
		}

		constexpr u64 operator "" _MB(u64 x)
		{
			return 1048576ULL * x;
		}

		constexpr u64 operator "" _GB(u64 x)
		{
			return 1073741824ULL * x;
		}

		constexpr std::size_t operator "" _uz(u64 x)
		{
			return static_cast<std::size_t>(x);
		}
	}
}