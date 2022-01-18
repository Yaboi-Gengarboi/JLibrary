// Array
// Array.ixx
// Created on 2022-01-14 by Justyn Durnford
// Last modified on 2022-01-14 by Justyn Durnford
// Module file for the Array template class.

module;

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

export module Array;

export namespace jlib
{
	// This template class serves as a resizable container.
	// Elements cannot be added or removed dynamically, but
	// the Array can be resized manually. It does not allocate extra 
	// memory, so if the Array is resized more than a few times,
	// it may be in your best interest to use a std::vector instead.
	template <typename T> class Array
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = const std::reverse_iterator<iterator>;

		private:

		pointer _data;
		size_type _size;

		// This function allocates memory for the container.
		// It may throw if it fails to do this.
		void allocate(size_type size)
		{
			if (size == 0)
			{
				_data = nullptr;
				_size = 0;
			}
			else
			{
				try
				{
					_data = new value_type[size];
					_size = size;
				}
				catch (...)
				{
					_data = nullptr;
					_size = 0;
					throw;
				}
			}
		}

		// This function deallocates the memory currently used
		// by the container and reallocates sufficient memory
		// for the new requested size.
		// It may throw if it fails to do this.
		void reallocate(size_type size)
		{
			if (size != _size)
			{
				delete[] _data;
				allocate(size);
			}
		}

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

			for (size_type i(0); i < _size; ++i)
				_data[i] = value;
		}

		// Constructs the Array with the contents in the range[begin, end).
		// This DOES NOT move the contents from the given range, it simply
		// copies its contents into the new Array.
		Array(const_pointer begin, const_pointer end)
		{
			size_type size = end - begin;
			allocate(size);
			std::copy(begin, end, _data);
		}

		// std::initializer_list constructor.
		Array(std::initializer_list<T> elems)
		{
			allocate(elems.size());
			std::copy(elems.begin(), elems.end(), _data);
		}

		// Copy constructor.
		Array(const Array& other)
		{
			allocate(other._size);
			std::copy(other._data, other._data + _size, _data);
		}

		// Constructs the Array from another type of Array.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <typename U>
		explicit Array(const Array<U>& other)
		{
			allocate(other._size);

			for (size_type i(0); i < _size; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Move constructor.
		Array(Array&& other) noexcept
		{
			_data = other._data;
			_size = other._size;
			other._data = nullptr;
			other._size = 0;
		}

		// std::initializer_list assignment operator.
		Array& operator = (std::initializer_list<T> elems)
		{
			reallocate(elems.size());
			std::copy(elems.begin(), elems.end(), _data);
			return *this;
		}

		// Copy assignment operator.
		Array& operator = (const Array& other)
		{
			reallocate(other._size);
			std::copy(other._data, other._data + _size, _data);
			return *this;
		}

		// Move assignment operator.
		Array& operator = (Array&& other) noexcept
		{
			delete[] _data;
			_data = other._data;
			_size = other._size;
			other._data = nullptr;
			other._size = 0;
			return *this;
		}

		// Destructor.
		~Array() noexcept
		{
			delete[] _data;
		}

		// Returns the size of the Array.
		size_type size() const noexcept
		{
			return _size;
		}

		// Returns true if the Array is empty.
		bool isEmpty() const noexcept
		{
			return _size != 0;
		}

		// Returns the first element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		reference first()
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[0];
		}

		// Returns the first element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		const_reference first() const
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[0];
		}

		// Returns the last element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		reference last()
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[_size - 1];
		}

		// Returns the last element of the Array.
		// Throws a std::out_of_range if the Array is empty.
		const_reference last() const
		{
			if (_size == 0)
				throw std::out_of_range("ERROR: Empty array.");

			return _data[_size - 1];
		}

		// Returns the pointer of the Array.
		pointer data() noexcept
		{
			return _data;
		}

		// Returns the pointer of the Array.
		const_pointer data() const noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		iterator begin() noexcept
		{
			return iterator(_data);
		}

		// Returns an iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator begin() const noexcept
		{
			return const_iterator(_data);
		}

		// Returns an iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator cbegin() const noexcept
		{
			return const_iterator(_data);
		}

		// Returns a reverse iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(_data);
		}

		// Returns a reverse iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(_data);
		}

		// Returns a reverse iterator pointing to the first element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(_data);
		}

		// Returns an iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		iterator end() noexcept
		{
			return iterator(_data + _size);
		}

		// Returns an iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator end() const noexcept
		{
			return const_iterator(_data + _size);
		}

		// Returns an iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_iterator cend() const noexcept
		{
			return const_iterator(_data + _size);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		reverse_iterator rend() noexcept
		{
			return reverse_iterator(_data + _size);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(_data + _size);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Array.
		// Returns nullptr if the Array is empty.
		const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(_data + _size);
		}

		// Returns the element at the given index of the Array.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= _size)
				throw std::out_of_range("ERROR: Invalid array index.");

			return _data[index];
		}

		// Returns the element at the given index of the Array.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type index) const
		{
			if (index >= _size)
				throw std::out_of_range("ERROR: Invalid array index.");

			return _data[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type index, const_reference value)
		{
			if (index >= _size)
				throw std::out_of_range("ERROR: Invalid array index.");

			_data[index] = value;
		}

		// Empties the Array.
		void clear() noexcept
		{
			delete[] _data;
			_size = 0;
		}

		// Resizes the Array with the copied elements.
		// It may throw if it fails to do this.
		void resize(size_type new_size)
		{
			if (new_size == 0)
				return;

			if (new_size == 0)
			{
				delete[] _data;
				_data = nullptr;
				_size = 0;
				return;
			}

			try
			{
				pointer new_data = new value_type[new_size];
				std::copy(_data, _data + new_size, new_data);
				delete[] _data;
				_data = new_data;
				_size = new_size;
				new_data = nullptr;
			}
			catch (...) { throw; }
		}

		// Swaps the contents of this Array with another Array.
		void swapWith(Array& other) noexcept
		{
			std::swap(_data, other._data);
			std::swap(_size, other._size);
		}

		// Returns the element at the given index the Array.
		// Does NOT perform bounds-checking.
		reference operator [] (size_type index)
		{
			return _data[index];
		}

		// Returns the element at the given index the Array.
		// Does NOT perform bounds-checking.
		const_reference operator [] (size_type index) const
		{
			return _data[index];
		}
	};

	// Overload of binary operator ==
	template <typename T>
	bool operator == (const Array<T>& A, const Array<T>& B)
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
	template <typename T>
	bool operator != (const Array<T>& A, const Array<T>& B)
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
}