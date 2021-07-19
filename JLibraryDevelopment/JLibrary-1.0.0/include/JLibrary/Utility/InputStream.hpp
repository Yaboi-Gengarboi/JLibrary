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