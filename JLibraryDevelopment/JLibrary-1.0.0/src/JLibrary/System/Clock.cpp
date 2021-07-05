////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Clock.cpp
// Created on 2021-05-24 by Justyn Durnford
// Last modified on 2021-07-04 by Justyn Durnford
// Source file for the Clock class.

#include <JLibrary/System/Clock.hpp>
using namespace jlib;

// <chrono>
using std::chrono::duration;
using std::chrono::system_clock;
using std::chrono::time_point;

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