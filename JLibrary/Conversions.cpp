// JLibrary
// Conversions.cpp
// Created on 2022-02-20 by Justyn Durnford
// Last modified on 2022-02-20 by Justyn Durnford
// Source file defining several conversion functions.

#include "Conversions.hpp"

namespace jlib
{
	constexpr float to_fahrenheit(float celcius)
	{
		return celcius * (9.0f / 5.0f) + 32.0f;
	}

	constexpr float to_celcius(float fahrenheit)
	{
		return (fahrenheit - 32.0f) * (5.0f / 9.0f);
	}

	constexpr float to_centimeters(float inches)
	{
		return inches * 2.54f;
	}

	constexpr float to_inches(float centimeters)
	{
		return centimeters / 2.54f;
	}

	constexpr float to_feet(float meters)
	{
		return meters * 3.280839895f;
	}

	constexpr float to_meters(float feet)
	{
		return feet / 3.280839895f;
	}
}