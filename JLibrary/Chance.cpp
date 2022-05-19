// JLibrary
// Chance.cpp
// Created on 2022-02-18 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// HSource file that defines functions to generate random numbers.

#include "Chance.hpp"
#include "IntegerTypedefs.hpp"
using namespace jlib;

#include <random>
using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;

random_device                 rand_device;
default_random_engine         rand_engine(rand_device());
uniform_int_distribution<i16> rand_dist_i16(I16_MIN, I16_MAX);
uniform_int_distribution<u16> rand_dist_u16(U16_MIN, U16_MAX);
uniform_int_distribution<i32> rand_dist_i32(I32_MIN, I32_MAX);
uniform_int_distribution<u32> rand_dist_u32(U32_MIN, U32_MAX);
uniform_int_distribution<i64> rand_dist_i64(I64_MIN, I64_MAX);
uniform_int_distribution<u64> rand_dist_u64(U64_MIN, U64_MAX);

namespace jlib
{
	i16 rand_i16()
	{
		return rand_dist_i16(rand_engine);
	}

	u16 rand_u16()
	{
		return rand_dist_u16(rand_engine);
	}

	i32 rand_i32()
	{
		return rand_dist_i32(rand_engine);
	}

	u32 rand_u32()
	{
		return rand_dist_u32(rand_engine);
	}

	i64 rand_i64()
	{
		return rand_dist_i64(rand_engine);
	}

	u64 rand_u64()
	{
		return rand_dist_u64(rand_engine);
	}
}