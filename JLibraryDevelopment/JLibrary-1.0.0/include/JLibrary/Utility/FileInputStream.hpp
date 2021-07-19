// JLibraryDevelopment
// FileInputStream.hpp
// Created on 2021-06-18 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the FileInputStream class.

#pragma once

#include <JLibrary/Utility/InputStream.hpp>
#include <cstdio>
#include <string>

namespace jlib
{
	class FileInputStream : public InputStream
	{
		std::FILE* file_;

		public:

		// Default constructor.
		FileInputStream();

		// Disabled copy constructor.
		FileInputStream(const FileInputStream& other) = delete;

		// Disabled copy assignment operator.
		FileInputStream& operator = (const FileInputStream& other) = delete;

		// Destructor.
		virtual ~FileInputStream();

		// Opens the stream from a file path.
		// Returns true on success, false on error
		bool open(const std::string& filename);

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