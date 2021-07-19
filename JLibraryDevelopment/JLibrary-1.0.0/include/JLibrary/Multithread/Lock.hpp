// JLibraryDevelopment
// Lock.hpp
// Created on 2021-06-20 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the Lock class.

#pragma once

#include <JLibrary/Utility/NonCopyable.hpp>

namespace jlib
{
	// 
	class Mutex;

	// Automatic wrapper class for locking and unlocking mutexes.
	class Lock : public NonCopyable
	{
		// Mutex to lock and unlock.
		Mutex& mutex_;

		public:

		// Disabled default constructor.
		Lock() = delete;

		// Constructs the lock with a target mutex,
		// automatically locking it.
		explicit Lock(Mutex& mutex);

		// Destructor.
		// Automatically unlocks the locked mutex.
		~Lock();
	};
}