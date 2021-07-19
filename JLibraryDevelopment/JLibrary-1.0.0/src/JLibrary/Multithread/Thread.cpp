// JLibraryDevelopment
// Thread.cpp
// Created on 2021-07-04 by Justyn Durnford
// Last modified on 2021-07-04 by Justyn Durnford
// Source file for the Thread template class.

#include <JLibrary/Multithread/Thread.hpp>
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