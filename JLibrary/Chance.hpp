// JLibrary
// Chance.hpp
// Created on 2022-02-18 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Header file that declares functions to generate random numbers.

#pragma once

#include "IntegerTypedefs.hpp"

namespace jlib
{
	// Returns a random i16.
	i16 rand_i16();

	// Returns a random u16.
	u16 rand_u16();

	// Returns a random i32.
	i32 rand_i32();

	// Returns a random u32.
	u32 rand_u32();

	// Returns a random i64.
	i64 rand_i64();

	// Returns a random u64.
	u64 rand_u64();
}