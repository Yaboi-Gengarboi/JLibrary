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
// Thread.cpp
// Created on 2021-07-04 by Justyn Durnford
// Last modified on 2021-07-04 by Justyn Durnford
// Source file for the Thread template class.

#include <JLibrary/System/Thread.hpp>
using namespace jlib;

#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <process.h>

Thread::ThreadImpl::ThreadImpl(Thread* owner)
{
    thread_ = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, &ThreadImpl::entryPoint, owner, 0, &threadID_));

    if (thread_ == nullptr)
        cout << "Failed to create thread." << endl;
}

Thread::ThreadImpl::~ThreadImpl()
{
    if (thread_ != nullptr)
        CloseHandle(thread_);
}

void Thread::ThreadImpl::wait()
{
    if (thread_)
    {
        assert(threadID_ != GetCurrentThreadId()); // A thread cannot wait for itself!
        WaitForSingleObject(thread_, INFINITE);
    }
}

void Thread::ThreadImpl::terminate()
{
    if (thread_ != nullptr)
        TerminateThread(thread_, 0);
}

unsigned int __stdcall Thread::ThreadImpl::entryPoint(void* userData)
{
    // The Thread instance is stored in the user data.
    Thread* owner = static_cast<Thread*>(userData);

    // Forward to the owner.
    owner->run();

    // Optional, but it is cleaner.
    _endthreadex(0);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Thread::~Thread()
{
    wait();
    delete entryPoint_;
}

void Thread::launch()
{
    wait();
    impl_ = new ThreadImpl(this);
}

void Thread::wait()
{
    if (impl_ != nullptr)
    {
        impl_->wait();
        delete impl_;
        impl_ = nullptr;
    }
}

void Thread::terminate()
{
    if (impl_ != nullptr)
    {
        impl_->terminate();
        delete impl_;
        impl_ = nullptr;
    }
}

void Thread::run()
{
    entryPoint_->run();
}