// JLibraryDevelopment
// Clock.cpp
// Created on 2021-05-24 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the Clock class.

#include <JLibrary/System/Clock.hpp>
using namespace jlib;

#include <chrono>
using std::chrono::duration;
using std::chrono::system_clock;
using std::chrono::time_point;

const Duration jlib::TimeZero = Duration(0.f);

Clock::Clock()
{
	start_ = now();
}

TimePoint Clock::startTime() const
{
	return start_;
}

TimePoint Clock::now() const
{
	return system_clock::now();
}

Duration Clock::restart()
{
	TimePoint time(now());
	Duration time_elapsed(time - start_);
	start_ = time;
	return time_elapsed;
}

Duration Clock::timeElapsed() const
{
	return now() - start_;
}