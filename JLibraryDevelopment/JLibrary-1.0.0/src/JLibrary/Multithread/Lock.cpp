// JLibraryDevelopment
// Lock.cpp
// Created on 2021-06-20 by Justyn Durnford
// Last modified on 2021-07-04 by Justyn Durnford
// Source file for the Lock class.

#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
using namespace jlib;

Lock::Lock(Mutex& mutex) : mutex_(mutex)
{
	mutex_.lock();
}

Lock::~Lock()
{
	mutex_.unlock();
}