// JLibraryDevelopment
// Array.hpp
// Created on 2021-06-25 by Justyn Durnford
// Last modified on 2021-07-15 by Justyn Durnford
// Header file for the Array template class.

#pragma once

#include <concepts>
#include <initializer_list>
#include <stdexcept>

namespace jlib
{
	// 
	template <std::semiregular T> class Array
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using iterator = T*;
		using const_iterator = const T*;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		private:

		pointer data_;
		size_type size_;

		// 
		void allocate(size_type size)
		{
			if (size == 0)
			{
				data_ = nullptr;
				size_ = 0;
			}
			else
			{
				try
				{
					data_ = new T[size];
					size_ = size;
				}
				catch (...)
				{
					data_ = nullptr;
					size_ = 0;
					throw;
				}
			}
		}

		// 
		void reallocate(size_type size)
		{
			if (size != size_)
			{
				delete[] data_;
				allocate(size);
			}
		}

		// 
		void copyFrom(const_pointer src_begin, size_type size)
		{
			for (std::size_t i(0); i < size; ++i)
				data_[i] = src_begin[i];
		}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		public:

		// Default constructor.
		Array()
		{
			allocate(0);
		}

		// Size constructor.
		Array(size_type size)
		{
			allocate(size);
		}

		// Size and value constructor.
		Array(size_type size, const_reference value)
		{
			allocate(size);

			for (std::size_t i(0); i < size_; ++i)
				data_[i] = value;
		}

		// Constructs the Array with the contents in the range[begin, end).
		// This DOES NOT move the contents from the given range, it simply
		// copies its contents into the new Array.
		Array(const_pointer begin, const_pointer end)
		{
			std::size_t size = end - begin;
			allocate(size);
			copyFrom(begin, size);
		}

		// std::initializer_list constructor.
		Array(const std::initializer_list<T>& list)
		{
			allocate(list.size());

			std::size_t i(0);
			for (const T& item : list)
				data_[i++] = item;
		}

		// Copy constructor.
		Array(const Array& other)
		{
			allocate(other.size_);
			copyFrom(other.data_, size_);
		}

		// Constructs the Array from another type of Array.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::semiregular U>
		explicit Array(const Array<U>& other)
		{
			allocate(other.size_);

			for (std::size_t i(0); i < size_; ++i)
				data_[i] = static_cast<T>(other.data_[i]);
		}

		// Move constructor.
		Array(Array&& other) noexcept
		{
			data_ = other.data_;
			size_ = other.size_;
			other.data_ = nullptr;
			other.size_ = 0;
		}

		// Copy assignment operator.
		Array& operator = (const Array& other)
		{
			reallocate(other.size_);
			copyFrom(other.data_, size_);
			return *this;
		}

		// Move assignment operator.
		Array& operator = (Array&& other) noexcept
		{
			delete[] data_;
			data_ = other.data_;
			size_ = other.size_;
			other.data_ = nullptr;
			other.size_ = 0;
			return *this;
		}

		// Destructor.
		~Array() noexcept
		{
			delete[] data_;
		}

		// Returns the size of the Array.
		size_type size() const noexcept
		{
			return size_;
		}

		// Returns true if the Array is empty.
		bool isEmpty() const noexcept
		{
			return size_ != 0;
		}

		// Returns the underlying array pointer.
		pointer data() noexcept
		{
			return data_;
		}

		// Returns the underlying array pointer.
		const_pointer data() const noexcept
		{
			return data_;
		}

		// 
		iterator begin() noexcept
		{
			return iterator(data_);
		}

		// 
		const_iterator begin() const noexcept
		{
			return const_iterator(data_);
		}

		// 
		const_iterator cbegin() const noexcept
		{
			return const_iterator(data_);
		}

		// 
		iterator end() noexcept
		{
			return iterator(data_ + size_);
		}

		// 
		const_iterator end() const noexcept
		{
			return const_iterator(data_ + size_);
		}

		// 
		const_iterator cend() const noexcept
		{
			return const_iterator(data_ + size_);
		}

		// Empties the Array.
		void clear() noexcept
		{
			delete[] data_;
			size_ = 0;
		}

		// Swaps the contents of this Array buffer with those of another.
		void swapWith(Array& other) noexcept
		{
			pointer this_data = data_;
			size_type this_size = size_;

			data_ = other.data_;
			size_ = other.size_;

			other.data_ = this_data;
			other.size_ = this_size;
		}

		// Returns the first element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		reference first()
		{
			if (size_ == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return data_[0];
		}

		// Returns the first element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		const_reference first() const
		{
			if (size_ == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return data_[0];
		}

		// Returns the last element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		reference last()
		{
			if (size_ == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return data_[size_ - 1];
		}

		// Returns the last element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		const_reference last() const
		{
			if (size_ == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return data_[size_ - 1];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= size_)
				throw std::out_of_range("ERROR: Invalid array index.");

			return data_[index];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type index) const
		{
			if (index >= size_)
				throw std::out_of_range("ERROR: Invalid array index.");

			return data_[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type index, const_reference value)
		{
			if (index >= size_)
				throw std::out_of_range("ERROR: Invalid array index.");

			data_[index] = value;
		}

		// Returns the element at the given index.
		reference operator [] (size_type index) noexcept
		{
			return data_[index];
		}

		// Returns the element at the given index.
		const_reference operator [] (size_type index) const noexcept
		{
			return data_[index];
		}
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
template <std::regular T>
bool operator == (const jlib::Array<T>& A, const jlib::Array<T>& B)
{
	if (A.size() != B.size())
		return false;

	for (std::size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return false;
	}

	return true;
}

// Overload of binary operator !=
template <std::regular T>
bool operator != (const jlib::Array<T>& A, const jlib::Array<T>& B)
{
	if (A.size() != B.size())
		return true;

	for (std::size_t i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i])
			return true;
	}

	return false;
}