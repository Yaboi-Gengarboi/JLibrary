// JLibrary
// Conversions.hpp
// Created on 2022-02-20 by Justyn Durnford
// Last modified on 2022-02-20 by Justyn Durnford
// Header file declaring several conversion functions.

#pragma once

namespace jlib
{
	// Converts from celcius to fahrenheit.
	constexpr float to_fahrenheit(float celcius);

	// Converts from fahrenheit to celcius.
	constexpr float to_celcius(float fahrenheit);

	// Converts from inches to centimeters.
	constexpr float to_centimeters(float inches);

	// Converts from centimeters to inches.
	constexpr float to_inches(float centimeters);

	// Converts from meters to feet.
	constexpr float to_feet(float meters);

	// Converts from feet to meters.
	constexpr float to_meters(float feet);
}