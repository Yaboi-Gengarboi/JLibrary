// JLibraryDevelopment
// ThreadLocal.hpp
// Created on 2021-07-04 by Justyn Durnford
// Last modified on 2021-07-11 by Justyn Durnford
// Header file for the ThreadLocal class.

#pragma once

#include <JLibrary/Utility/NonCopyable.hpp>
#include <windows.h>

namespace jlib
{
	// 
	class ThreadLocal : NonCopyable
	{
        DWORD index_;

		public:

        // Default constructor.
        ThreadLocal(void* value = nullptr);

        // Destructor.
        ~ThreadLocal();

        // Set the thread-specific value of the variable.
        void setValue(void* value);

        // Retrieve the thread-specific value of the variable.
        void* getValue() const;
	};
}