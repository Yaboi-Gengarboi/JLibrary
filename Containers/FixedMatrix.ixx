// JLibrary
// Containers
// FixedMatrix.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-03-05 by Justyn Durnford
// Module file for the FixedMatrix template class.

module;

#include "Arithmetic.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

export module FixedMatrix;

import FixedArray;
import MiscTemplateFunctions;

export namespace jlib
{
	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A FixedMatrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <typename T, std::size_t R, std::size_t C> class FixedMatrix
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = FixedArray<T, R* C>::iterator;
		using const_iterator = FixedArray<T, R* C>::const_iterator;
		using reverse_iterator = FixedArray<T, R* C>::reverse_iterator;
		using const_reverse_iterator = FixedArray<T, R* C>::const_reverse_iterator;

		private:

		FixedArray<T, R* C> _data;

		public:

		// Default constructor.
		FixedMatrix() = default;

		// 1-parameter constructor.
		// Sets every element of the FixedMatrix to value.
		FixedMatrix(const_reference value)
		{
			std::fill(data(), data() + size(), value);
		}

		// 2-dimensional std::initializer_list constructor.
		FixedMatrix(std::initializer_list<std::initializer_list<T>> list)
		{
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + C, _data.begin() + (row_i * C));
				++row_i;
			}
		}

		// Constructs the FixedMatrix from another type of FixedMatrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <typename U>
		explicit FixedMatrix(const FixedMatrix<U, R, C>& other)
		{
			jlib::copy(other.data(), other.data() + size(), data());
		}

		// 2-dimensional std::initializer_list assignment operator.
		FixedMatrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				std::copy(elem.begin(), elem.begin() + C, _data.begin() + (row_i * C));
				++row_i;
			}

			return *this;
		}

		// Returns the number of rows in the FixedMatrix.
		constexpr size_type rowCount() const noexcept
		{
			return R;
		}

		// Returns the number of columns in the FixedMatrix.
		constexpr size_type colCount() const noexcept
		{
			return C;
		}

		// Returns the number of elements in the FixedMatrix.
		constexpr size_type size() const noexcept
		{
			return R * C;
		}

		// Returns the pointer of the FixedMatrix.
		pointer data() noexcept
		{
			return _data.data();
		}

		// Returns the pointer of the FixedMatrix.
		const_pointer data() const noexcept
		{
			return _data.data();
		}

		// Returns an iterator pointing to the first element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		iterator begin() noexcept
		{
			return _data.begin();
		}

		// Returns an iterator pointing to the first element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_iterator begin() const noexcept
		{
			return _data.cbegin();
		}

		// Returns an iterator pointing to the first element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_iterator cbegin() const noexcept
		{
			return _data.cbegin();
		}

		// Returns a reverse iterator pointing to the first element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		reverse_iterator rbegin() noexcept
		{
			return std::reverse_iterator<iterator>(_data + R * C);
		}

		// Returns a reverse iterator pointing to the first element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_reverse_iterator rbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + R * C);
		}

		// Returns a reverse iterator pointing to the first element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_reverse_iterator crbegin() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data + R * C);
		}

		// Returns an iterator pointing to 1 past the last element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		iterator end() noexcept
		{
			return _data.end();
		}

		// Returns an iterator pointing to 1 past the last element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_iterator end() const noexcept
		{
			return _data.cend();
		}

		// Returns an iterator pointing to 1 past the last element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_iterator cend() const noexcept
		{
			return _data.cend();
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		reverse_iterator rend() noexcept
		{
			return std::reverse_iterator<iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_reverse_iterator rend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns a reverse iterator pointing to 1 past the last element of the FixedMatrix.
		// Returns nullptr if the FixedMatrix is empty.
		const_reverse_iterator crend() const noexcept
		{
			return std::reverse_iterator<const_iterator>(_data);
		}

		// Returns an iterator pointing to the first element of the given row.
		iterator rowBegin(size_type row) noexcept
		{
			return _data.begin() + (C * row);
		}

		// Returns an iterator pointing to the first element of the given row.
		const_iterator rowBegin(size_type row) const noexcept
		{
			return _data.cbegin() + (C * row);
		}

		// Returns the element at the given index of the FixedMatrix.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type n)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return _data[n];
		}

		// Returns the element at the given index of the FixedMatrix.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type n) const
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return _data[n];
		}

		// Returns the element at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type row, size_type col)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Returns the element at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type row, size_type col) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type n, const_reference value)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			_data[n] = value;
		}

		// Sets the element at [row][col] to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type row, size_type col, const_reference value)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			_data[(row * C) + col] = value;
		}

		// Returns a copy of the given row.
		std::array<T, C> getRow(size_type row) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index.");

			std::array<T, C> arr;

			for (size_type col_i(0); col_i < C; ++col_i)
				arr[col_i] = _data[(C * row) + col_i];

			return arr;
		}

		// Returns a copy of the given column.
		std::array<T, R> getCol(size_type col) const
		{
			if (col >= C)
				throw std::out_of_range("Invalid column index.");

			std::array<T, R> arr;

			for (size_type row_i(0); row_i < C; ++row_i)
				arr[row_i] = _data[(C * row_i) + col];

			return arr;
		}

		// Returns the submatrix formed by the row and col indices.
		template <size_type R2, size_type C2>
		FixedMatrix<T, R2, C2> submatrix(size_type row_begin, size_type col_begin) const
		{
			if (row_begin >= R || row_begin + R2)
				throw std::out_of_range("Invalid row index.");
			if (col_begin >= C || col_begin + C >= C2)
				throw std::out_of_range("Invalid column index.");

			FixedMatrix<T, R2, C2> M;

			for (size_type row_i(0); row_i < R2; ++row_i)
			{
				for (size_type col_i(0); col_i < C2; ++col_i)
					M._data[(row_i * C) + col_i] = _data[(row_i * C) + col_i];
			}

			return M;
		}

		// Swaps the contents of this FixedMatrix with another FixedMatrix.
		void swapWith(FixedMatrix& other) noexcept
		{
			_data.swapWith(other._data);
		}

		// Returns the element at the given index the FixedMatrix.
		// Does NOT perform bounds-checking.
		reference operator [] (size_type n)
		{
			return _data[n];
		}

		// Returns the element at the given index the FixedMatrix.
		// Does NOT perform bounds-checking.
		const_reference operator [] (size_type n) const
		{
			return _data[n];
		}

		#if __cplusplus <= 202002L

			// Returns the element at [row][col].
			// Does NOT perform bounds-checking.
			reference operator () (size_type row, size_type col)
			{
				return _data[(row * C) + col];
			}

			// Returns the element at [row][col].
			// Does NOT perform bounds-checking.
			const_reference operator () (size_type row, size_type col) const
			{
				return _data[(row * C) + col];
			}

		#else

			// Returns the element at [row][col].
			// Does NOT perform bounds-checking.
			reference operator [] (size_type row, size_type col)
			{
				return _data[(row * C) + col];
			}

			// Returns the element at [row][col].
			// Does NOT perform bounds-checking.
			const_reference operator [] (size_type row, size_type col) const
			{
				return _data[(row * C) + col];
			}

		#endif // #if __cplusplus <= 202002L
	};

	// Returns the determinant of the 2x2 FixedMatrix formed as
	// {  a,  b  }
	// {  c,  d  }
	template <arithmetic T>
	constexpr T determinant(T a, T b, T c, T d)
	{
		return (a * d) - (b * c);
	}

	// Returns the determinant of the 2x2 FixedMatrix.
	template <arithmetic T>
	constexpr T determinant(const FixedMatrix<T, 2, 2>& M)
	{
		return (M(0, 0) * M(1, 1)) - (M(1, 0) * M(0, 1));
	}

	// Returns the determinant of the 3x3 FixedMatrix.
	template <arithmetic T>
	T determinant(const FixedMatrix<T, 3, 3>& M)
	{
		T A = M(0, 0) * determinant(M(1, 1), M(1, 2), M(2, 1), M(2, 2));
		T B = M(0, 1) * determinant(M(1, 0), M(1, 2), M(2, 0), M(2, 2));
		T C = M(0, 2) * determinant(M(1, 0), M(1, 1), M(2, 0), M(2, 1));

		return A - B + C;
	}

	// Returns the determinant of the 4x4 FixedMatrix.
	template <arithmetic T>
	T determinant(const FixedMatrix<T, 4, 4>& M)
	{
		FixedMatrix<T, 3, 3> A =
		{
			{ M(1, 1), M(1, 2), M(1, 3) },
			{ M(2, 1), M(2, 2), M(2, 3) },
			{ M(3, 1), M(3, 2), M(3, 3) }
		};

		FixedMatrix<T, 3, 3> B =
		{
			{ M(1, 0), M(1, 2), M(1, 3) },
			{ M(2, 0), M(2, 2), M(2, 3) },
			{ M(3, 0), M(3, 2), M(3, 3) }
		};

		FixedMatrix<T, 3, 3> C =
		{
			{ M(1, 0), M(1, 1), M(1, 3) },
			{ M(2, 0), M(2, 1), M(2, 3) },
			{ M(3, 0), M(3, 1), M(3, 3) }
		};

		FixedMatrix<T, 3, 3> D =
		{
			{ M(1, 0), M(1, 1), M(1, 2) },
			{ M(2, 0), M(2, 1), M(2, 2) },
			{ M(3, 0), M(3, 1), M(3, 2) }
		};

		return M(0, 0) * determinant(A) - M(0, 1) * determinant(B) + M(0, 2) * determinant(C) - M(0, 3) * determinant(D);
	}

	// Returns the dot product of the given Matrices.
	template <arithmetic T, std::size_t R, std::size_t C, std::size_t S>
	FixedMatrix<T, R, S> dot_product(const FixedMatrix<T, R, C>& A, const FixedMatrix<T, C, S>& B)
	{
		FixedMatrix<T, R, S> M;
		T value;

		for (std::size_t r(0); r < R; ++r)
		{
			std::array<T, C> row(A.getRow(r));

			for (std::size_t s(0); s < S; ++s)
			{
				value = 0;
				std::array<R, C> col(B.getCol(s));

				for (std::size_t c(0); c < C; ++c)
					value += row[c] * col[c];

				M(r, s) = value;
			}
		}

		return M;
	}

	// Overload of binary operator == 
	template <typename T, std::size_t R, std::size_t C>
	bool operator == (const FixedMatrix<T, R, C>& A, const FixedMatrix<T, R, C>& B)
	{
		for (std::size_t i(0); i < R * C; ++i)
		{
			if (A[i] != B[i])
				return false;
		}

		return true;
	}

	// Overload of binary operator != 
	template <typename T, std::size_t R, std::size_t C>
	bool operator != (const FixedMatrix<T, R, C>& A, const FixedMatrix<T, R, C>& B)
	{
		for (std::size_t i(0); i < R * C; ++i)
		{
			if (A[i] != B[i])
				return true;
		}

		return false;
	}

	// Overload of unary operator -
	template <arithmetic T, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C> operator - (const FixedMatrix<T, R, C>& A)
	{
		FixedMatrix<T, R, C> M;

		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				M(row_i, col_i) = A(row_i, col_i) * static_cast<T>(-1);
		}

		return M;
	}

	// Overload of binary operator +
	template <arithmetic T, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C> operator + (const FixedMatrix<T, R, C>& A, const FixedMatrix<T, R, C>& B)
	{
		FixedMatrix<T, R, C> M;

		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				M(row_i, col_i) = A(row_i, col_i) + B(row_i, col_i);
		}

		return M;
	}

	// Overload of binary operator -
	template <arithmetic T, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C> operator - (const FixedMatrix<T, R, C>& A, const FixedMatrix<T, R, C>& B)
	{
		FixedMatrix<T, C, R> M;

		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				M(row_i, col_i) = A(row_i, col_i) - B(row_i, col_i);
		}

		return M;
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C> operator * (const FixedMatrix<T, R, C>& A, U scalar)
	{
		FixedMatrix<T, C, R> M;

		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				M(row_i, col_i) = A(row_i, col_i) * scalar;
		}

		return M;
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C> operator / (const FixedMatrix<T, R, C>& A, U scalar)
	{
		FixedMatrix<T, C, R> M;

		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				M(row_i, col_i) = A(row_i, col_i) / scalar;
		}

		return M;
	}

	// Overload of binary operator +=
	template <arithmetic T, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C>& operator += (FixedMatrix<T, R, C>& A, const FixedMatrix<T, R, C>& B)
	{
		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				A(row_i, col_i) += B(row_i, col_i);
		}

		return A;
	}

	// Overload of binary operator -=
	template <arithmetic T, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C>& operator -= (FixedMatrix<T, R, C>& A, const FixedMatrix<T, R, C>& B)
	{
		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				A(row_i, col_i) -= B(row_i, col_i);
		}

		return A;
	}

	// Overload of binary operator *=
	template <arithmetic T, arithmetic U, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C>& operator *= (FixedMatrix<T, R, C>& M, U scalar)
	{
		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				M(row_i, col_i) *= scalar;
		}

		return M;
	}

	// Overload of binary operator /=
	template <arithmetic T, arithmetic U, std::size_t R, std::size_t C>
	FixedMatrix<T, R, C>& operator /= (FixedMatrix<T, R, C>& M, U scalar)
	{
		for (std::size_t row_i(0); row_i < R; ++row_i)
		{
			for (std::size_t col_i(0); col_i < C; ++col_i)
				M(row_i, col_i) /= scalar;
		}

		return M;
	}
}