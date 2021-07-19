// JLibraryDevelopment
// Matrix.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Header file for the Matrix template class.

#pragma once

#include <Jlibrary/Math/Arithmetic.hpp>
#include <array>
#include <stdexcept>

namespace jlib
{
	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A Matrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <std::semiregular T, std::size_t R, std::size_t C> class Matrix
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
		using iterator = T*;
		using const_iterator = const T*;

		private:

		pointer data_;

		// 
		void allocate()
		{
			if (R != 0 && C != 0)
				data_ = new T[R * C];
			else
				data_ = nullptr;
		}

		// 
		void copyElements(pointer dst_begin, const_pointer src_begin, size_type count)
		{
			for (size_type i(0); i < count; ++i)
				dst_begin[i] = src_begin[i];
		}

		public:

		// Default constructor.
		Matrix()
		{
			allocate();
		}

		// 1-parameter constructor.
		// Sets every element of the Matrix to value.
		Matrix(const_reference value)
		{
			allocate();

			for (size_type i(0); i < R * C; ++i)
				data_[i] = value;
		}

		// 2-dimensional std::initializer_list constructor.
		Matrix(std::initializer_list<std::initializer_list<T>> list)
		{
			allocate();
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				copyElements(&data_[row_i * C], elem.begin(), C);
				++row_i;
			}
		}

		// Copy constructor.
		Matrix(const Matrix& other)
		{
			allocate();
			copyElements(data_, other.data_, R * C);
		}

		// Constructs the Matrix from another type of Matrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::semiregular U>
		explicit Matrix(const Matrix<U, R, C>& other)
		{
			allocate();

			for (size_type i(0); i < R * C; ++i)
				data_[i] = static_cast<T>(other.data_[i]);
		}

		// Move constructor.
		Matrix(Matrix&& other) noexcept
		{
			data_ = other.data_;
			other.data_ = nullptr;
		}

		// 2-dimensional std::initializer_list assignment operator.
		Matrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			size_type row_i = 0;

			for (const auto& elem : list)
			{
				copyElements(&data_[row_i * C], elem.begin(), C);
				++row_i;
			}

			return *this;
		}

		// Copy assignment operator.
		Matrix& operator = (const Matrix& other)
		{
			copyElements(data_, other.data_, R * C);
			return *this;
		}

		// Move assignment operator.
		Matrix& operator = (Matrix&& other) noexcept
		{
			delete[] data_;

			data_ = other.data_;
			other.data_ = nullptr;

			return *this;
		}

		// Destructor.
		~Matrix() noexcept
		{
			delete[] data_;
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		reference at(size_type n)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return data_[n];
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		const_reference at(size_type n) const
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return data_[n];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		reference at(size_type row, size_type col)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return data_[(row * R) + col];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		const_reference at(size_type row, size_type col) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return data_[(row * R) + col];
		}

		// Sets the nth element of the Matrix to value.
		// Performs bounds-checking.
		void set(size_type n, const_reference value)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			data_[n] = value;
		}

		// Sets the element at [row][col] to value.
		// Performs bounds-checking.
		void set(size_type row, size_type col, const_reference value)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			data_[(row * R) + col] = value;
		}

		// Returns the nth element of the Matrix.
		reference operator [] (size_type n)
		{
			return data_[n];
		}

		// Returns the nth element of the Matrix.
		const_reference operator [] (size_type n) const
		{
			return data_[n];
		}

		// Returns the element at [row][col].
		reference operator () (size_type row, size_type col)
		{
			return data_[(row * R) + col];
		}

		// Returns the element at [row][col].
		const_reference operator () (size_type row, size_type col) const
		{
			return data_[(row * R) + col];
		}

		// Returns the number of rows in the Matrix.
		size_type rowCount() const
		{
			return R;
		}

		// Returns the number of columns in the Matrix.
		size_type colCount() const
		{
			return C;
		}

		// Returns the number of elements in the Matrix.
		size_type size() const
		{
			return R * C;
		}

		// Returns a copy of the given row.
		std::array<T, C> getRow(size_type row) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index.");

			std::array<T, C> arr;

			for (size_type col_i(0); col_i < C; ++col_i)
				arr[col_i] = data_[(C * row) + col_i];

			return arr;
		}

		// Returns a copy of the given column.
		std::array<T, R> getCol(size_type col) const
		{
			if (col >= C)
				throw std::out_of_range("Invalid column index.");

			std::array<T, R> arr;

			for (size_type row_i(0); row_i < C; ++row_i)
				arr[row_i] = data_[(C * row_i) + col];

			return arr;
		}

		// Returns the submatrix formed by the row and col indices.
		template <size_type R2, size_type C2>
		Matrix<T, R2, C2> submatrix(size_type row_begin, size_type col_begin) const
		{
			if (row_begin >= R || row_begin + R2)
				throw std::out_of_range("Invalid row index.");
			if (col_begin >= C || col_begin + C >= C2)
				throw std::out_of_range("Invalid column index.");

			Matrix<T, R2, C2> M;

			for (size_type row_i(0); row_i < R2; ++row_i)
			{
				for (size_type col_i(0); col_i < C2; ++col_i)
					M.data_[(row_i * R) + col_i] = data_[(row_i * R) + col_i];
			}

			return M;
		}

		// 
		iterator begin()
		{
			return data_;
		}

		// 
		const_iterator begin() const
		{
			return data_;
		}

		// 
		iterator end()
		{
			return data_;
		}

		// 
		const_iterator end() const
		{
			return data_;
		}

		// 
		iterator rowBegin(size_type row)
		{
			return data_ + (R * row);
		}

		// 
		const_iterator rowBegin(size_type row) const
		{
			return data_ + (R * row);
		}
	};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

	// Returns the determinant of the 2x2 Matrix formed as
	// {  a,  b  }
	// {  c,  d  }
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

	// Returns the determinant of the 4x4 Matrix.
	template <std_arithmetic T>
	T determinant(const Matrix<T, 4, 4>& M)
	{
		Matrix<T, 3, 3> A =
		{
			{ M(1, 1), M(1, 2), M(1, 3) },
			{ M(2, 1), M(2, 2), M(2, 3) },
			{ M(3, 1), M(3, 2), M(3, 3) }
		};

		Matrix<T, 3, 3> B =
		{
			{ M(1, 0), M(1, 2), M(1, 3) },
			{ M(2, 0), M(2, 2), M(2, 3) },
			{ M(3, 0), M(3, 2), M(3, 3) }
		};

		Matrix<T, 3, 3> C =
		{
			{ M(1, 0), M(1, 1), M(1, 3) },
			{ M(2, 0), M(2, 1), M(2, 3) },
			{ M(3, 0), M(3, 1), M(3, 3) }
		};

		Matrix<T, 3, 3> D =
		{
			{ M(1, 0), M(1, 1), M(1, 2) },
			{ M(2, 0), M(2, 1), M(2, 2) },
			{ M(3, 0), M(3, 1), M(3, 2) }
		};

		return M(0, 0) * determinant(A) - M(0, 1) * determinant(B) + M(0, 2) * determinant(C) - M(0, 3) * determinant(D);
	}

	// Returns the dot product of the given Matrices.
	template <std_arithmetic T, std::size_t R, std::size_t C, std::size_t S>
	Matrix<T, R, S> dot_product(const Matrix<T, R, C>& A, const Matrix<T, C, S>& B)
	{
		Matrix<T, R, S> M;
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
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Overload of binary operator == 
template <std::regular T, std::size_t R, std::size_t C>
bool operator == (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
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
template <std::regular T, std::size_t R, std::size_t C>
bool operator != (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
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

// Overload of unary operator -
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator - (const jlib::Matrix<T, R, C>& A)
{
	jlib::Matrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * static_cast<T>(-1);
	}

	return M;
}

// Overload of binary operator +
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator + (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	jlib::Matrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) + B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator -
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator - (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	jlib::Matrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) - B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator * (const jlib::Matrix<T, R, C>& A, U scalar)
{
	jlib::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * scalar;
	}

	return M;
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator / (const jlib::Matrix<T, R, C>& A, U scalar)
{
	jlib::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) / scalar;
	}

	return M;
}

// Overload of binary operator +=
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator += (jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			A(row_i, col_i) += B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator -= (jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			A(row_i, col_i) -= B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator *= (jlib::Matrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) *= scalar;
	}

	return M;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator /= (jlib::Matrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) /= scalar;
	}

	return M;
}