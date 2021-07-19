// JLibraryDevelopment
// ThreadLocal.cpp
// Created on 2021-07-04 by Justyn Durnford
// Last modified on 2021-07-11 by Justyn Durnford
// Source file for the ThreadLocal class.

#include <JLibrary/Multithread/ThreadLocal.hpp>
using namespace jlib;

ThreadLocal::ThreadLocal(void* value)
{
    index_ = TlsAlloc();
    setValue(value);
}

ThreadLocal::~ThreadLocal()
{
    TlsFree(index_);
}

void ThreadLocal::setValue(void* value)
{
    TlsSetValue(index_, value);
}

void* ThreadLocal::getValue() const
{
    return TlsGetValue(index_);
}