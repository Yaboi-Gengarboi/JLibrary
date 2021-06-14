// JLibraryDevelopment
// Clock.cpp
// Created on 2021-05-24 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Source file for the Clock class.

#include <JLibrary/System/Clock.hpp>
using namespace std;
using namespace chrono;
using namespace jlib;

Clock::Clock()
{
	start_ = system_clock::now();
}

duration<double> Clock::timeElapsed() const
{
	return system_clock::now() - start_;
}

duration<double> Clock::restart()
{
	duration<double> time_elapsed(system_clock::now() - start_);
	start_ = system_clock::now();
	return time_elapsed;
}