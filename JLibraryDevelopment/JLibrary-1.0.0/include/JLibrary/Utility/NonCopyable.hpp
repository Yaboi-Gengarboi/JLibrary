// JLibraryDevelopment
// NonCopyable.hpp
// Created on 2021-06-20 by Justyn Durnford
// Last modified on 2021-06-20 by Justyn Durnford
// Header file for the abstract NonCopyable struct.

#pragma once

namespace jlib
{
	// Utility class that makes any 
	// derived struct or class non-copyable.
	struct NonCopyable
	{
		// Constructor.
		NonCopyable() = default;

		// Disabled copy constructor.
		NonCopyable(const NonCopyable& other) = delete;

		// Move constructor.
		NonCopyable(NonCopyable&& other) = default;

		// Disabled copy assignment operator.
		NonCopyable& operator = (const NonCopyable& other) = delete;

		// Move assignment operator.
		NonCopyable& operator = (NonCopyable&& other) = default;

		// Destructor.
		virtual ~NonCopyable() = default;
	};
}