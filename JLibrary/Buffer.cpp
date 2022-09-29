// JLibrary
// Buffer.cpp
// Created on 2022-04-11 by Justyn Durnford
// Last modified on 2022-07-02 by Justyn Durnford
// Source file for the Buffer class.

#include "Buffer.hpp"
#include "Hexadecimal.hpp"
#include "String.hpp"

#include <cstddef>
using std::byte;
using std::size_t;

#include <cstring>
using std::memcpy;
using std::memset;

#include <iostream>
using std::cout;
using std::ostream;

#include <stdexcept>
using std::out_of_range;

#include <string>
using std::string;

namespace jlib
{
	constexpr size_t Buffer::_minCount(size_t byte_count) const noexcept
	{
		return byte_count > _size ? _size : byte_count;
	}

	void Buffer::_allocate(size_t size)
	{
		_data = new byte[size];
		_size = size;
	}

	Buffer::Buffer()
	{
		_data = nullptr;
		_size = 0;
	}

	Buffer::Buffer(size_t size)
	{
		_allocate(size);
	}

	Buffer::Buffer(size_t size, unsigned char value)
	{
		_allocate(size);
		memset(_data, value, _size);
	}

	Buffer::Buffer(const string& str)
	{
		_allocate(str.size());
		memcpy(_data, str.c_str(), _size);
	}

	Buffer::Buffer(const void* src, size_t size)
	{
		_allocate(size);
		memcpy(_data, src, _size);
	}

	Buffer::Buffer(const Buffer& other)
	{
		_allocate(other._size);
		memcpy(_data, other._data, _size);
	}

	Buffer::Buffer(Buffer&& other) noexcept
	{
		_data = other._data;
		_size = other._size;
		other._data = nullptr;
	}

	Buffer& Buffer::operator = (const Buffer& other)
	{
		_size = other._size;
		memcpy(_data, other._data, _size);
		return *this;
	}

	Buffer& Buffer::operator = (Buffer&& other) noexcept
	{
		delete[] _data;
		_data = other._data;
		_size = other._size;
		other._data = nullptr;

		return *this;
	}

	Buffer::~Buffer() noexcept
	{
		delete[] _data;
	}

	byte* Buffer::pointer() noexcept
	{
		return _data;
	}

	const byte* Buffer::pointer() const noexcept
	{
		return _data;
	}

	size_t Buffer::size() const noexcept
	{
		return _size;
	}

	byte* Buffer::begin() noexcept
	{
		return _data;
	}

	const byte* Buffer::begin() const noexcept
	{
		return _data;
	}

	const byte* Buffer::cbegin() const noexcept
	{
		return _data;
	}

	byte* Buffer::end() noexcept
	{
		return _data + _size;
	}

	const byte* Buffer::end() const noexcept
	{
		return _data + _size;
	}

	const byte* Buffer::cend() const noexcept
	{
		return _data + _size;
	}

	byte& Buffer::at(size_t index)
	{
		if (index >= _size)
			throw out_of_range("ERROR: Invalid buffer index.");

		return _data[index];
	}

	const byte& Buffer::at(size_t index) const
	{
		if (index >= _size)
			throw out_of_range("ERROR: Invalid buffer index.");

		return _data[index];
	}

	byte& Buffer::operator [] (size_t index) noexcept
	{
		return _data[index];
	}

	const byte& Buffer::operator [] (size_t index) const noexcept
	{
		return _data[index];
	}

	void Buffer::clear() noexcept
	{
		memset(_data, 0, _size);
	}

	void Buffer::fill(unsigned char value) noexcept
	{
		memset(_data, value, _size);
	}

	void Buffer::read(void* dest, size_t byte_count) const
	{
		memcpy(dest, _data, _minCount(byte_count));
	}

	int Buffer::readInt(size_t index) const
	{
		return *(reinterpret_cast<int*>(_data + index));
	}

	float Buffer::readFloat(size_t index) const
	{
		return *(reinterpret_cast<float*>(_data + index));
	}

	void Buffer::write(const void* src, size_t byte_count)
	{
		memcpy(_data, src, _minCount(byte_count));
	}

	void Buffer::writeInt(int value, size_t index) const
	{
		*(reinterpret_cast<int*>(_data + index)) = value;
	}

	void Buffer::writeFloat(float value, size_t index) const
	{
		*(reinterpret_cast<float*>(_data + index)) = value;
	}

	Buffer::operator bool() const noexcept
	{
		return _data;
	}

	string Buffer::toString(bool uppercase) const
	{
		return to_hex_string(_data, _size, uppercase);
	}

	void print(const Buffer& buffer)
	{
		cout << buffer.toString();
	}

	void println(const Buffer& buffer)
	{
		cout << buffer.toString() << '\n';
	}

	ostream& operator << (ostream& os, const Buffer& A)
	{
		os << A.toString();
		return os;
	}
}