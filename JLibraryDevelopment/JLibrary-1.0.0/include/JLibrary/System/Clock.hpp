// JLibraryDevelopment
// Clock.hpp
// Created on 2021-05-24 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Header file for the Clock class.

#pragma once

#include <chrono>

namespace jlib
{
	// 
	class Clock
	{
		std::chrono::time_point<std::chrono::system_clock> start_;

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
		std::chrono::duration<double> timeElapsed() const;

		// 
		std::chrono::duration<double> restart();
	};
}