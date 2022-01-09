// JLibrary
// Clock.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file for the Clock class.

#pragma once

#include <chrono>

namespace jlib
{
	// Shorthand for std::chrono::time_point<std::chrono::system_clock>.
	typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
	// Shorthand for std::chrono::duration<float>.
	typedef std::chrono::duration<float> Duration;

	extern const Duration TimeZero;

	// 
	class Clock
	{
		TimePoint _start;

		public:

		// Default constructor.
		//
		Clock();

		// Copy constructor.
		Clock(const Clock& other) = delete;

		// Move constructor.
		Clock(Clock&& other) = delete;

		// Copy assignment operator.
		Clock& operator = (const Clock& other) = delete;

		// Move assignment operator.
		Clock& operator = (Clock&& other) = delete;

		// Destructor.
		~Clock() = default;

		// 
		TimePoint startTime() const;

		// 
		TimePoint now() const;

		// 
		Duration restart();

		// 
		Duration timeElapsed() const;
	};
}