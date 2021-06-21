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
// InputStream.hpp
// Created on 2021-06-18 by Justyn Durnford
// Last modified on 2021-06-19 by Justyn Durnford
// Header file for the abstract InputStream class.

#pragma once

#include <JLibrary/System/Integer.hpp>

namespace jlib
{
    class InputStream
    {
        public:

        // Virtual destructor.
        virtual ~InputStream() {}

        // Reads data from the stream.
        // Returns the number of bytes actually read, or -1 on error.
        virtual i64 read(void* data, i64 byteCount) = 0;

        // Changes the current reading position.
        // Returns the position actually sought to, or -1 on error.
        virtual i64 seek(i64 position) = 0;

        // Copy of member function seek().
        virtual i64 setReadPosition(i64 position) = 0;

        // Gets the current reading position in the stream/
        // Returns the current position, or -1 on error.
        virtual i64 tell() = 0;

        // Copy of member function tell().
        virtual i64 readPosition() = 0;

        // Returns the size of the stream.
        // Returns the total number of bytes available in the stream, or -1 on error.
        virtual i64 size() = 0;
    };

}