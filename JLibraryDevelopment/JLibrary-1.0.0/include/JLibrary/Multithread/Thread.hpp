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
// Thread.hpp
// Created on 2021-07-02 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the Thread template class.

#pragma once

#include <JLibrary/Utility/NonCopyable.hpp>
#include <windows.h>

namespace jlib
{
	// 
	class Thread : NonCopyable
	{
		class ThreadImpl : NonCopyable
		{
			HANDLE thread_;
			unsigned int threadID_; 

			// Global entry point for all threads.
			// Returns an OS specific error code.
			static unsigned int __stdcall entryPoint(void* userData);

			public:

			// Default constructor. 
			// Launches the thread.
			ThreadImpl(Thread* owner);

			// Destructor.
			~ThreadImpl();

			// Waits until the thread finishes.
			void wait();

			// Terminates the thread.
			void terminate();
		};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		// Base class for abstract thread functions.
		struct ThreadFunc
		{
			virtual ~ThreadFunc() {}
			virtual void run() = 0;
		};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		// Specialization using a functor (including free functions) with no argument.
		template <typename T>
		struct ThreadFunctor : ThreadFunc
		{
			T functor_;

			ThreadFunctor(T functor)
			{
				functor_(functor);
			}

			virtual void run() 
			{ 
				functor_(); 
			}
		};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		// Specialization using a functor (including free functions) with one argument.
		template <typename Func, typename Arg>
		struct ThreadFunctorWithArg : ThreadFunc
		{
			Func function_;
			Arg arg_;

			ThreadFunctorWithArg(Func func, Arg arg)
			{
				function_(func);
				arg_(arg);
			}

			virtual void run() 
			{ 
				function_(arg_); 
			}
		};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		// Specialization using a member function.
		template <typename Cl>
		struct ThreadMemberFunc : ThreadFunc
		{
			Cl* object_;
			void(Cl::* function_)();

			ThreadMemberFunc(void(Cl::* function)(), Cl* object)
			{
				function_(function);
				object_(object);
			}
			
			virtual void run() 
			{ 
				(object_->*function_)(); 
			}
		};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		ThreadImpl* impl_;
		ThreadFunc* entryPoint_;

		// Internal entry point of the thread.
		void run();

		public:

		// Construct the thread from a functor with no arguments.
		// This does *not* run the thread, use launch().
		template <typename Func>
		Thread(Func func)
			: impl_(nullptr), entryPoint_(new ThreadFunc<Func>(func)) {}

		// Construct the thread from a functor with an argument.
		// This does *not* run the thread, use launch().
		template <typename Func, typename Arg>
		Thread(Func func, Arg arg)
			: impl_(nullptr), entryPoint_(new ThreadFunctorWithArg<Func, Arg>(func, arg)) {}

		// Construct the thread from a member function and an object.
		// This does *not* run the thread, use launch().
		template <typename Cl>
		Thread(void(Cl::* function)(), Cl* object)
			: impl_(nullptr), entryPoint_(new ThreadMemberFunc<Cl>(function, object)) {}

		// Destructor.
		// This destructor calls wait(), so that the internal thread
		// cannot survive after its sf::Thread instance is destroyed.
		~Thread();

		// This function starts the entry point passed to the
		// thread's constructor, and returns immediately.
		// After this function returns, the thread's function is
		// running in parallel to the calling code.
		void launch();

		// Wait until the thread finishes.
		void wait();

		// Terminate.
		void terminate();
	};
}