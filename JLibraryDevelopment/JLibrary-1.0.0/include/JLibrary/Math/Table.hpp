// JLibraryDevelopment
// Table.hpp
// Created on 2021-06-27 by Justyn Durnford
// Last modified on 2021-06-27 by Justyn Durnford
// Header file for the Table template class.

#pragma once

#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace jlib
{
	// 
	template <std::semiregular T> class Table
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;

		private:

		T** data_;
		std::size_t rows_;
		std::size_t cols_;

		// 
		void allocate(std::size_t rows, std::size_t cols)
		{
			if (rows != 0 && cols != 0)
			{
				rows_ = rows;
				cols_ = cols;
				data_ = new T*[rows_];
				for (std::size_t row_i(0); row_i < rows_; ++row_i)
					data_[row_i] = new T[cols_];
			}
			else 
			{
				rows_ = 0;
				cols_ = 0;
				data_ = nullptr;
			}
		}

		// 
		void deallocate() noexcept
		{
			if (data_ != nullptr)
			{
				for (std::size_t row_i(0); row_i < rows_; ++row_i)
					delete[] data_[row_i];
				delete[] data_;
			}
		}

		// 
		void reallocate(std::size_t rows, std::size_t cols)
		{
			if (rows != rows_ || cols != cols_)
			{
				deallocate();
				allocate(rows, cols);
			}
		}

		// 
		void copyElements(T* dst_begin, const T* src_begin, std::size_t count)
		{
			for (std::size_t i(0); i < count; ++i)
				dst_begin[i] = src_begin[i];
		}

		public:

		// Default constructor.
		Table()
		{
			allocate(0, 0);
		}

		// Size and constructor.
		Table(std::size_t rows, std::size_t cols)
		{
			allocate(rows, cols);
		}

		// Size and value constructor.
		// Sets every element of the Table to value.
		Table(std::size_t rows, std::size_t cols, const T& value)
		{
			allocate(rows, cols);
			for (std::size_t row_i(0); row_i < rows_; ++row_i)
			{
				for (std::size_t col_i(0); col_i < cols_; ++col_i)
					data_[row_i][col_i] = value;
			}
		}

		// 2-dimensional std::initializer_list constructor.
		Table(std::initializer_list<std::initializer_list<T>> list)
		{
			allocate(list.size(), list.begin->size());
			std::size_t row_i(0);

			for (const auto& row : list)
				copyElements(data_[row_i++], row.begin(), cols_);
		}

		// Copy constructor.
		Table(const Table& other)
		{
			allocate(other.rows_, other.cols_);

			for (std::size_t row_i(0); row_i < rows_; ++row_i)
				copyElements(data_[row_i], other.data_[row_i], cols_);
		}

		// Constructs the Table from another type of Table.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::semiregular U>
		explicit Table(const Table<U>& other)
		{
			allocate();

			for (std::size_t row_i(0); row_i < rows_; ++row_i)
			{
				for (std::size_t col_i(0); col_i < cols_; ++col_i)
					data_[row_i][col_i] = static_cast<T>(other.data_[row_i][col_i]);
			}
		}

		// Move constructor.
		Table(Table&& other) noexcept
		{
			data_ = other.data_;
			rows_ = other.rows_;
			cols_ = other.cols_;

			other.data_ = nullptr;
			other.rows_ = 0;
			other.cols_ = 0;
		}

		// Copy assignment operator.
		Table& operator = (const Table& other)
		{
			reallocate(other.rows_, other.cols_);

			for (std::size_t row_i(0); row_i < rows_; ++row_i)
				copyElements(data_[row_i], other.data_[row_i], cols_);

			return *this;
		}

		// Move assignment operator.
		Table(Table&& other) noexcept
		{
			data_ = other.data_;
			rows_ = other.rows_;
			cols_ = other.cols_;

			other.data_ = nullptr;
			other.rows_ = 0;
			other.cols_ = 0;

			return *this;
		}

		// Destructor.
		~Table() noexcept
		{
			deallocate();
		}

		// Returns the number of rows in the Table.
		std::size_t rowCount() const
		{
			return rows_;
		}

		// Returns the number of columns in the Table.
		std::size_t colCount() const
		{
			return cols_;
		}

		// Returns a copy of the given row.
		T* getRow(std::size_t row) const
		{
			if (row >= rows_)
				throw std::out_of_range("Invalid row index");

			T* arr = new T[cols_];
			for (std::size_t col_i(0); col_i < cols_; ++col_i)
				arr[col_i] = data_[row][col_i];

			return arr;
		}

		// Returns a copy of the given column.
		T* getCol(std::size_t col) const
		{
			if (col >= cols_)
				throw std::out_of_range("Invalid column index");

			T* arr = new T[rows_];
			for (std::size_t row_i(0); row_i < rows_; ++row_i)
				arr[row_i] = data_[row_i][col];

			return arr;
		}

		// Returns the nth element of the Table.
		// Performs bounds-checking.
		T& at(std::size_t n)
		{
			if (n >= rows_ * cols_)
				throw std::out_of_range("Invalid table index");

			return data_[n / rows_][n % cols_];
		}

		// Returns the nth element of the Table.
		// Performs bounds-checking.
		const T& at(std::size_t n) const
		{
			if (n >= rows_ * cols_)
				throw std::out_of_range("Invalid table index");

			return data_[n / rows_][n % cols_];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		T& at(std::size_t row, std::size_t col)
		{
			if (row >= rows_)
				throw std::out_of_range("Invalid row index");
			if (col >= cols_)
				throw std::out_of_range("Invalid column index");

			return data_[row][col];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		const T& at(std::size_t row, std::size_t col) const
		{
			if (row >= rows_)
				throw std::out_of_range("Invalid row index");
			if (col >= cols_)
				throw std::out_of_range("Invalid column index");

			return data_[row][col];
		}

		// Sets the nth element of the Table to value.
		// Performs bounds-checking.
		void set(std::size_t n, const T& value)
		{
			if (n >= rows_ * cols_)
				throw std::out_of_range("Invalid table index");

			data_[n / rows_][n % cols_] = value;
		}

		// Sets the element at [row][col] to value.
		// Performs bounds-checking.
		void set(std::size_t row, std::size_t col, const T& value)
		{
			if (row >= rows_)
				throw std::out_of_range("Invalid row index");
			if (col >= cols_)
				throw std::out_of_range("Invalid column index");

			data_[row][col] = value;
		}

		// Returns the nth element of the Matrix.
		T& operator () (std::size_t n)
		{
			return data_[n / rows_][n % cols_];
		}

		// Returns the nth element of the Matrix.
		const T& operator () (std::size_t n) const
		{
			return data_[n / rows_][n % cols_];
		}

		// Returns the element at [row][col].
		T& operator () (std::size_t row, std::size_t col)
		{
			return data_[row][col];
		}

		// Returns the element at [row][col].
		const T& operator () (std::size_t row, std::size_t col) const
		{
			return data_[row][col];
		}
	};
}

// Overload of binary operator ==
template <std::regular T>
bool operator == (const jlib::Table<T>& A, const jlib::Table<T>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
		{
			if (A(row_i, col_i) != B(row_i, col_i))
				return false;
		}
	}

	return true;
}

// Overload of binary operator !=
template <std::regular T>
bool operator != (const jlib::Table<T>& A, const jlib::Table<T>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
		{
			if (A(row_i, col_i) != B(row_i, col_i))
				return true;
		}
	}

	return false;
}