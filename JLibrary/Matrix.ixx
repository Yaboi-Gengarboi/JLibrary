// JLibrary
// Matrix.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the Matrix template class.

module;

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

export module Matrix;

import Arithmetic;
import Array;
import Vector2;

export namespace jlib
{
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

		// 
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

		// 
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

		// 
		pointer data() noexcept
		{
			return _data.data();
		}

		// 
		const_pointer data() const noexcept
		{
			return _data.data();
		}

		// 
		iterator begin() noexcept
		{
			return _data.begin();
		}

		// 
		const_iterator begin() const noexcept
		{
			return _data.cbegin();
		}

		// 
		const_iterator cbegin() const noexcept
		{
			return _data.cbegin();
		}

		// 
		iterator end() noexcept
		{
			return _data.end();
		}

		// 
		const_iterator end() const noexcept
		{
			return _data.cend();
		}

		// 
		const_iterator cend() const noexcept
		{
			return _data.cend();
		}

		// 
		iterator rowBegin(size_type row) noexcept
		{
			return _data.begin() + (_cols * row);
		}

		// 
		const_iterator rowBegin(size_type row) const noexcept
		{
			return _data.cbegin() + (_cols * row);
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		reference at(size_type n)
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid Matrix index.");
			return _data[n];
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		const_reference at(size_type n) const
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid Matrix index.");
			return _data[n];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		reference at(size_type row, size_type col)
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(row * _cols) + col];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		const_reference at(size_type row, size_type col) const
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(row * _cols) + col];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		reference at(const Vector2<std::size_t>& pos)
		{
			if (pos.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (pos.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		template <arithmetic U>
		reference at(const Vector2<U>& pos)
		{
			if (static_cast<size_t>(pos.y) >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (static_cast<size_t>(pos.x) >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		const_reference at(const Vector2<size_type>& pos) const
		{
			if (pos.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (pos.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		// Performs bounds-checking.
		template <arithmetic U>
		const_reference at(const Vector2<U>& pos) const
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));

			if (v.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (v.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			return _data[(v.y * _cols) + v.x];
		}

		// Sets the nth element of the Matrix to value.
		// Performs bounds-checking.
		void set(size_type n, const_reference value)
		{
			if (n >= _data.size())
				throw std::out_of_range("ERROR: Invalid table index.");
			_data[n] = value;
		}

		// Sets the element at [row][col] to value.
		// Performs bounds-checking.
		void set(size_type row, size_type col, const_reference value)
		{
			if (row >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (col >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			_data[(row * _cols) + col] = value;
		}

		// Sets the element at [pos.y][pos.x] to value.
		// Performs bounds-checking.
		void set(const Vector2<size_type>& pos, const_reference value)
		{
			if (pos.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (pos.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			_data[(pos.y * _cols) + pos.x] = value;
		}

		// Sets the element at [pos.y][pos.x] to value.
		// Performs bounds-checking.
		template <arithmetic U>
		void set(const Vector2<U>& pos, const_reference value)
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));

			if (v.y >= _rows)
				throw std::out_of_range("ERROR: Invalid row index.");
			if (v.x >= _cols)
				throw std::out_of_range("ERROR: Invalid column index.");

			_data[(v.y * _cols) + v.x] = value;
		}

		// 
		void clear() noexcept
		{
			_data.clear();
		}

		// 
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
		Array<T> getCol(size_type col) const
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

		// Returns the nth element of the Matrix.
		reference operator [] (size_type n)
		{
			return _data[n];
		}

		// Returns the nth element of the Matrix.
		const_reference operator [] (size_type n) const
		{
			return _data[n];
		}

		// Returns the element at [row][col].
		reference operator () (size_type row, size_type col)
		{
			return _data[(row * _cols) + col];
		}

		// Returns the element at [row][col].
		const_reference operator () (size_type row, size_type col) const
		{
			return _data[(row * _cols) + col];
		}

		// Returns the element at [pos.y][pos.x].
		reference operator () (const Vector2<size_type>& pos)
		{
			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		template <arithmetic U>
		reference operator () (const Vector2<U>& pos)
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));
			return _data[(v.y * _cols) + v.x];
		}

		// Returns the element at [pos.y][pos.x].
		const_reference operator () (const Vector2<size_type>& pos) const
		{
			return _data[(pos.y * _cols) + pos.x];
		}

		// Returns the element at [pos.y][pos.x].
		template <arithmetic U>
		const_reference operator () (const Vector2<U>& pos) const
		{
			Vector2<size_t> v(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y));
			return _data[(v.y * _cols) + v.x];
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