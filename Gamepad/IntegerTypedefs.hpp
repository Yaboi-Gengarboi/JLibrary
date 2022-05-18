// JLibrary
// IntegerTypedefs.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-02-20 by Justyn Durnford
// Header file defining several integer typedefs.

#pragma once

namespace jlib
{
	// 8-bit signed integer.
	typedef signed char i8;
	// 8-bit unsigned integer.
	typedef unsigned char u8;

	// 16-bit signed integer.
	typedef signed short i16;
	// 16-bit unsigned integer.
	typedef unsigned short u16;

	// 32-bit signed integer.
	typedef signed int i32;
	// 32-bit unsigned integer.
	typedef unsigned int u32;

	#ifdef _WIN64

	// 64-bit signed integer.
	typedef signed long long i64;
	// 64-bit unsigned integer.
	typedef unsigned long long u64;

	#else

	// 64-bit signed integer.
	typedef signed __int64 i64;
	// 64-bit unsigned integer.
	typedef unsigned __int64 u64;

	#endif // #ifdef _WIN64

	// Minimum 8-bit signed integer value (-128).
	constexpr i8 I8_MIN = static_cast<i8>(-128);
	// Maximum 8-bit signed integer value (127).
	constexpr i8 I8_MAX = static_cast<i8>(127);

	// Minimun 8-bit unsigned integer value (0).
	constexpr u8 U8_MIN = static_cast<u8>(0);
	// Maximum 8-bit unsigned integer value (255).
	constexpr u8 U8_MAX = static_cast<u8>(255);

	// Minimum 16-bit signed integer value (-32768).
	constexpr i16 I16_MIN = static_cast<i16>(-32768);
	// Maximum 16-bit signed integer value (32767).
	constexpr i16 I16_MAX = static_cast<i16>(32767);

	// Minimun 16-bit unsigned integer value (0).
	constexpr u16 U16_MIN = static_cast<i16>(0);
	// Maximum 16-bit unsigned integer value (65535).
	constexpr u16 U16_MAX = static_cast<i16>(65535);

	// Minimum 32-bit signed integer value (-2147483648).
	constexpr i32 I32_MIN = -2147483648;
	// Maximum 32-bit signed integer value (2147483647).
	constexpr i32 I32_MAX = 2147483647;

	// Minimum 32-bit unsigned integer value (0).
	constexpr u32 U32_MIN = 0u;
	// Maximum 32-bit unsigned integer value (4294967295).
	constexpr u32 U32_MAX = 4294967295u;

	// Minimum 64-bit signed integer value (-9223372036854775808).
	constexpr i64 I64_MIN = -9223372036854775807ll - 1ll;
	// Maximum 64-bit signed integer value (9223372036854775807).
	constexpr i64 I64_MAX = 9223372036854775807ll;

	// Minimum 64-bit unsigned integer value (0).
	constexpr u64 U64_MIN = 0ull;
	// Maximum 64-bit unsigned integer value (18446744073709551615).
	constexpr u64 U64_MAX = 18446744073709551615ull;

	// Minimum 32-bit floating point value (1.175494351e-38f).
	constexpr float F32_MIN = 1.175494351e-38f;

	// Maximum 32-bit floating point value (3.402823466e+38f).
	constexpr float F32_MAX = 3.402823466e+38f;

	// Minimum 64-bit floating point value (2.2250738585072014e-308).
	constexpr double F64_MIN = 2.2250738585072014e-308;

	// Maximum 64-bit floating point value (1.7976931348623158e+308).
	constexpr double F64_MAX = 1.7976931348623158e+308;
}