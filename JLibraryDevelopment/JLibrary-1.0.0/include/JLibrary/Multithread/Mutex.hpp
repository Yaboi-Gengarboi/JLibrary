// JLibraryDevelopment
// Mutex.hpp
// Created on 2021-06-20 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the Mutex class.

#pragma once

#include <JLibrary/Utility/NonCopyable.hpp>
#include <windows.h>

namespace jlib
{
	// 
	class Mutex : NonCopyable
	{
		CRITICAL_SECTION mutex_;

		public:

		// Default constructor.
		Mutex();

		// Destructor.
		~Mutex();

		// Locks the mutex.
		void lock();

		// Unlocks the mutex.
		void unlock();
	};
}