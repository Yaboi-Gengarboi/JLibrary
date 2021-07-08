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
// MemoryInputStream.cpp
// Created on 2021-06-19 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Source file for the MemoryInputStream class.

#include <JLibrary/Utility/MemoryInputStream.hpp>
using namespace jlib;

#include <cstring>
using std::memcpy;

MemoryInputStream::MemoryInputStream()
{
	data_ = nullptr;
	size_ = 0;
	position_ = 0;
}

void MemoryInputStream::open(const void* data, size_t byteCount)
{
	data_ = static_cast<const char*>(data);
	size_ = byteCount;
	position_ = 0;
}

i64 MemoryInputStream::read(void* data, i64 byteCount)
{
    if (data_ == nullptr)
        return -1;

    i64 endPosition = position_ + byteCount;
    i64 count = 0;
    
    if (endPosition <= size_)
        count = size_;
    else
        count = size_ - position_;

    if (count > 0)
    {
        memcpy(data, data_ + position_, static_cast<size_t>(count));
        position_ += count;
    }

    return count;
}

i64 MemoryInputStream::seek(i64 position)
{
    if (data_ == nullptr)
        return -1;

    if (position < size_)
        position_ = position;
    else
        position_ = size_;

    return position_;
}

i64 MemoryInputStream::setReadPosition(i64 position)
{
    return seek(position);
}

i64 MemoryInputStream::tell()
{
    if (data_ == nullptr)
        return -1;
    return position_;
}

i64 MemoryInputStream::readPosition()
{
    return tell();
}

i64 MemoryInputStream::size()
{
    if (data_ == nullptr)
        return -1;

    return size_;
}