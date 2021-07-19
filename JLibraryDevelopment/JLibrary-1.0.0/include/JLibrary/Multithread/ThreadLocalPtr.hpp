// JLibraryDevelopment
// ThreadLocalPtr.hpp
// Created on 2021-07-10 by Justyn Durnford
// Last modified on 2021-07-10 by Justyn Durnford
// Header file for the ThreadLocalPtr class.

#pragma once

#include <JLibrary/Multithread/ThreadLocal.hpp>

namespace jlib
{
	// Pointer to a thread-local variable.
	template <typename T>
	class ThreadLocalPtr : private ThreadLocal
	{
		public:

		// Default constructor.
		ThreadLocalPtr(T* value = nullptr) : ThreadLocal(value) {}

        // Raw pointer sssignment operator.
        ThreadLocalPtr<T>& operator = (T* value)
        {
            setValue(value);
            return *this;
        }

        // Copy assignment operator.
        ThreadLocalPtr<T>& operator = (const ThreadLocalPtr<T>& other)
        {
            setValue(other.getValue());
            return *this;
        }

        // Overload of unary dereference operator *
        // Like raw pointers, applying the * operator returns a
        // reference to the pointed-to object.
        T& operator * () const
        {
            return static_cast<T*>(getValue());
        }

        // Overload of operator ->
        // Similarly to raw pointers, applying the -> operator
        // returns the pointed-to object.
        T* operator -> () const
        {
            return static_cast<T*>(getValue());
        }

        // Conversion operator to implicitly convert the pointer to its raw pointer type (T*).
        operator T* () const
        {
            return static_cast<T*>(getValue());
        }
	};
}