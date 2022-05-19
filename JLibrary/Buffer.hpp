// JLibrary
// Buffer.hpp
// Created on 2022-04-11 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Header file for the Buffer class.

#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

namespace jlib
{
	// Class that represents a memory buffer.
	class Buffer
	{
		std::byte* _data;
		std::size_t _size;

		// Returns the minimum byte count between _size and byte_count.
		constexpr std::size_t _minCount(std::size_t byte_count) const noexcept;

		// Allocates memory for the buffer.
		void _allocate(std::size_t size);

		public:

		// Default constructor.
		// Sets the buffer to nullptr.
		Buffer();

		// Size constructor.
		// Sets the size of the buffer to size.
		Buffer(std::size_t size);

		// Size and byte constructor.
		// Sets the size of the buffer to size.
		// Sets each byte of the buffer to value.
		Buffer(std::size_t size, unsigned char value);

		// Constructs the Buffer with the contents of the given string.
		// This DOES NOT move the contents from the given range, it simply
		// copies its contents into the new Buffer.
		Buffer(const std::string& str);

		// Constructs the Buffer with the contents in the range[src, src + size).
		// This DOES NOT move the contents from the given range, it simply
		// copies its contents into the new Buffer.
		Buffer(const void* src, std::size_t size);

		// Copy constructor.
		Buffer(const Buffer& other);

		// Move constructor.
		Buffer(Buffer&& other) noexcept;

		// Copy assignment operator.
		Buffer& operator = (const Buffer& other);

		// Move assignment operator.
		Buffer& operator = (Buffer&& other) noexcept;

		// Destructor.
		~Buffer() noexcept;

		// Returns the raw pointer of the buffer.
		std::byte* pointer() noexcept;

		// Returns the raw pointer of the buffer.
		const std::byte* pointer() const noexcept;

		// Returns the size of the buffer.
		std::size_t size() const noexcept;

		// Returns a pointer to the start of the buffer.
		std::byte* begin() noexcept;

		// Returns a pointer to the start of the buffer.
		const std::byte* begin() const noexcept;

		// Returns a pointer to the start of the buffer.
		const std::byte* cbegin() const noexcept;

		// Returns a pointer to 1 past the end of the buffer.
		std::byte* end() noexcept;

		// Returns a pointer to 1 past the end of the buffer.
		const std::byte* end() const noexcept;

		// Returns a pointer to 1 past the end of the buffer.
		const std::byte* cend() const noexcept;

		// Returns the byte at the given index.
		// Throws a std::out_of_range exception if given an invalid index.
		std::byte& at(std::size_t index);

		// Returns the byte at the given index.
		const std::byte& at(std::size_t index) const;

		// Subscript operator.
		// Returns the byte at the given index.
		std::byte& operator [] (std::size_t index) noexcept;

		// Subscript operator.
		// Returns the byte at the given index.
		const std::byte& operator [] (std::size_t index) const noexcept;

		// Clears the buffer by setting all of the bytes to 0.
		void clear() noexcept;

		// Sets all of the bytes of the buffer to the given value.
		void fill(unsigned char value) noexcept;

		// Reads byte_count amount of bytes from the buffer
		// into the source.
		void read(void* dest, std::size_t byte_count) const;

		// Reinterprets the data from the buffer as a 32-bit integer.
		int readInt(std::size_t index) const;

		// Reinterprets the data from the buffer as a 32-bit floating-point.
		float readFloat(std::size_t index) const;

		// Reinterprets the data from the buffer as the given type.
		template <typename T>
		T readT(std::size_t index) const
		{
			return *(reinterpret_cast<T*>(_data + index));
		}

		// Writes byte_count amount of bytes from the source
		// into the buffer.
		void write(const void* src, std::size_t byte_count);

		// Writes a 32-bit integer into the buffer.
		void writeInt(int value, std::size_t index) const;

		// Writes a 32-bit floating-point into the buffer.
		void writeFloat(float value, std::size_t index) const;

		// Writes an object into the buffer.
		template <typename T>
		void writeT(T& value, std::size_t index)
		{
			*(reinterpret_cast<T*>(_data + index)) = value;
		}

		// Returns a reinterpret_cast<T>* pointer.
		template <typename T>
		T* reinterpret() noexcept
		{
			return reinterpret_cast<T*>(_data);
		}

		// Returns a reinterpret_cast<T>* pointer.
		template <typename T>
		const T* reinterpret() const noexcept
		{
			return reinterpret_cast<const T*>(_data);
		}

		// Returns true if the buffer != nullptr.
		explicit operator bool() const noexcept;

		// Returns a std::string constructed from the contents of the buffer in hex.
		std::string toString() const;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Prints the buffer to std::cout in hex format.
	void print(const Buffer& buffer);

	// Prints the buffer to std::cout in hex format with a new line.
	void println(const Buffer& buffer);

	// Overload of std::ostream operator <<
	std::ostream& operator << (std::ostream& os, const Buffer& A);
}