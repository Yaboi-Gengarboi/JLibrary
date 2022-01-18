// Matrix
// Matrix.ixx
// Created on 2022-01-15 by Justyn Durnford
// Last modified on 2022-01-17 by Justyn Durnford
// Module file for the Matrix template class.

module;

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

export module Matrix;

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

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A Matrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <typename T> class Matrix
	{
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = Array<T>::iterator;
		using const_iterator = Array<T>::const_iterator;
		using reverse_iterator = Array<T>::reverse_iterator;
		using const_reverse_iterator = Array<T>::const_reverse_iterator;

		private:

		Array<T> _data;
		size_type _rows;
		size_type _cols;

		// This function allocates memory for the container.
		// It may throw if it fails to do this.
		void allocate(size_type rows, size_type cols)
		{
			if (rows != 0 && cols != 0)
			{
				_rows = rows;
				_cols = cols;

				_data = Array<T>(_rows * _cols);
			}
			else
			{
				_rows = 0;
				_cols = 0;
			}
		}

		// This function deallocates the memory currently used
		// by the container and reallocates sufficient memory
		// for the new requested size.
		// It may throw if it fails to do this.
		void reallocate(size_type rows, size_type cols)
		{
			Array<T> newarr(rows * cols);
			size_type size = std::min(_data.size(), newarr.size());
			std::copy(newarr.begin(), newarr.end(), _data.begin());
			_data = std::move(newarr);
		}

		public:

		// Default constructor.
		Matrix()
		{
			allocate(0, 0);
		}

		// Size constructor.
		Matrix(size_type rows, size_type cols)
		{
			allocate(rows, cols);
		}

		// Size and value constructor.
		// Sets every element of the Matrix to value.
		Matrix(size_type rows, size_type cols, const_reference value)
		{
			allocate(rows, cols);

			for (size_type i = 0; i < _rows * _cols; ++i)
				_data[i] = value;
		}

		// 2-dimensional std::initializer_list constructor.
		Matrix(std::initializer_list<std::initializer_list<T>> list)
		{
			auto iter = list.begin();
			size_type cols = 0;

			while (iter != list.end())
			{
				if (cols < iter->size())
					cols = iter->size();

				++iter;
			}

			allocate(list.size(), cols);
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + _cols, &(_data[row_i * _cols]));
				++row_i;
			}
		}

		// Copy constructor.
		Matrix(const Matrix& other) = default;

		// Constructs the Matrix from another type of Matrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <typename U>
		explicit Matrix(const Matrix<U>& other)
		{
			allocate(other._rows, other._cols);

			for (size_type i = 0; i < _rows * _cols; ++i)
				_data[i] = static_cast<T>(other._data[i]);
		}

		// Move constructor.
		Matrix(Matrix&& other) = default;

		// 2-dimensional std::initializer_list assignment operator.
		Matrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			auto iter = list.begin();
			size_type cols = 0;

			while (iter != list.end())
			{
				if (cols < iter->size())
					cols = iter->size();

				++iter;
			}

			allocate(list.size(), cols);
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + _cols, &(_data[row_i * _cols]));
				++row_i;
			}

			return *this;
		}

		// Copy assignment operator.
		Matrix& operator = (const Matrix& other) = default;

		// Move assignment operator.
		Matrix& operator = (Matrix&& other) = default;

		// Destructor.
		~Matrix() = default;

		// Returns the number of rows in the Matrix.
		size_type rowCount() const noexcept
		{
			return _rows;
		}

		// Returns the number of columns in the Matrix.
		size_type colCount() const noexcept
		{
			return _cols;
		}

		// Returns the number of elements in the Matrix.
		size_type size() const noexcept
		{
			return _data.size();
		}

		// Returns the pointer of the Matrix.
		pointer data() noexcept
		{
			return _data.data();
		}

		// Returns the pointer of the Matrix.
		const_pointer data() const noexcept
		{
			return _data.data();
		}

		// Returns an iterator pointing to the first element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		iterator begin() noexcept
		{
			return _data.begin();
		}

		// Returns an iterator pointing to the first element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_iterator begin() const noexcept
		{
			return _data.cbegin();
		}

		// Returns an iterator pointing to the first element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_iterator cbegin() const noexcept
		{
			return _data.cbegin();
		}

		// Returns a reverse iterator pointing to the first element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		reverse_iterator rbegin() noexcept
		{
			return std::reverse_iterator<iterator>(_data + _data.size());
		}

		// Returns a reverse iterator pointing to the first element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_reverse_iterator rbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + _data.size());
		}

		// Returns a reverse iterator pointing to the first element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_reverse_iterator crbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + _data.size());
		}

		// Returns an iterator pointing to 1 past the last element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		iterator end() noexcept
		{
			return _data.end();
		}

		// Returns an iterator pointing to 1 past the last element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_iterator end() const noexcept
		{
			return _data.cend();
		}

		// Returns an iterator pointing to 1 past the last element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_iterator cend() const noexcept
		{
			return _data.cend();
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		reverse_iterator rend() noexcept
		{
			return std::reverse_iterator<iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_reverse_iterator rend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the Matrix.
		// Returns nullptr if the Matrix is empty.
		const_reverse_iterator crend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns an iterator pointing to the first element of the given row.
		iterator rowBegin(size_type row) noexcept
		{
			return _data.begin() + (_cols * row);
		}

		// Returns an iterator pointing to the first element of the given row.
		const_iterator rowBegin(size_type row) const noexcept
		{
			return _data.cbegin() + (_cols * row);
		}

		// Returns the element at the given index of the Matrix.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type n)
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid Matrix index.");
			return _data[n];
		}

		// Returns the element at the given index of the Matrix.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type n) const
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid Matrix index.");
			return _data[n];
		}

		// Returns the element at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type row, size_type col)
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(row * _cols) + col];
		}

		// Returns the element at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type row, size_type col) const
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(row * _cols) + col];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type n, const_reference value)
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid table index.");
			_data[n] = value;
		}

		// Sets the element at [row][col] to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type row, size_type col, const_reference value)
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			_data[(row * _cols) + col] = value;
		}

		// Empties the Matrix.
		void clear() noexcept
		{
			_data.clear();
		}

		// Resizes the Matrix with the copied elements.
		// It may throw if it fails to do this.
		void resize(size_type rows, size_type cols)
		{
			reallocate(rows, cols);
		}

		// Returns a copy of the given row.
		Array<T> getRow(size_type row) const
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");

			Array<T> arr;
			for (size_type col_i(0); col_i < _cols; ++col_i)
				arr[col_i] = _data[row][col_i];

			return arr;
		}

		// Returns a copy of the given column.
		Array<T> getColumn(size_type col) const
		{
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			Array<T> arr;
			for (size_type row_i(0); row_i < _rows; ++row_i)
				arr[row_i] = _data[row_i][col];

			return arr;
		}

		// Swaps the contents of this Matrix with another Matrix.
		void swapWith(Matrix& other) noexcept
		{
			_data.swapWith(other._data);
			std::swap(_rows, other._rows);
			std::swap(_cols, other._cols);
		}

		// Returns the element at the given index the Matrix.
		// Does NOT perform bounds-checking.
		reference operator [] (size_type n)
		{
			return _data[n];
		}

		// Returns the element at the given index the Matrix.
		// Does NOT perform bounds-checking.
		const_reference operator [] (size_type n) const
		{
			return _data[n];
		}

		// Returns the element at [row][col].
		// Does NOT perform bounds-checking.
		reference operator () (size_type row, size_type col)
		{
			return _data[(row * _cols) + col];
		}

		// Returns the element at [row][col].
		// Does NOT perform bounds-checking.
		const_reference operator () (size_type row, size_type col) const
		{
			return _data[(row * _cols) + col];
		}
	};

	// Overload of binary operator == 
	template <typename T>
	bool operator == (const Matrix<T>& A, const Matrix<T>& B)
	{
		if (A.rowCount() != B.rowCount() || A.colCount() != B.colCount())
			return false;

		for (std::size_t i(0); i < A.size(); ++i)
		{
			if (A[i] != B[i])
				return false;
		}

		return true;
	}

	// Overload of binary operator == 
	template <typename T>
	bool operator != (const Matrix<T>& A, const Matrix<T>& B)
	{
		if (A.rowCount() != B.rowCount() || A.colCount() != B.colCount())
			return true;

		for (std::size_t i(0); i < A.size(); ++i)
		{
			if (A[i] != B[i])
				return true;
		}

		return false;
	}
}