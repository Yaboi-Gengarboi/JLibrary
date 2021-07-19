// JLibraryDevelopment
// MemoryInputStream.hpp
// Created on 2021-06-18 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the MemoryInputStream class.

#pragma once

#include <JLibrary/Utility/InputStream.hpp>
#include <cstddef>

namespace jlib
{
	class MemoryInputStream : public InputStream
	{
		const char* data_;
		i64 size_;
		i64 position_;

		public:

		// Default constructor.
		MemoryInputStream();

		// Opens the stream from the memory data.
		void open(const void* data, std::size_t byteCount);

		// Reads data from the stream.
		// Returns the number of bytes actually read, or -1 on error.
		virtual i64 read(void* data, i64 byteCount);

		// Changes the current reading position.
		// Returns the position actually sought to, or -1 on error.
		virtual i64 seek(i64 position);

		// Copy of member function seek().
		virtual i64 setReadPosition(i64 position);

		// Gets the current reading position in the stream/
		// Returns the current position, or -1 on error.
		virtual i64 tell();

		// Copy of member function tell().
		virtual i64 readPosition();

		// Returns the size of the stream.
		// Returns the total number of bytes available in the stream, or -1 on error.
		virtual i64 size();
	};
}