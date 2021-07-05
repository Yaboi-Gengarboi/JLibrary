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
// ThreadLocal.cpp
// Created on 2021-07-04 by Justyn Durnford
// Last modified on 2021-07-04 by Justyn Durnford
// Source file for the ThreadLocal class.

#include <JLibrary/Multithread/ThreadLocal.hpp>
using namespace jlib;

ThreadLocal::ThreadLocalImpl::ThreadLocalImpl()
{
    index_ = TlsAlloc();
}

ThreadLocal::ThreadLocalImpl::~ThreadLocalImpl()
{
    TlsFree(index_);
}

void ThreadLocal::ThreadLocalImpl::setValue(void* value)
{
    TlsSetValue(index_, value);
}

void* ThreadLocal::ThreadLocalImpl::getValue() const
{
    return TlsGetValue(index_);
}

ThreadLocal::ThreadLocal(void* value)
{
    impl_ = new ThreadLocalImpl;
    setValue(value);
}

ThreadLocal::~ThreadLocal()
{
    delete impl_;
}

void ThreadLocal::setValue(void* value)
{
    impl_->setValue(value);
}

void* ThreadLocal::getValue() const
{
    return impl_->getValue();
}