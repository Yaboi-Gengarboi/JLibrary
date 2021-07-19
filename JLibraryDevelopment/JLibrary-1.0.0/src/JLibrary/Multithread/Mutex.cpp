// JLibraryDevelopment
// Mutex.cpp
// Created on 2021-06-20 by Justyn Durnford
// Last modified on 2021-07-04 by Justyn Durnford
// Source file for the Mutex class.

#include <JLibrary/Multithread/Mutex.hpp>
using namespace jlib;

Mutex::Mutex()
{
	InitializeCriticalSection(&mutex_);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&mutex_);
}

void Mutex::lock()
{
	EnterCriticalSection(&mutex_);
}

void Mutex::unlock()
{
	LeaveCriticalSection(&mutex_);
}