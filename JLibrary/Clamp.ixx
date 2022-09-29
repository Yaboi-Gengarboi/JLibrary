// JLibrary
// Clamp.ixx
// Created on 2022-09-28 by Justyn Durnford
// Last modified on 2022-09-28 by Justyn Durnford
// Module file defining several clamp template functions.

module;

#include "Arithmetic.hpp"

export module Clamp;

export namespace jlib
{
	// Sets the given value to lower if value < lower.
	template <arithmetic T>
	void clamp_min(T& value, T lower)
	{
		if (value < lower)
			value = lower;
	}

	// Sets the given value to upper if value > upper.
	template <arithmetic T>
	void clamp_max(T& value, T upper)
	{
		if (value > upper)
			value = upper;
	}

	// Sets the given value to lower if value < lower.
	// Sets the given value to upper if value > upper.
	template <arithmetic T>
	void clamp(T& value, T lower, T upper)
	{
		if (value < lower)
			value = lower;
		else if (value > upper)
			value = upper;
	}

	// Returns lower if the given value < lower.
	// Returns upper if the given value > upper.
	// Returns the given value if neither of the
	// above conditions are met.
	template <arithmetic T>
	T clamp_of(T value, T lower, T upper)
	{
		if (value < lower)
			return lower;
		if (value > upper)
			return upper;
		return value;
	}

	// Returns true if the given value is within, but not on, the given bounds.
	template <arithmetic T>
	bool is_within_exclusive(T value, T lower, T upper)
	{
		return (value > lower) && (value < upper);
	}

	// Returns true if the given value is within or on the given bounds.
	template <arithmetic T>
	bool is_within_inclusive(T value, T lower, T upper)
	{
		return (value >= lower) && (value <= upper);
	}
}