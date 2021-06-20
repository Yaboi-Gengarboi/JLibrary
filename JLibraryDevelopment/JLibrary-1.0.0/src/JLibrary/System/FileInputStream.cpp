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
// FileInputStream.cpp
// Created on 2021-06-18 by Justyn Durnford
// Last modified on 2021-06-19 by Justyn Durnford
// Source file for the FileInputStream class.

#include <JLibrary/System/FileInputStream.hpp>
#include <cstdio>
using namespace std;
using namespace jlib;

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