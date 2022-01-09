// JLibrary
// FixedArray.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the FixedArray template class.

module;

#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

export module FixedArray;

export namespace jlib
{
	// 
	template <typename T, std::size_t N> class FixedArray
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		private:

		pointer _data;

		void allocate()
		{
			if (N != 0)
			{
				try
				{
					_data = new value_type[N];
				}
				catch (...)
				{
					_data = nullptr;
					throw;
				}
			}
			else
				_data = nullptr;
		}

		public:

		// Default constructor.
		FixedArray()
		{
			allocate();
		}

		// Value constructor.
		FixedArray(const_reference value)
		{
			allocate();
			for (size_type i = 0; i < N; ++i)
				_data[i] = value;
		}

		// std::initializer_list constructor.
		FixedArray(std::initializer_list<T> elems)
		{
			allocate();
			std::copy(elems.begin(), elems.begin() + N, _data);
		}

		// std::array constructor.
		FixedArray(const std::array<T, N>& arr)
		{
			allocate();
			std::copy(arr.begin(), arr.end(), _data);
		}

		// Copy constructor.
		FixedArray(const FixedArray& other)
		{
			allocate();
			std::copy(other.begin(), other.end(), _data);
		}

		// Different-type Copy constructor.
		template <typename U>
		explicit FixedArray(const FixedArray<U, N>& other)
		{
			allocate();
			for (size_type i = 0; i < N; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Move constructor.
		FixedArray(FixedArray&& other) noexcept
		{
			std::swap(_data, other._data);
		}

		// std::initializer_list assignment operator.
		FixedArray& operator = (std::initializer_list<T> elems)
		{
			std::copy(elems.begin(), elems.begin() + N, _data);
			return *this;
		}

		// std::array assignment operator.
		FixedArray& operator = (const std::array<T, N>& arr)
		{
			std::copy(arr.begin(), arr.end(), _data);
			return *this;
		}

		// Copy assignment operator.
		FixedArray& operator = (const FixedArray& other)
		{
			std::copy(other.begin(), other.end(), _data);
			return *this;
		}

		// Move assignment operator.
		FixedArray& operator = (FixedArray&& other) noexcept
		{
			delete[] _data;
			_data = nullptr;
			std::swap(_data, other._data);
			return *this;
		}

		// Destructor.
		~FixedArray() noexcept
		{
			delete[] _data;
		}

		// Returns the size of the FixedArray.
		constexpr size_type size() const noexcept
		{
			return N;
		}

		// Returns true if the FixedArray has a size of 0.
		constexpr bool isEmpty() const noexcept
		{
			return N == 0;
		}

		// Returns the first element of the FixedArray.
		reference first()
		{
			return _data[0];
		}

		// Returns the first element of the FixedArray.
		const_reference first() const
		{
			return _data[0];
		}

		// Returns the last element of the FixedArray.
		reference last()
		{
			return _data[N - 1];
		}

		// Returns the last element of the FixedArray.
		const_reference last() const
		{
			return _data[N - 1];
		}

		// Returns the pointer of the FixedArray.
		pointer data() noexcept
		{
			return _data;
		}

		// Returns the pointer of the FixedArray.
		const_pointer data() const noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		iterator begin() noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator begin() const noexcept
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator cbegin() const noexcept
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		reverse_iterator rbegin() noexcept
		{
			return std::reverse_iterator<iterator>(_data + N);
		}

		// Returns a reverse iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator rbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + N);
		}

		// Returns a reverse iterator pointing to the first element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator crbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + N);
		}

		// Returns an iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		iterator end() noexcept
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator end() const noexcept
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_iterator cend() const noexcept
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		reverse_iterator rend() noexcept
		{
			return std::reverse_iterator<iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator rend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedArray.
		// Returns nullptr if the FixedArray is empty.
		const_reverse_iterator crend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns the element at the given index of the FixedArray.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid array index.");
			return _data[index];
		}

		// Returns the element at the given index of the FixedArray.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type index) const
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid array index.");
			return _data[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type index, const_reference value)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid array index.");
			_data[index] = value;
		}

		// Swaps the contents of this FixedArray with another FixedArray.
		void swapWith(FixedArray& other) noexcept
		{
			std::swap(_data, other._data);
		}

		// Returns the element at the given index the FixedArray.
		// Does NOT perform bounds-checking.
		reference operator [] (size_type index)
		{
			return _data[index];
		}

		// Returns the element at the given index the FixedArray.
		// Does NOT perform bounds-checking.
		const_reference operator [] (size_type index) const
		{
			return _data[index];
		}
	};

	// Overload of binary operator ==
	template <typename T, std::size_t N>
	bool operator == (const FixedArray<T, N>& A, const FixedArray<T, N>& B)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (A[i] != B[i])
				return false;
		}

		return true;
	}

	// Overload of binary operator !=
	template <typename T, std::size_t N>
	bool operator != (const FixedArray<T, N>& A, const FixedArray<T, N>& B)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (A[i] != B[i])
				return true;
		}

		return false;
	}
}