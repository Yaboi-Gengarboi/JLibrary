// JLibrary
// Clock.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Source file for the Clock class.

#include "Clock.hpp"

#include <chrono>
using std::chrono::duration;
using std::chrono::system_clock;
using std::chrono::time_point;

namespace jlib
{
	const Duration jlib::TimeZero = Duration(0.0f);

	Clock::Clock()
	{
		_start = now();
	}

	TimePoint Clock::startTime() const
	{
		return _start;
	}

	TimePoint Clock::now() const
	{
		return system_clock::now();
	}

	Duration Clock::restart()
	{
		TimePoint time(now());
		Duration time_elapsed(time - _start);
		_start = time;
		return time_elapsed;
	}

	Duration Clock::timeElapsed() const
	{
		return now() - _start;
	}
}