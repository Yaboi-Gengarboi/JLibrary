// JLibraryDevelopment
// Matrix.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-05-23 by Justyn Durnford
// Header file for the Matrix template class.

#pragma once

#include <Jlibrary/Math/Arithmetic.hpp>

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace jl
{
	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A Matrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <std_arithmetic T, std::size_t R, std::size_t C> class Matrix
	{
		// Private member variable
		std::array<std::array<T, C>, R> data_;

		// Private member functions

		//
		inline void checkRow(std::size_t row) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
		}

		//
		inline void checkCol(std::size_t col) const
		{
			if (col >= C)
				throw std::out_of_range("Invalid column index");
		}

		// 
		void checkBounds(std::size_t row, std::size_t col) const
		{
			checkRow(row);
			checkCol(col);
		}

		public:

		using value_type = T;
		using size_type = std::size_t;
		using reference = T&;
		using const_reference = const T&;

		// 
		Matrix() = default;

		// 
		Matrix(T value)
		{
			for (std::size_t row_i(0u); row_i < R; ++row_i)
			{
				for (std::size_t col_i(0u); col_i < C; ++col_i)
					data_[row_i][col_i] = value;
			}
		}

		// 
		Matrix(std::initializer_list<std::initializer_list<T>> list)
		{
			std::size_t row_i(0u);

			for (const auto& row : list)
			{
				std::copy(row.begin(), row.begin() + C, data_[row_i].begin());
				++row_i;
			}
		}

		// 
		template <std_arithmetic U>
		explicit Matrix(const Matrix<U, R, C>& other)
		{
			for (std::size_t row_i(0u); row_i < R; ++row_i)
			{
				for (std::size_t c(0u); c < C; ++c)
					data_[row_i][c] = static_cast<T>(other.data_[row_i][c]);
			}
		}

		// 
		Matrix(const Matrix& other) = default;

		// 
		Matrix(Matrix&& other) = default;

		// 
		Matrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			std::size_t row_i(0u);

			for (const auto& row : list)
			{
				std::copy(row.begin(), row.begin() + C, data_[row_i].begin());
				++row_i;
			}

			return *this;
		}

		// 
		Matrix& operator = (const Matrix& other) = default;

		// 
		Matrix& operator = (Matrix&& other) = default;

		// 
		~Matrix() = default;

		// 
		std::size_t rowCount() const
		{
			return R;
		}

		// 
		std::size_t colCount() const
		{
			return C;
		}

		//
		std::array<T, C> getRow(std::size_t row) const
		{
			checkRow(row);
			return data_[row];
		}

		//
		std::array<T, R> getCol(std::size_t col) const
		{
			checkRow(col);
			std::array<T, R> arr;

			for (std::size_t row_i = 0; row_i < R; ++row_i)
				arr[row_i] = data_[row_i][col];

			return arr;
		}

		// 
		T& at(std::size_t row, std::size_t col)
		{
			checkBounds(row, col);
			return data_[row][col];
		}

		// 
		const T& at(std::size_t row, std::size_t col) const
		{
			checkBounds(row, col);
			return data_[row][col];
		}

		// 
		void set(std::size_t row, std::size_t col, T value)
		{
			checkBounds(row, col);
			data_[row][col] = value;
		}

		// 
		T& operator () (std::size_t row, std::size_t col)
		{
			return data_[row][col];
		}

		// 
		const T& operator () (std::size_t row, std::size_t col) const
		{
			return data_[row][col];
		}
	};

	// Returns the determinant of the 2x2 Matrix formed as
	// { a, b }
	// { c, d }
	template <std_arithmetic T>
	inline T determinant(T a, T b, T c, T d)
	{
		return (a * d) - (b * c);
	}

	// Returns the determinant of the 2x2 Matrix.
	template <std_arithmetic T>
	inline T determinant(const Matrix<T, 2, 2>& M)
	{
		return (M(0, 0) * M(1, 1)) - (M(1, 0) * M(0, 1));
	}

	// Returns the determinant of the 3x3 Matrix.
	template <std_arithmetic T>
	T determinant(const Matrix<T, 3, 3>& M)
	{
		T A = M(0, 0) * determinant(M(1, 1), M(1, 2), M(2, 1), M(2, 2));
		T B = M(0, 1) * determinant(M(1, 0), M(1, 2), M(2, 0), M(2, 2));
		T C = M(0, 2) * determinant(M(1, 0), M(1, 1), M(2, 0), M(2, 1));

		return A - B + C;
	}
}

// Overload of unary operator -
template <jl::std_arithmetic T, std::size_t R, std::size_t C>
jl::Matrix<T, R, C> operator - (const jl::Matrix<T, R, C>& A)
{
	jl::Matrix<T, R, C> M;

	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * static_cast<T>(-1);
	}

	return M;
}

// Overload of binary operator +
template <jl::std_arithmetic T, std::size_t R, std::size_t C>
jl::Matrix<T, R, C> operator + (const jl::Matrix<T, R, C>& A, const jl::Matrix<T, R, C>& B)
{
	jl::Matrix<T, R, C> M;

	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) + B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator -
template <jl::std_arithmetic T, std::size_t R, std::size_t C>
jl::Matrix<T, R, C> operator - (const jl::Matrix<T, R, C>& A, const jl::Matrix<T, R, C>& B)
{
	jl::Matrix<T, C, R> M;

	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) - B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator *
template <jl::std_arithmetic T, jl::std_arithmetic U, std::size_t R, std::size_t C>
jl::Matrix<T, R, C> operator * (const jl::Matrix<T, R, C>& A, U scalar)
{
	jl::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * scalar;
	}

	return M;
}

// Overload of binary operator *
template <jl::std_arithmetic T, jl::std_arithmetic U, std::size_t R, std::size_t C>
jl::Matrix<T, R, C> operator * (U scalar, const jl::Matrix<T, R, C>& A)
{
	jl::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * scalar;
	}

	return M;
}

// Overload of binary operator /
template <jl::std_arithmetic T, jl::std_arithmetic U, std::size_t R, std::size_t C>
jl::Matrix<T, R, C> operator / (const jl::Matrix<T, R, C>& A, U scalar)
{
	jl::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) / scalar;
	}

	return M;
}

// Overload of binary operator +=
template <jl::std_arithmetic T, jl::std_arithmetic U, std::size_t R, std::size_t C>
jl::Matrix<T, R, C>& operator += (jl::Matrix<T, R, C>& A, const jl::Matrix<U, R, C>& B)
{
	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			A(row_i, col_i) += B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator -=
template <jl::std_arithmetic T, jl::std_arithmetic U, std::size_t R, std::size_t C>
jl::Matrix<T, R, C>& operator -= (jl::Matrix<T, R, C>& A, const jl::Matrix<U, R, C>& B)
{
	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			A(row_i, col_i) -= B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator *=
template <jl::std_arithmetic T, jl::std_arithmetic U, std::size_t R, std::size_t C>
jl::Matrix<T, R, C>& operator *= (jl::Matrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) *= scalar;
	}

	return M;
}

// Overload of binary operator /=
template <jl::std_arithmetic T, jl::std_arithmetic U, std::size_t R, std::size_t C>
jl::Matrix<T, R, C>& operator /= (jl::Matrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0u); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0u); col_i < C; ++col_i)
			M(row_i, col_i) /= scalar;
	}

	return M;
}