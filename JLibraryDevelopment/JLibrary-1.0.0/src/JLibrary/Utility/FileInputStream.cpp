// JLibraryDevelopment
// FileInputStream.cpp
// Created on 2021-06-18 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Source file for the FileInputStream class.

#include <JLibrary/Utility/FileInputStream.hpp>
using namespace jlib;

// <cstdio>
using std::fclose;
using std::fopen;
using std::fread;
using std::fseek;
using std::ftell;

// <string>
using std::string;

FileInputStream::FileInputStream()
{
	file_ = nullptr;
}

FileInputStream::~FileInputStream()
{
	if (file_ != nullptr)
		fclose(file_);
}

bool FileInputStream::open(const string& filename)
{
	if (file_ != nullptr)
		fclose(file_);
	file_ = fopen(filename.c_str(), "rb");
	return file_ != nullptr;
}

i64 FileInputStream::read(void* data, i64 byteCount)
{
	if (file_ != nullptr)
		return fread(data, 1, static_cast<size_t>(byteCount), file_);
	return -1;
}

i64 FileInputStream::seek(i64 position)
{
	if (file_ != nullptr)
	{
		if (fseek(file_, static_cast<long>(position), SEEK_SET))
			return -1;
		return tell();
	}

	return -1;
}

i64 FileInputStream::setReadPosition(i64 position)
{
	return seek(position);
}

i64 FileInputStream::tell()
{
	if (file_ != nullptr)
		return ftell(file_);
	return -1;
}

i64 FileInputStream::readPosition()
{
	return tell();
}

i64 FileInputStream::size()
{
	if (file_ != nullptr)
	{
		i64 position = tell();
		fseek(file_, 0, SEEK_END);
		i64 size = tell();
		seek(position);
		return size;
	}

	return -1;
}