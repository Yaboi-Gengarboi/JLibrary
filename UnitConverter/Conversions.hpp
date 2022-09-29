// UnitConverter
// Conversions.hpp
// Created on 2022-02-20 by Justyn Durnford
// Last modified on 2022-09-09 by Justyn Durnford
// Header file declaring several conversion functions.

#pragma once

namespace jlib
{
	// Converts from celcius to fahrenheit.
	constexpr float to_fahrenheit(float celcius)
	{
		return celcius * 1.8f + 32.0f;
	}

	// Converts from fahrenheit to celcius.
	constexpr float to_celcius(float fahrenheit)
	{
		return (fahrenheit - 32.0f) * 0.55555556f;
	}

	// Converts from inches to centimeters.
	constexpr float to_centimeters(float inches)
	{
		return inches * 2.54f;
	}

	// Converts from centimeters to inches.
	constexpr float to_inches(float centimeters)
	{
		return centimeters * 0.393701f;
	}

	// Converts from meters to feet.
	constexpr float to_feet(float meters)
	{
		return meters * 3.280839895f;
	}

	// Converts from feet to meters.
	constexpr float to_meters(float feet)
	{
		return feet * 0.3048f;
	}

	// Converts from kilometers to miles.
	constexpr float to_miles(float kilometers)
	{
		return kilometers * 0.621371f;
	}

	// Converts from miles to kilometers.
	constexpr float to_kilometers(float miles)
	{
		return miles * 1.60934f;
	}

	// Converts from kmph to miph.
	constexpr float to_miph(float kmph)
	{
		return kmph * 0.621371f;
	}

	// Converts from miph to kmph.
	constexpr float to_kmph(float miph)
	{
		return miph * 1.60934f;
	}
}