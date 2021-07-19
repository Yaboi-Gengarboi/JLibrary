// JLibraryDevelopment
// Sleep.cpp
// Created on 2021-07-15 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Source file for the Sleep function.

#include <JLibrary/Multithread/Sleep.hpp>
using namespace jlib;

#ifndef NOMINMAX
	#define NOMINMAX
#endif // NOMINMAX

#pragma comment (lib, "winmm")

#include <windows.h>

void jlib::sleep(Duration millisec)
{
	float ticks = millisec.count();

	if (ticks >= 0.f)
	{
		// Get the supported timer resolutions on this system.
		TIMECAPS tc;
		timeGetDevCaps(&tc, sizeof(TIMECAPS));

		// Set the timer resolution to the minimum for the Sleep call.
		timeBeginPeriod(tc.wPeriodMin);

		// Wait...
		::Sleep(ticks);

		// Reset the timer resolution back to the system default.
		timeEndPeriod(tc.wPeriodMin);
	}
}